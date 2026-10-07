// Mark verified descriptor-shaped regions as data in a fresh Ghidra project.
// This changes the Ghidra listing only, not the preserved firmware dump.
// @category Hi75

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.ArrayDataType;
import ghidra.program.model.data.ByteDataType;

import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;

public class MarkFirmwareDescriptors extends GhidraScript {
    private static final int[][] REGIONS = {
        {0x53B2, 67}, {0x53F5, 240}, {0x54E5, 18}, {0x54F7, 59}
    };

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
        File output = new File(directory, "descriptor-data-marking.txt");
        if (output.exists()) {
            throw new IllegalStateException("Refusing to overwrite " + output);
        }
        Address device = toAddr("54E5");
        Address config = toAddr("54F7");
        if ((currentProgram.getMemory().getByte(device) & 0xff) != 0x12 ||
            (currentProgram.getMemory().getByte(device.add(1)) & 0xff) != 0x01 ||
            (currentProgram.getMemory().getByte(config) & 0xff) != 0x09 ||
            (currentProgram.getMemory().getByte(config.add(1)) & 0xff) != 0x02) {
            throw new IllegalStateException("Descriptor signatures do not match this firmware image");
        }
        try (PrintWriter writer = new PrintWriter(output, StandardCharsets.UTF_8)) {
            writer.println("Ghidra listing annotations only; source image untouched.");
            for (int[] region : REGIONS) {
                Address start = toAddr(String.format("%04X", region[0]));
                createData(start, new ArrayDataType(ByteDataType.dataType, region[1], 1));
                writer.println(start + " length=" + region[1]);
            }
        }
        println("Wrote " + output.getAbsolutePath());
    }
}
