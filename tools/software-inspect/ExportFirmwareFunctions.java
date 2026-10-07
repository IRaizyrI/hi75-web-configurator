// Export the analyzed firmware functions for offline, read-only inspection.
// @category Hi75

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;

import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;

public class ExportFirmwareFunctions extends GhidraScript {
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
        File index = new File(directory, "functions-index.txt");
        File c = new File(directory, "firmware-decompiled.c");
        File asm = new File(directory, "firmware-disassembly.txt");
        if (index.exists() || c.exists() || asm.exists()) {
            throw new IllegalStateException("Refusing to overwrite existing exports");
        }
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        try (PrintWriter indexOut = new PrintWriter(index, StandardCharsets.UTF_8);
             PrintWriter cOut = new PrintWriter(c, StandardCharsets.UTF_8);
             PrintWriter asmOut = new PrintWriter(asm, StandardCharsets.UTF_8)) {
            indexOut.println("8051 function index from Ghidra; addresses and boundaries are analytical, not validated on device.");
            FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
            int count = 0;
            while (functions.hasNext() && !monitor.isCancelled()) {
                Function function = functions.next();
                count++;
                String header = "===== " + function.getName() + " " +
                    function.getEntryPoint() + " size=" + function.getBody().getNumAddresses() + " =====";
                indexOut.println(header);
                cOut.println("\n" + header);
                DecompileResults result = decompiler.decompileFunction(function, 10, monitor);
                if (result.decompileCompleted() && result.getDecompiledFunction() != null) {
                    cOut.println(result.getDecompiledFunction().getC());
                } else {
                    cOut.println("// Decompilation unavailable: " + result.getErrorMessage());
                }
                asmOut.println("\n" + header);
                InstructionIterator instructions = currentProgram.getListing().getInstructions(function.getBody(), true);
                while (instructions.hasNext()) {
                    Instruction instruction = instructions.next();
                    asmOut.println(instruction.getAddress() + " " + instruction);
                }
            }
            indexOut.println("Total exported: " + count);
        } finally {
            decompiler.dispose();
        }
        println("Exported firmware functions to " + directory.getAbsolutePath());
    }
}
