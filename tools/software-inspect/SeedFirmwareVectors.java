// Seed Ghidra analysis at standard 8051 vectors in a copy of the preserved dump.
// This changes only the Ghidra project, never the source image or the keyboard.
// @category Hi75

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;

import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;

public class SeedFirmwareVectors extends GhidraScript {
    private static final int[] VECTORS = {0x0000, 0x0003, 0x000B, 0x0013,
        0x001B, 0x0023, 0x002B, 0x0033, 0x003B};

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
        File output = new File(directory, "vector-seeding.txt");
        if (output.exists()) {
            throw new IllegalStateException("Refusing to overwrite " + output);
        }
        try (PrintWriter writer = new PrintWriter(output, StandardCharsets.UTF_8)) {
            writer.println("Ghidra project analysis only; no hardware access or source-image mutation.");
            writer.println("Program: " + currentProgram.getName());
            for (int offset : VECTORS) {
                Address vector = toAddr(String.format("%04X", offset));
                int opcode = currentProgram.getMemory().getByte(vector) & 0xff;
                writer.printf("vector %s opcode=%02X", vector, opcode);
                if (opcode != 0x02) {
                    writer.println("; not an LJMP, left for manual review");
                    continue;
                }
                int high = currentProgram.getMemory().getByte(vector.add(1)) & 0xff;
                int low = currentProgram.getMemory().getByte(vector.add(2)) & 0xff;
                Address target = toAddr(String.format("%04X", (high << 8) | low));
                writer.print(" target=" + target);
                if (!currentProgram.getMemory().contains(target)) {
                    writer.println("; target outside imported firmware");
                    continue;
                }
                disassemble(vector);
                disassemble(target);
                Function function = getFunctionAt(target);
                if (function == null) {
                    function = createFunction(target, "vector_target_" +
                        String.format("%04X", offset));
                }
                writer.println(" function=" + (function == null ? "none" : function.getName()));
            }
            analyzeChanges(currentProgram);
            writer.println("Functions after analysis: " +
                currentProgram.getFunctionManager().getFunctionCount());
            for (int offset : VECTORS) {
                Address address = toAddr(String.format("%04X", offset));
                Instruction instruction = currentProgram.getListing().getInstructionAt(address);
                writer.println(address + " " + (instruction == null ? "undefined" : instruction));
            }
        }
        println("Wrote " + output.getAbsolutePath());
    }
}
