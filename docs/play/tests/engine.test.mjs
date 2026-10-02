import test from 'node:test';
import assert from 'node:assert/strict';
import { Game, WORDS, readHistory, saveResult } from '../engine.mjs';
const create = options => { const game = new Game({ random: () => 0, ...options }); game.start(); return game; };

test('typing locks a target, mistakes do not advance it, completion awards score', () => {
  const g = create(); const word = g.targets[0].word;
  assert.equal(g.type(word[0]), 'hit');
  assert.equal(g.type('z'), 'error'); assert.equal(g.targets[0].typed, 1);
  for (const char of word.slice(1)) g.type(char);
  assert.equal(g.cleared, 1); assert.equal(g.lock, null);
  assert.equal(g.score, word.length * 10 + 50);
  assert.equal(g.accuracy, Math.round(word.length / (word.length + 1) * 100));
});
test('paused time and typing cannot change results; resume continues', () => {
  const g = create(); g.tick(5); g.pause(); const snapshot = JSON.stringify(g);
  g.tick(20); g.type('o'); assert.equal(JSON.stringify(g), snapshot);
  g.resume(); g.tick(2); assert.equal(g.elapsed, 7);
});
test('full minute finishes exactly once and freezes subsequent input', () => {
  const g = create({ mode: 'focus' }); g.type('o'); g.tick(75);
  assert.equal(g.elapsed, 60); assert.equal(g.status, 'finished'); assert.equal(g.result().completed, true);
  const correct = g.correct; g.type('r'); g.tick(1); assert.equal(g.correct, correct); assert.equal(g.elapsed, 60);
});
test('Focus retains one stationary target and shields', () => {
  const g = create({ mode: 'focus' }); g.tick(50);
  assert.equal(g.targets.length, 1); assert.equal(g.targets[0].y, 0); assert.equal(g.lives, 5);
  for (const c of g.targets[0].word) g.type(c);
  assert.equal(g.targets.length, 1); assert.equal(g.cleared, 1);
});
test('escaping target loses a shield and releases target lock', () => {
  const g = create(); g.type(g.targets[0].word[0]); g.targets[0].y = .99; g.tick(1);
  assert.equal(g.lives, 4); assert.equal(g.missed, 1); assert.equal(g.lock, null); assert.equal(g.streak, 0);
});
test('five escaped targets end Orbit before the minute', () => {
  const g = create(); for (let i = 0; i < 4; i++) g.spawn();
  g.targets.forEach(t => t.y = .99); g.tick(1);
  assert.equal(g.status, 'finished'); assert.equal(g.lives, 0); assert.equal(g.result().completed, false);
});
test('spawns have distinct lanes and initial letters; population is bounded', () => {
  const g = create(); for (let i = 0; i < 20; i++) g.spawn();
  assert.equal(g.targets.length, 5);
  assert.equal(new Set(g.targets.map(t => t.lane)).size, 5);
  assert.equal(new Set(g.targets.map(t => t.word[0])).size, 5);
});
test('Norwegian accepts composed letters and uppercase input', () => {
  const g = create({ language: 'norwegian' }); assert.equal(g.targets[0].word, 'måne');
  for (const c of 'MÅNE') g.type(c);
  assert.equal(g.cleared, 1); assert.equal(g.accuracy, 100);
});
test('WPM is correct characters divided by five per active minute', () => {
  const g = create({ mode: 'focus' }); for (const c of 'orbit') g.type(c); g.tick(30);
  assert.equal(g.wpm, 2); g.pause(); g.tick(30); assert.equal(g.wpm, 2);
});
test('invalid config, ignored keys, invalid time cannot corrupt session', () => {
  const g = create({ language: '__proto__', mode: 'bad' }); assert.equal(g.language, 'english');
  for (const key of ['Enter', ' ', '1']) assert.equal(g.type(key), 'ignored');
  for (const dt of [NaN, Infinity, -1]) g.tick(dt);
  assert.equal(g.elapsed, 0); assert.equal(g.attempts, 0);
  for (const words of Object.values(WORDS)) assert.ok(words.every(w => /^[a-zæøå]+$/.test(w)));
});
test('storage rejects malformed data, handles failure, and keeps last 30', () => {
  assert.deepEqual(readHistory({ getItem: () => '{oops' }), []);
  assert.deepEqual(readHistory({ getItem: () => '[null,{}, {"language":"__proto__"}]' }), []);
  assert.deepEqual(readHistory({ getItem() { throw Error(); } }), []);
  let data; const storage = { setItem(k, v) { data = v; }, getItem() { return data; } };
  const result = create().result(); let rows = [];
  for (let i = 0; i < 35; i++) rows = saveResult(storage, rows, result).rows;
  assert.equal(readHistory(storage).length, 30);
  assert.equal(saveResult({ setItem() { throw Error(); } }, [], result).saved, false);
});
