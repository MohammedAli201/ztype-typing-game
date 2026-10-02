import test from 'node:test';
import assert from 'node:assert/strict';
import { advanceShot, targetPosition } from '../physics.mjs';
import { Game } from '../engine.mjs';

test('unit-vector velocity has constant magnitude and follows a moving destination', () => {
  const shot = { x: 0, y: 0 };
  advanceShot(shot, { x: 300, y: 400 }, .1, 100);
  assert.equal(shot.x, 6); assert.equal(shot.y, 8);
  assert.equal(Math.hypot(shot.vx, shot.vy), 100);
  advanceShot(shot, { x: -300, y: 400 }, .1, 100);
  assert.ok(shot.vx < 0); assert.ok(shot.vy > 0);
});
test('travel is frame-rate independent for a fixed target', () => {
  const a = { x: 0, y: 0 }, b = { x: 0, y: 0 }, target = { x: 1000, y: 0 };
  for (let i = 0; i < 60; i++) advanceShot(a, target, 1 / 60, 100);
  for (let i = 0; i < 30; i++) advanceShot(b, target, 1 / 30, 100);
  assert.ok(Math.abs(a.x - b.x) < 1e-9);
});
test('collision clamps overshoot and coincident points avoid division by zero', () => {
  const shot = { x: 0, y: 0 };
  assert.equal(advanceShot(shot, { x: 20, y: 0 }, 1), true);
  assert.equal(shot.x, 8);
  assert.equal(advanceShot(shot, { ...shot }, .1), true);
  assert.ok(Number.isFinite(shot.x));
});
test('correct letters fire, wrong letters do not, and destruction waits for impact', () => {
  const g = new Game({ random: () => 0, mode: 'focus' }); g.start();
  const target = g.targets[0]; g.type('z'); assert.equal(g.shots.length, 0);
  for (const letter of target.word) g.type(letter);
  assert.equal(g.shots.length, target.word.length); assert.equal(target.completed, true);
  assert.ok(g.targets.includes(target)); assert.equal(g.type('o'), 'ignored');
  g.tick(.3);
  assert.ok(!g.targets.includes(target)); assert.equal(g.shots.length, 0);
  assert.equal(g.targets.length, 1); assert.ok(g.impacts.some(hit => hit.destroyed));
});
test('shots track their own target after the typing lock switches', () => {
  const g = new Game({ random: () => 0 }); g.start(); const first = g.targets[0];
  for (const letter of first.word) g.type(letter);
  const second = g.targets.find(t => !t.completed); g.type(second.word[0]);
  assert.equal(g.lock, second.id);
  assert.equal(g.shots[0].targetId, first.id); assert.equal(g.shots.at(-1).targetId, second.id);
  g.tick(.1); assert.ok(g.shots.every(s => Number.isFinite(s.x) && Number.isFinite(s.y)));
  assert.deepEqual(g.aim, targetPosition(second, g.mode));
});
test('pause freezes shots; escaped targets cancel their remaining shots', () => {
  const g = new Game({ random: () => 0 }); g.start(); g.type('o'); g.tick(.01); g.pause();
  const position = { ...g.shots[0] }; g.tick(1); assert.deepEqual(g.shots[0], position);
  g.resume(); g.targets[0].y = .999; g.tick(.1); assert.equal(g.shots.length, 0);
});
test('impact particles expire and new sessions contain no old shots', () => {
  const g = new Game({ random: () => 0, mode: 'focus' }); g.start(); g.type('o'); g.tick(.3);
  assert.ok(g.impacts.length); g.tick(.5); assert.equal(g.impacts.length, 0);
  assert.equal(new Game().shots.length, 0);
});
