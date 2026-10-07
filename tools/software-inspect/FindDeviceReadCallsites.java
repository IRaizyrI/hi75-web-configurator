// Locate indirect-call candidates for CDevG5KB read vtable slots.
// @category Hi75

import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.scalar.Scalar;

import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;

public class FindDeviceReadCallsites extends GhidraScript {
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
        File output = new File(directory, "device-read-callsites.txt");
        if (output.exists()) {
            throw new IllegalStateException("Refusing to overwrite " + output);
        }
        try (PrintWriter writer = new PrintWriter(output, StandardCharsets.UTF_8)) {
            writer.println("Static callsite scan only. Slot +0x5c is a candidate GetMatrix call, not proof of execution.");
            InstructionIterator instructions = currentProgram.getListing().getInstructions(true);
            int count = 0;
            while (instructions.hasNext() && !monitor.isCancelled()) {
                Instruction instruction = instructions.next();
                String mnemonic = instruction.getMnemonicString().toUpperCase();
                if (!mnemonic.startsWith("CALL")) {
                    continue;
                }
                boolean candidate = false;
                for (int operand = 0; operand < instruction.getNumOperands(); operand++) {
                    for (Object object : instruction.getOpObjects(operand)) {
                        if (object instanceof Scalar scalar &&
                            (scalar.getUnsignedValue() == 0x5c || scalar.getUnsignedValue() == 0x64)) {
                            candidate = true;
                        }
                    }
                }
                if (!candidate) {
                    continue;
                }
                Function function = currentProgram.getFunctionManager()
                    .getFunctionContaining(instruction.getAddress());
                writer.println(instruction.getAddress() + " " + instruction +
                    " caller=" + (function == null ? "none" : function.getName() +
                    "@" + function.getEntryPoint()));
                count++;
            }
            writer.println("Candidates: " + count);
        }
        println("Wrote " + output.getAbsolutePath());
    }
}
