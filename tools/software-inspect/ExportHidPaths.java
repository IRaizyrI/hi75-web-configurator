// Headless Ghidra script. Decompiles selected static paths; never executes the PE.
// @category Hi75

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;

import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.LinkedHashSet;
import java.util.HashSet;
import java.util.Set;

public class ExportHidPaths extends GhidraScript {
    private static final String[] TARGETS = {
        "00410b00", // profile loader / INI reads
        "0048b180", // smaller feature-report transport candidate
        "0048b210", // corresponding feature read candidate
        "0048ef20", // 520-byte chunked transport candidate
        "0048f696", // 0x84 SET/GET builder in initial Capstone listing
        "0048ff90", // 0x82 SET/GET builder in initial Capstone listing
        "005bd73c", // HidD_SetFeature import thunk
        "005bd742"  // HidD_GetFeature import thunk
    };

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 1) {
            throw new IllegalArgumentException("Pass an output directory and optional extra addresses");
        }
        File directory = new File(args[0]);
        if (!directory.isDirectory() && !directory.mkdirs()) {
            throw new IllegalStateException("Could not create " + directory);
        }
        File output = new File(directory, "hid-paths.txt");
        if (output.exists()) {
            throw new IllegalStateException("Refusing to overwrite " + output);
        }

        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        decompiler.toggleSyntaxTree(true);
        if (!decompiler.openProgram(currentProgram)) {
            throw new IllegalStateException("Could not open program in decompiler");
        }
        try (PrintWriter writer = new PrintWriter(output, StandardCharsets.UTF_8)) {
            writer.println("Static analysis only; target executable was not run.");
            writer.println("Program: " + currentProgram.getName());
            writer.println("Image base: " + currentProgram.getImageBase());
            Set<Address> targets = new LinkedHashSet<>();
            for (String target : TARGETS) {
                targets.add(toAddr(target));
            }
            for (int i = 1; i < args.length; i++) {
                targets.add(toAddr(args[i]));
            }
            for (String thunk : new String[] { "005bd73c", "005bd742" }) {
                ReferenceIterator uses = currentProgram.getReferenceManager().getReferencesTo(toAddr(thunk));
                for (Reference use : uses) {
                    if (!use.getReferenceType().isCall()) {
                        continue;
                    }
                    Function caller = currentProgram.getFunctionManager().getFunctionContaining(use.getFromAddress());
                    if (caller != null) {
                        targets.add(caller.getEntryPoint());
                    }
                }
            }
            writer.println("Selected targets and every analyzed direct caller of the HID feature thunks.");
            Set<Address> emitted = new HashSet<>();
            for (Address address : targets) {
                Function function = currentProgram.getFunctionManager().getFunctionContaining(address);
                if (function == null) {
                    writer.println("\nTarget " + address + ": no analyzed function");
                    continue;
                }
                if (!emitted.add(function.getEntryPoint())) {
                    writer.println("\nTarget " + address + " belongs to function already exported: " + function.getEntryPoint());
                    continue;
                }
                writer.println("\n===== target " + address + " function " + function.getName() +
                               " @ " + function.getEntryPoint() + " =====");
                writer.println("Body instructions: " + function.getBody().getNumAddresses());
                writer.println("Direct references to entry:");
                ReferenceIterator references = currentProgram.getReferenceManager()
                    .getReferencesTo(function.getEntryPoint());
                int referenceCount = 0;
                for (Reference reference : references) {
                    Function caller = currentProgram.getFunctionManager()
                        .getFunctionContaining(reference.getFromAddress());
                    writer.println("  " + reference.getFromAddress() + " " +
                                   reference.getReferenceType() + " caller=" +
                                   (caller == null ? "unknown" : caller.getName() + "@" + caller.getEntryPoint()));
                    referenceCount++;
                }
                writer.println("Reference count: " + referenceCount);
                DecompileResults result = decompiler.decompileFunction(function, 120, monitor);
                if (result.decompileCompleted() && result.getDecompiledFunction() != null) {
                    writer.println("Decompiled C:\n" + result.getDecompiledFunction().getC());
                } else {
                    writer.println("Decompilation unavailable: " + result.getErrorMessage());
                }
            }
        } finally {
            decompiler.dispose();
        }
        println("Wrote " + output.getAbsolutePath());
    }
}
