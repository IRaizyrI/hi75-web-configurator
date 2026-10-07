# Headless Ghidra Jython script. Static PE analysis; never executes the target.
# @category Hi75

from java.io import File, PrintWriter
from ghidra.app.decompiler import DecompInterface


addresses = [
    '00410b00', '0048b180', '0048b210', '0048ef20',
    '0048f696', '0048ff90', '005bd73c', '005bd742',
]

args = getScriptArgs()
if len(args) != 1:
    raise ValueError('Pass one output directory')
directory = File(args[0])
if not directory.isDirectory() and not directory.mkdirs():
    raise IOError('Could not create output directory')
output = File(directory, 'hid-paths.txt')
if output.exists():
    raise IOError('Refusing to overwrite ' + str(output))

fm = currentProgram.getFunctionManager()
rm = currentProgram.getReferenceManager()
decompiler = DecompInterface()
decompiler.toggleCCode(True)
decompiler.toggleSyntaxTree(True)
if not decompiler.openProgram(currentProgram):
    raise RuntimeError('Could not open program in decompiler')

targets = [toAddr(value) for value in addresses]
for thunk in ('005bd73c', '005bd742'):
    for ref in rm.getReferencesTo(toAddr(thunk)):
        if ref.getReferenceType().isCall():
            caller = fm.getFunctionContaining(ref.getFromAddress())
            if caller is not None:
                targets.append(caller.getEntryPoint())

writer = PrintWriter(output, 'UTF-8')
try:
    writer.println('Static analysis only; target executable was not run.')
    writer.println('Program: ' + str(currentProgram.getName()))
    writer.println('Image base: ' + str(currentProgram.getImageBase()))
    writer.println('Selected targets and analyzed direct callers of HID feature thunks.')
    emitted = set()
    for address in targets:
        function = fm.getFunctionContaining(address)
        if function is None:
            writer.println('\nTarget %s: no analyzed function' % address)
            continue
        entry = str(function.getEntryPoint())
        if entry in emitted:
            continue
        emitted.add(entry)
        writer.println('\n===== target %s function %s @ %s =====' %
                       (address, function.getName(), entry))
        writer.println('Body addresses: ' + str(function.getBody().getNumAddresses()))
        writer.println('Direct references to entry:')
        reference_count = 0
        for ref in rm.getReferencesTo(function.getEntryPoint()):
            caller = fm.getFunctionContaining(ref.getFromAddress())
            caller_name = 'unknown' if caller is None else '%s@%s' % (caller.getName(), caller.getEntryPoint())
            writer.println('  %s %s caller=%s' %
                           (ref.getFromAddress(), ref.getReferenceType(), caller_name))
            reference_count += 1
        writer.println('Reference count: ' + str(reference_count))
        result = decompiler.decompileFunction(function, 120, monitor)
        if result.decompileCompleted() and result.getDecompiledFunction() is not None:
            writer.println('Decompiled C:\n' + result.getDecompiledFunction().getC())
        else:
            writer.println('Decompilation unavailable: ' + result.getErrorMessage())
finally:
    writer.close()
    decompiler.dispose()

print('Wrote ' + output.getAbsolutePath())
