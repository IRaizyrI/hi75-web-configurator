"""Launch Ghidra's existing project in headless mode with local PyGhidra.

Pass the extracted Ghidra directory, then normal analyzeHeadless arguments.
The JPype JVM needs jdk.zipfs for Ghidra's jar: resources on this host.
"""
import sys
from pathlib import Path

from pyghidra.ghidra_launch import GhidraLauncher


if len(sys.argv) < 3:
    raise SystemExit('usage: launch_pyghidra_headless.py <ghidra-dir> <headless-args...>')

launcher = GhidraLauncher(
    class_name='ghidra.app.util.headless.AnalyzeHeadless',
    install_dir=Path(sys.argv[1]),
)
launcher.add_vmargs('--add-modules=jdk.zipfs')
launcher.args = sys.argv[2:]
launcher.start()
