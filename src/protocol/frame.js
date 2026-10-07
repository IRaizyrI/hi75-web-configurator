// Report-ID-6 framing used by the official app and the firmware handler at
// CODE 0x0340: [cmd, arg, 0, chunkCount, chunkIndex, lenLo, lenHi, data...].
// WebHID takes the report ID separately, so bodies here are 519 bytes.
export const REPORT_ID = 6;
export const BODY_BYTES = 519;
export const HEADER_BYTES = 7;
export const MAX_CHUNK = 512;

export function buildBody({ command, arg = 0, chunkCount = 1, chunkIndex = 0, length, data }) {
  const len = data ? data.length : length;
  if (!Number.isInteger(len) || len < 0 || len > MAX_CHUNK) throw new RangeError(`Chunk length ${len} out of range`);
  const body = new Uint8Array(BODY_BYTES);
  body[0] = command;
  body[1] = arg;
  body[3] = chunkCount;
  body[4] = chunkIndex;
  body[5] = len & 0xff;
  body[6] = len >> 8;
  if (data) body.set(data, HEADER_BYTES);
  return body;
}

// The returned feature DataView may or may not include the report ID
// (observed: it does on Chrome/Windows). Commands are never 0x06 in replies we
// parse, so a leading 0x06 is the ID.
export function parseReply(bytes) {
  const raw = Uint8Array.from(bytes);
  const off = raw[0] === REPORT_ID ? 1 : 0;
  if (raw.length < off + HEADER_BYTES) throw new RangeError("Reply shorter than the 8-byte header");
  const h = raw.subarray(off);
  const length = h[5] | (h[6] << 8);
  return {
    command: h[0],
    arg: h[1],
    chunkCount: h[3],
    chunkIndex: h[4],
    length,
    data: h.slice(HEADER_BYTES, HEADER_BYTES + length),
    truncated: h.length - HEADER_BYTES < length,
  };
}
