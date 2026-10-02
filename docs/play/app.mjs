import { Game, readHistory, saveResult } from './engine.mjs?v=0.2.0';
const $ = id => document.getElementById(id);
const names = { english: 'English', norwegian: 'Norsk', coding: 'Code' };
let storage;
try { storage = window.localStorage; } catch { storage = { getItem() { return null; }, setItem() { throw Error('Unavailable'); }, removeItem() { throw Error('Unavailable'); } }; }
let history = readHistory(storage), game = new Game(), lastFrame = 0, sound = false, audio, errorTimeout;
const nodes = new Map();
const reducedMotion = matchMedia('(prefers-reduced-motion: reduce)');
const svgNS = 'http://www.w3.org/2000/svg';
function shape(tag, attributes) {
  const node = document.createElementNS(svgNS, tag);
  for (const [name, value] of Object.entries(attributes)) node.setAttribute(name, value);
  return node;
}
function renderCombat() {
  const fragments = document.createDocumentFragment();
  for (const shot of game.shots) {
    if (reducedMotion.matches) continue;
    const length = Math.hypot(shot.vx, shot.vy) || 1;
    fragments.append(shape('line', { x1: shot.x - shot.vx / length * 18, y1: shot.y - shot.vy / length * 18, x2: shot.x, y2: shot.y, class: 'laser' }));
  }
  for (const hit of game.impacts) {
    const progress = hit.age / .45;
    fragments.append(shape('circle', { cx: hit.x, cy: hit.y, r: reducedMotion.matches ? 14 : 5 + progress * (hit.destroyed ? 42 : 18), opacity: 1 - progress, class: hit.destroyed ? 'impact destruction' : 'impact' }));
    if (hit.destroyed && !reducedMotion.matches) for (let i = 0; i < 8; i++) {
      const angle = i * Math.PI / 4, radius = 8 + progress * 48;
      fragments.append(shape('circle', { cx: hit.x + Math.cos(angle) * radius, cy: hit.y + Math.sin(angle) * radius, r: 2 * (1 - progress), opacity: 1 - progress, class: 'spark' }));
    }
  }
  $('combat').replaceChildren(fragments);
  const angle = Math.atan2(game.aim.y - 368, game.aim.x - 400) * 180 / Math.PI + 90;
  document.querySelector('.ship').style.transform = `translate(-50%, -50%) rotate(${reducedMotion.matches ? 0 : angle}deg)`;
}
if (matchMedia('(prefers-reduced-motion: reduce)').matches) document.querySelector('[value="focus"]').checked = true;
function settings() { return { language: $('language').value, mode: document.querySelector('[name="mode"]:checked').value }; }
function announce(text) { $('announcement').textContent = text; }
function tone(frequency, duration = .06) {
  if (!sound) return;
  try {
    audio ??= new (window.AudioContext || window.webkitAudioContext)();
    if (audio.state === 'suspended') audio.resume().catch(() => {});
    const oscillator = audio.createOscillator(), gain = audio.createGain();
    oscillator.type = 'sine'; oscillator.frequency.value = frequency;
    gain.gain.setValueAtTime(.035, audio.currentTime);
    gain.gain.exponentialRampToValueAtTime(.001, audio.currentTime + duration);
    oscillator.connect(gain); gain.connect(audio.destination);
    oscillator.start(); oscillator.stop(audio.currentTime + duration);
  } catch { sound = false; $('sound').textContent = 'Sound unavailable'; $('sound').setAttribute('aria-pressed', 'false'); }
}
function updateProgress() {
  const selected = settings();
  if (game.status === 'ready' || game.status === 'finished') {
    $('overlay-copy').textContent = selected.mode === 'focus' ? 'One word at a time, without moving targets. Type at your own pace for one minute.' : 'Type a word’s first letter to lock on. Each correct letter fires a tracking shot. Finish the word before it reaches your ship.';
    document.querySelector('.hint').textContent = selected.mode === 'focus' ? '60 seconds · still words · no lost shields' : '60 seconds · 5 shields · find your rhythm';
  }
  const matching = history.filter(r => r.language === selected.language && r.mode === selected.mode && r.completed);
  $('best').textContent = matching.length ? Math.max(...matching.map(r => r.wpm)) : '—';
  $('best-caption').textContent = matching.length ? `${names[selected.language]} · ${selected.mode === 'focus' ? 'Focus' : 'Orbit'} · best of saved full-minute sessions` : 'Complete a full minute to set your best.';
  $('sessions').textContent = history.length;
  $('history').replaceChildren();
  for (const row of history.slice(0, 5)) {
    const tr = document.createElement('tr');
    const date = new Date(row.date).toLocaleDateString(undefined, { month: 'short', day: 'numeric' });
    for (const text of [`${date} · ${row.seconds}s`, `${names[row.language]} / ${row.mode === 'focus' ? 'Focus' : 'Orbit'}`, `${row.wpm} WPM`, `${row.accuracy}%`, row.score.toLocaleString()]) {
      const td = document.createElement('td'); td.textContent = text; tr.append(td);
    }
    $('history').append(tr);
  }
  $('history-table').hidden = !history.length; $('empty-history').hidden = !!history.length;
  $('clear-history').disabled = !history.length;
}
function render() {
  $('time').textContent = `${Math.ceil(Math.max(0, 60 - game.elapsed))}s`;
  $('wpm').textContent = game.elapsed >= 1 ? game.wpm : 0;
  $('accuracy').textContent = game.attempts ? `${game.accuracy}%` : '—';
  $('score').textContent = game.score.toLocaleString();
  $('sector').textContent = game.mode === 'focus' ? 'FOCUS / NO PRESSURE' : `SECTOR 0${game.level}`;
  $('shields').textContent = game.mode === 'focus' ? 'ONE WORD AT A TIME' : `${Math.max(0, game.lives)} SHIELDS`;
  const activeIds = new Set(game.targets.map(t => t.id));
  for (const [id, node] of nodes) if (!activeIds.has(id)) { node.remove(); nodes.delete(id); }
  for (const target of game.targets) {
    let node = nodes.get(target.id);
    if (!node) { node = document.createElement('div'); node.append(document.createElement('span'), document.createElement('span')); node.firstChild.className = 'typed'; $('targets').append(node); nodes.set(target.id, node); }
    node.className = `target${target.completed ? ' secured' : ''}${game.lock === target.id ? ' locked' : ''}${game.mode === 'focus' ? ' focus-target' : ''}`;
    node.style.left = game.mode === 'focus' ? '50%' : `${10 + target.lane * 20}%`;
    node.style.top = game.mode === 'focus' ? '48%' : `${16 + target.y * 68}%`;
    node.firstChild.textContent = target.word.slice(0, target.typed); node.lastChild.textContent = target.word.slice(target.typed);
  }
  renderCombat();
}
function announceTarget() {
  const target = game.targets.find(t => t.id === game.lock) || game.targets[0];
  if (target && game.mode === 'focus') announce(`Word: ${target.word}`);
}
function start() {
  game = new Game(settings()); nodes.forEach(node => node.remove()); nodes.clear();
  game.start(); lastFrame = performance.now();
  $('overlay').hidden = true; $('typing').disabled = false; $('typing').value = '';
  $('typing').placeholder = 'Type the words above…'; $('pause').disabled = false; $('pause').textContent = 'Pause'; $('restart').disabled = false;
  $('language').disabled = true; document.querySelectorAll('[name="mode"]').forEach(el => el.disabled = true);
  $('typing').focus(); announce(game.mode === 'focus' ? `Word: ${game.targets[0].word}` : 'Session started. Type a target word.'); render();
}
function pause() {
  if (game.status !== 'running') return;
  game.pause(); $('overlay').hidden = false; $('overlay-title').textContent = 'Take a breath.';
  $('overlay-copy').textContent = 'Your session is paused. Pick up where you left off.';
  $('start').textContent = 'Resume session ↗'; $('pause').textContent = 'Resume'; $('typing').disabled = true;
  $('start').focus(); announce('Session paused.');
}
function resume() {
  game.resume(); lastFrame = performance.now(); $('overlay').hidden = true;
  $('typing').disabled = false; $('typing').focus(); $('pause').textContent = 'Pause'; announceTarget();
}
function finish() {
  $('typing').disabled = true; $('pause').disabled = true; $('restart').disabled = true;
  $('language').disabled = false; document.querySelectorAll('[name="mode"]').forEach(el => el.disabled = false);
  const result = game.result();
  const saved = saveResult(storage, history, result); history = saved.rows;
  if (!saved.saved) $('storage-note').textContent = 'Browser storage is unavailable. Progress lasts only while this page stays open.';
  updateProgress();
  $('result-title').textContent = result.completed ? 'Nice flying.' : 'Every flight is practice.';
  $('result-copy').textContent = result.completed ? 'One minute invested in a better rhythm.' : 'Your shields ran out. Try Focus for a calmer session.';
  $('result-wpm').textContent = result.wpm; $('result-accuracy').textContent = `${result.accuracy}%`;
  $('result-cleared').textContent = result.cleared;
  $('result-detail').textContent = `${result.score.toLocaleString()} points · ${result.bestStreak} correct letters in your best streak · ${result.seconds}s played`;
  $('results').showModal(); tone(660, .15); announce('Session complete. Results are open.');
}
function dashboard() {
  $('overlay').hidden = false; $('overlay-title').textContent = 'Ready for another flight?';
  $('overlay-copy').textContent = 'Small steps add up. Choose your next word collection and go again.';
  $('start').textContent = 'Start session ↗'; $('start').focus();
}
function frame(now) {
  if (game.status === 'running') {
    const dt = Math.max(0, (now - lastFrame) / 1000);
    // Freeze after a suspended/blocked frame rather than charging unseen time.
    if (dt > 1) pause();
    else {
      const previousTarget = game.targets[0]?.id;
      game.tick(dt); render();
      if (game.mode === 'focus' && game.targets[0]?.id !== previousTarget) announceTarget();
      if (game.status === 'finished') finish();
    }
  }
  lastFrame = now; requestAnimationFrame(frame);
}
$('start').addEventListener('click', () => game.status === 'paused' ? resume() : start());
$('restart').addEventListener('click', start);
$('pause').addEventListener('click', () => game.status === 'paused' ? resume() : pause());
$('typing').addEventListener('input', event => {
  if (event.isComposing) return;
  const value = $('typing').value.normalize('NFC'); $('typing').value = '';
  for (const letter of value) {
    const outcome = game.type(letter);
    if (outcome === 'error') { tone(120); $('arena').classList.add('error'); clearTimeout(errorTimeout); errorTimeout = setTimeout(() => $('arena').classList.remove('error'), 160); }
    else if (outcome !== 'ignored') { tone(outcome === 'cleared' ? 620 : 420); if (outcome === 'cleared') announceTarget(); }
  }
  render();
});
$('typing').addEventListener('paste', event => event.preventDefault());
$('typing').addEventListener('drop', event => event.preventDefault());
document.addEventListener('keydown', event => {
  if (event.key === 'Escape' && !$('results').open && !$('clear-dialog').open && ['running', 'paused'].includes(game.status)) {
    event.preventDefault(); game.status === 'running' ? pause() : resume();
  }
});
document.addEventListener('visibilitychange', () => { if (document.hidden) pause(); });
window.addEventListener('blur', pause);
$('sound').addEventListener('click', () => { sound = !sound; $('sound').setAttribute('aria-pressed', String(sound)); $('sound').textContent = sound ? 'Sound on' : 'Sound off'; tone(440); });
$('results').addEventListener('close', () => { const action = $('results').returnValue; $('results').returnValue = ''; action === 'again' ? start() : dashboard(); });
$('results').addEventListener('cancel', () => { $('results').returnValue = 'close'; });
$('clear-history').addEventListener('click', () => { if (game.status === 'running') pause(); $('clear-dialog').showModal(); });
$('clear-dialog').addEventListener('close', () => {
  if ($('clear-dialog').returnValue === 'clear') {
    try { storage.removeItem('ztype.progress.v1'); history = []; updateProgress(); announce('Progress cleared.'); }
    catch { $('storage-note').textContent = 'Could not clear browser storage. Check your browser privacy settings.'; }
  }
  $('clear-dialog').returnValue = '';
});
$('language').addEventListener('change', updateProgress);
document.querySelectorAll('[name="mode"]').forEach(el => el.addEventListener('change', updateProgress));
updateProgress(); requestAnimationFrame(frame);
