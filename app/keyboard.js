import { HI75_KEYS } from "../src/protocol/hi75-layout.js";

// Bounding box of the official app's key rectangles (KB.ini), plus room for
// the knob in the empty top-right slot.
const X0 = 15, Y0 = 18, W = 648, H = 260;
export const KNOB = { id: 82, name: "Knob", matrix: 84, rect: [625, 28, 653, 56], knob: true };
// Same spelling the Remap page uses for these keys.
const DISPLAY = {
  CapsLock: "Caps Lock", LShift: "L-Shift", RShift: "R-Shift", LCtrl: "L-Ctrl", RCtrl: "R-Ctrl",
  LWin: "L-Win", LAlt: "L-Alt", RAlt: "R-Alt", FN: "Fn", PgUp: "PgUp", PgDn: "PgDn",
};
export const KEYS = HI75_KEYS.map((k) => (k.rect[2] === 0 ? KNOB : { ...k, name: DISPLAY[k.name] ?? k.name }));
// Knob rotation slots used by the knob firmware patch (tools/software-inspect/patch_knob.py).
export const KNOB_TURNS = [
  { name: "Knob clockwise", matrix: 75, turn: true },
  { name: "Knob counter-clockwise", matrix: 76, turn: true },
];

// Renders the keyboard. opts: { labelFor(key), colorFor(key), selected:Set, onClick(key) }
export function renderKeyboard(container, opts) {
  container.replaceChildren();
  container.classList.add("kb");
  for (const key of KEYS) {
    const [x1, y1, x2, y2] = key.rect;
    const el = document.createElement("button");
    el.type = "button";
    el.className = `kb-key${key.knob ? " kb-knob" : ""}${opts.selected?.has(key.matrix) ? " selected" : ""}`;
    Object.assign(el.style, {
      left: `${((x1 - X0) / W) * 100}%`, top: `${((y1 - Y0) / H) * 100}%`,
      width: `${((x2 - x1) / W) * 100}%`, height: `${((y2 - y1) / H) * 100}%`,
    });
    const color = opts.colorFor?.(key);
    if (color) {
      el.style.background = color;
      el.classList.add("colored");
      const [r, g, b] = [1, 3, 5].map((i) => Number.parseInt(color.slice(i, i + 2), 16));
      el.style.color = r * 0.3 + g * 0.6 + b * 0.1 > 140 ? "#111" : "#fff";
    }
    const label = opts.labelFor?.(key) ?? key.name;
    el.innerHTML = `<span>${escapeHtml(label)}</span>`;
    el.title = key.knob ? `Knob press: ${label}` : `${key.name}: ${label}`;
    el.addEventListener("click", () => opts.onClick?.(key));
    container.append(el);
  }
}

const escapeHtml = (s) => String(s).replace(/[&<>"]/g, (c) => ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;" })[c]);
