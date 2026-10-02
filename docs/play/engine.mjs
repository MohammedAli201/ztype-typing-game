import { SHIP, targetPosition, advanceShot } from './physics.mjs';
export const WORDS = {
  english: 'orbit star moon light sky comet solar nova pulse drift spark cloud river green blue amber bright quiet dream night space speed focus calm brave clear earth flame frost glide hello journey learn meteor ocean planet quick rocket silver signal smooth steady storm stream sunrise swift trail travel world'.split(' '),
  norwegian: 'måne stjerne sol lys himmel nord vind hav snø skog fjell elv blå grønn rød gul rolig rask modig klar drøm natt rom fart fokus hei reise lære verden venn hjem varme vinter sommer høst vår strøm bølge hjerte glede morgen kveld flyte regn sky tenke skrive øve'.split(' '),
  coding: 'const let return function import export class async await promise array object string number boolean null true false map filter reduce sort find push pop shift slice split join parse fetch try catch throw loop while break switch case index value key state event render test debug build code module scope'.split(' '),
};

export class Game {
  constructor({ language = 'english', mode = 'arcade', random = Math.random } = {}) {
    this.language = Object.hasOwn(WORDS, language) ? language : 'english';
    this.mode = mode === 'focus' ? 'focus' : 'arcade';
    this.random = random;
    this.status = 'ready'; this.elapsed = 0; this.duration = 60;
    this.targets = []; this.nextId = 0; this.lock = null; this.spawnClock = 0;
    this.correct = 0; this.attempts = 0; this.cleared = 0; this.missed = 0;
    this.streak = 0; this.bestStreak = 0; this.score = 0; this.lives = 5;
    this.shots = []; this.impacts = []; this.nextShot = 0; this.aim = { ...SHIP, y: 0 };
  }
  get level() { return 1 + Math.floor(this.elapsed / 15); }
  get accuracy() { return this.attempts ? Math.round(100 * this.correct / this.attempts) : 100; }
  get wpm() { return this.elapsed > 0 ? Math.round(this.correct * 12 / this.elapsed) : 0; }
  start() { if (this.status !== 'ready') return; this.status = 'running'; this.spawn(); }
  pause() { if (this.status === 'running') this.status = 'paused'; }
  resume() { if (this.status === 'paused') this.status = 'running'; }
  spawn() {
    if (this.targets.length >= 5) return;
    const occupied = new Set(this.targets.map(t => t.lane));
    const lanes = [0, 1, 2, 3, 4].filter(lane => !occupied.has(lane));
    const words = WORDS[this.language].filter(word => !this.targets.some(t => t.word[0] === word[0]));
    const word = words[Math.min(words.length - 1, Math.floor(this.random() * words.length))];
    const lane = lanes[Math.min(lanes.length - 1, Math.floor(this.random() * lanes.length))];
    this.targets.push({ id: ++this.nextId, word, typed: 0, hits: 0, completed: false, lane, y: 0 });
  }
  tick(seconds) {
    if (this.status !== 'running' || !Number.isFinite(seconds) || seconds <= 0) return;
    const dt = Math.min(seconds, this.duration - this.elapsed);
    this.elapsed += dt;
    if (this.mode === 'arcade') {
      for (const target of this.targets) {
        target.y += dt / (20 - this.level * 2);
        // A fully typed word is secured; let the last shots finish it visibly.
        if (target.completed) target.y = Math.min(.98, target.y);
      }
      const escaped = this.targets.filter(target => target.y >= 1);
      for (const target of escaped) {
        this.lives--; this.missed++; this.streak = 0;
        if (this.lock === target.id) this.lock = null;
      }
      this.targets = this.targets.filter(target => target.y < 1);
      this.spawnClock += dt;
      const interval = Math.max(1.3, 3.5 - this.level * .45);
      if (this.spawnClock >= interval) { this.spawnClock %= interval; this.spawn(); }
    }
    this.impacts = this.impacts.map(effect => ({ ...effect, age: effect.age + dt })).filter(effect => effect.age < .45);
    const survivingShots = [];
    for (const shot of this.shots) {
      const target = this.targets.find(t => t.id === shot.targetId);
      if (!target) continue;
      const position = targetPosition(target, this.mode);
      if (advanceShot(shot, position, dt)) {
        target.hits++;
        const destroyed = target.completed && target.hits === target.word.length;
        this.impacts.push({ id: shot.id, ...position, age: 0, destroyed });
        if (destroyed) this.targets = this.targets.filter(t => t.id !== target.id);
      } else survivingShots.push(shot);
    }
    this.shots = survivingShots;
    const aimed = this.targets.find(t => t.id === this.lock) || this.targets.find(t => t.id === this.shots.at(-1)?.targetId);
    if (aimed) this.aim = targetPosition(aimed, this.mode);
    if (!this.targets.length) this.spawn();
    if (this.elapsed >= this.duration || this.lives <= 0) this.status = 'finished';
  }
  type(character) {
    if (this.status !== 'running' || [...character].length !== 1 || !/^[a-zæøå]$/i.test(character)) return 'ignored';
    character = character.toLowerCase();
    // A completed Focus word waits briefly for impact; don't penalize extra keys.
    if (!this.targets.some(t => !t.completed)) return 'ignored';
    this.attempts++;
    let target = this.targets.find(t => t.id === this.lock);
    if (!target) target = [...this.targets].filter(t => !t.completed).sort((a, b) => b.y - a.y).find(t => t.word[0] === character);
    if (!target || target.word[target.typed] !== character) { this.streak = 0; return 'error'; }
    this.lock = target.id; target.typed++; this.correct++; this.streak++;
    this.bestStreak = Math.max(this.bestStreak, this.streak);
    this.score += 10;
    this.aim = targetPosition(target, this.mode);
    this.shots.push({ id: ++this.nextShot, targetId: target.id, ...SHIP, vx: 0, vy: -850 });
    if (target.typed === target.word.length) {
      this.score += 50; this.cleared++; this.lock = null;
      target.completed = true;
      if (this.mode === 'arcade' && !this.targets.some(t => !t.completed)) this.spawn();
      return 'cleared';
    }
    return 'hit';
  }
  result() {
    return { language: this.language, mode: this.mode, wpm: this.wpm, accuracy: this.accuracy,
      score: this.score, cleared: this.cleared, missed: this.missed, bestStreak: this.bestStreak,
      seconds: Math.round(this.elapsed), completed: this.elapsed >= this.duration };
  }
}

export function readHistory(storage) {
  try {
    const rows = JSON.parse(storage.getItem('ztype.progress.v1') || '[]');
    if (!Array.isArray(rows)) return [];
    return rows.filter(r => r && Object.hasOwn(WORDS, r.language) && ['arcade', 'focus'].includes(r.mode)
      && ['wpm', 'accuracy', 'score', 'cleared', 'missed', 'bestStreak', 'seconds', 'date'].every(k => Number.isFinite(r[k]) && r[k] >= 0)
      && r.accuracy <= 100 && r.seconds <= 60 && typeof r.completed === 'boolean').slice(0, 30);
  } catch { return []; }
}
export function saveResult(storage, history, result) {
  const rows = [{ ...result, date: Date.now() }, ...history].slice(0, 30);
  try { storage.setItem('ztype.progress.v1', JSON.stringify(rows)); return { rows, saved: true }; }
  catch { return { rows, saved: false }; }
}
