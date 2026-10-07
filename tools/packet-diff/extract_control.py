"""Extract USBPcap control transfers through TShark; file-only, no device I/O.

Offsets in payloadHex include the report-ID byte as actually captured. Setup
bytes are kept separately. No proprietary field meanings are assumed.
"""
import argparse
import hashlib
import json
import struct
import subprocess
from collections import Counter
from pathlib import Path


def extract(capture, tshark):
    command = [str(tshark), '-r', str(capture), '-Y', 'usb.transfer_type == 2', '-T', 'json', '-x']
    completed = subprocess.run(command, capture_output=True, check=True, encoding='utf-8')
    source = json.loads(completed.stdout)
    result, pending = [], {}
    for packet in source:
        layers = packet['_source']['layers']
        frame, usb = layers['frame'], layers['usb']
        raw = bytes.fromhex(layers['frame_raw'][0])
        header = int(usb['usb.usbpcap_header_len'])
        if header > len(raw) or int(frame['frame.cap_len']) != int(frame['frame.len']):
            raise ValueError('Truncated frame or inconsistent USBPcap header')
        data = raw[header:]
        if len(data) != int(usb['usb.data_len']):
            raise ValueError('USBPcap data length does not match captured frame')
        stage = int(usb['usb.control_stage'])
        key = (usb['usb.bus_id'], usb['usb.device_address'], usb['usb.irp_id'])
        row = {'frame': int(frame['frame.number']), 'timeUtc': frame['frame.time'],
               'relativeSeconds': float(frame['frame.time_relative']),
               'bus': int(key[0]), 'deviceAddress': int(key[1]), 'irpId': key[2],
               'stage': stage, 'status': usb['usb.usbd_status'],
               'endpoint': usb['usb.endpoint_address'], 'setup': None,
               'requestFrame': None, 'payloadHex': '', 'payloadBytes': 0}
        if stage == 0:
            if len(data) < 8:
                raise ValueError('Setup packet shorter than eight bytes')
            bm, request, value, index, length = struct.unpack('<BBHHH', data[:8])
            row['setup'] = {'bmRequestType': bm, 'bRequest': request, 'wValue': value,
                            'wIndex': index, 'wLength': length, 'rawHex': data[:8].hex()}
            row['isHidReportTransfer'] = (bm & 0x60) == 0x20 and (bm & 0x1f) == 1 and request in (1,9)
            row['requestFrame'] = row['frame']
            if key in pending:
                raise ValueError('IRP reused before previous control transfer completed')
            pending[key] = row
            data = data[8:]
        else:
            request_row = pending.get(key)
            row['isHidReportTransfer'] = bool(request_row and request_row['isHidReportTransfer'])
            if request_row:
                row['requestFrame'] = request_row['frame']
                row['setup'] = request_row['setup']
            if stage == 3:
                pending.pop(key, None)
        row['payloadHex'] = data.hex()
        row['payloadBytes'] = len(data)
        if row['isHidReportTransfer']:
            row['reportIdFromSetup'] = row['setup']['wValue'] & 255
            row['reportTypeFromSetup'] = row['setup']['wValue'] >> 8
        result.append(row)
    return result, command, completed.stderr, [r['frame'] for r in pending.values()]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('capture', type=Path)
    parser.add_argument('--tshark', type=Path, default=Path(r'C:\Program Files\Wireshark\tshark.exe'))
    args = parser.parse_args()
    rows, command, stderr, incomplete = extract(args.capture, args.tshark)
    derived = args.capture.parent / 'derived'
    derived.mkdir(exist_ok=True)
    report = {'source': args.capture.name,
        'sourceSha256': hashlib.sha256(args.capture.read_bytes()).hexdigest(),
        'scriptSha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'command': command, 'tsharkStderr': stderr, 'incompleteRequestFrames': incomplete,
        'offsetConvention': 'payloadHex includes all captured report bytes including report ID; USB setup is separate',
        'packets': rows}
    (derived / 'control-transfers.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
    hid = [r for r in rows if r['isHidReportTransfer']]
    summary = {'source': args.capture.name, 'controlFrames': len(rows), 'hidReportFrames': len(hid),
        'setReportRequestFrames': [r['frame'] for r in hid if r['stage']==0 and r['setup']['bRequest']==9],
        'getReportRequestFrames': [r['frame'] for r in hid if r['stage']==0 and r['setup']['bRequest']==1],
        'setPayloadPrefixes': dict(Counter(r['payloadHex'][:16] for r in hid if r['stage']==0 and r['setup']['bRequest']==9)),
        'responseLengths': dict(Counter(r['payloadBytes'] for r in hid if r['stage']==3 and r['setup']['bRequest']==1)),
        'incompleteRequestFrames': incomplete}
    (derived / 'summary.json').write_text(json.dumps(summary, indent=2), encoding='utf-8')
    print(json.dumps(summary, indent=2))
    for r in hid:
        if r['payloadBytes']:
            print(f"frame {r['frame']}: {r['payloadBytes']} bytes {r['payloadHex'][:96]}" + ('...' if r['payloadBytes']>48 else ''))


if __name__ == '__main__':
    main()
