// Read-only Ghidra inventory of the preserved 8051 firmware dump.
// @category Hi75

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.mem.MemoryBlock;

import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;

public class ExportFirmwareEntry extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) {
            throw new IllegalArgumentException("Pass a new output directory");
        }
        File directory = new File(args[0]);
        if (!directory.isDirectory() && !directory.mkdirs()) {
            throw new IllegalStateException("Could not create " + directory);
        }
        File output = new File(directory, "firmware-entry.txt");
        if (output.exists()) {
            throw new IllegalStateException("Refusing to overwrite " + output);
        }
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        try (PrintWriter writer = new PrintWriter(output, StandardCharsets.UTF_8)) {
            writer.println("Read-only static analysis; source firmware dump was not modified.");
            writer.println("Program: " + currentProgram.getName());
            writer.println("Language: " + currentProgram.getLanguageID());
            writer.println("Image base: " + currentProgram.getImageBase());
            writer.println("Functions: " + currentProgram.getFunctionManager().getFunctionCount());
            for (MemoryBlock block : currentProgram.getMemory().getBlocks()) {
                writer.println("Block: " + block.getName() + " " + block.getStart() +
                    ".." + block.getEnd() + " execute=" + block.isExecute());
            }
            for (String location : new String[] {"0000", "0003", "000B", "0013", "001B",
                    "0023", "002B", "0033", "003B", "0093A0", "009D49", "00AC89"}) {
                Address address = toAddr(location);
                Function function = currentProgram.getFunctionManager().getFunctionContaining(address);
                writer.println("\n===== address " + address + " function=" +
                    (function == null ? "none" : function.getName() + "@" + function.getEntryPoint()) + " =====");
                Instruction instruction = currentProgram.getListing().getInstructionAt(address);
                for (int count = 0; count < 20 && instruction != null; count++) {
                    writer.println(instruction.getAddress() + " " + instruction);
                    instruction = instruction.getNext();
                }
                if (function != null) {
                    DecompileResults result = decompiler.decompileFunction(function, 30, monitor);
                    if (result.decompileCompleted() && result.getDecompiledFunction() != null) {
                        writer.println("Decompiled C:\n" + result.getDecompiledFunction().getC());
                    } else {
                        writer.println("Decompilation unavailable: " + result.getErrorMessage());
                    }
                }
            }
        } finally {
            decompiler.dispose();
        }
        println("Wrote " + output.getAbsolutePath());
    }
}
