# Incomplete experiment: no brightness change occurred

The timed capture ran from `2026-09-19T21:49:06.3511294Z` to
`2026-09-19T21:49:52.0105146Z` and exited successfully, but the intended
official-app brightness action was interrupted before it happened. The filename
records the planned action only. The 756-byte pcapng has six control frames
and **zero HID report transfers** according to
`tools/packet-diff/extract_control.py`; see `derived/summary.json`.
This file is retained as raw evidence and must not be used to infer a brightness
field or behavior.
