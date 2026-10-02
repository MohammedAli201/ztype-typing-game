# ZType Lab — browser MVP

A new, dependency-free browser implementation of the typing-shooter concept. This is an early product prototype, not a port of the original C++ engine. Original source, academic report, archive, and author credits remain intact in the parent repository. The browser UI uses CSS, system fonts, and synthesized audio; no original third-party images or sound files are reused.

[Play the live browser MVP](https://mohammedali201.github.io/ztype-typing-game/play/)

## Run

From the repository root:

```sh
python3 -m http.server 8080 --directory docs/play
```

Open http://localhost:8080 in a modern browser. ES modules require HTTP; opening `index.html` directly as a file is not supported. No install or build step is needed.

## Play

- Choose English, Norwegian, or code vocabulary. Code mode practices words, not syntax or punctuation.
- **Orbit:** type the first letter of a visible word to lock onto it, then finish it. Five missed targets end the session; speed increases every 15 seconds.
- **Focus:** one stationary word at a time, without shield losses. This is the default for people requesting reduced motion. Target words are announced to assistive technology in this mode.
- Every session lasts up to 60 active seconds. Escape or the Pause button pauses/resumes. Restart begins a fresh attempt without saving the unfinished session. Switching tabs or windows automatically pauses; resuming is explicit.
- A mistake counts against accuracy but does not advance the target. Spaces, punctuation, modifiers, and backspace are ignored. Pasting and dropping text into the typing field are blocked.
- Optional synthesized sound starts off. Standard buttons and settings support keyboard navigation. The input supports touch keyboards, though a physical keyboard is recommended for Orbit.

## Shooting and motion

Each correct letter fires a visible homing shot from the ship to its word. The ship turns toward the target; impacts produce rings and sparks. Completed words stay visible until their final impact. [Read the vector mathematics and collision rules](PHYSICS.md).

## Results and privacy

WPM = correct letters / 5 / active minutes, including correctly typed partial words. Accuracy = correct letters / attempted letters. Scores award 10 points per correct letter and 50 per cleared word. Speed from a short session is noisy, so personal bests only compare completed 60-second sessions with the same collection and style.

Up to 30 sessions are saved in browser `localStorage`; five appear in the table. Personal bests apply to these retained sessions, not an unlimited lifetime history. There is no backend, account, analytics, or network dependency. Clear history asks for confirmation. When storage is blocked, the game still works and reports that progress is temporary. Scores are client-side practice metrics, not cheat-resistant leaderboard records.

## Verify

```sh
node --test docs/play/tests/*.test.mjs
node --check docs/play/app.mjs
```

The pure game engine is separated from rendering to test target locking, mistakes, Norwegian input, timing, shield loss, scoring, and persistence without a browser. Manual release checks: play both modes, switch collections, finish a full session, exhaust shields, pause/resume, switch tabs, reload saved history, clear history, toggle sound, and check narrow screens and a screen reader. Automated engine tests do not replace these checks.

## Product scope

This MVP establishes the play–results–practice loop. Before calling it production-ready, run cross-browser and assistive-technology testing, gather feedback from real players, tune the difficulty and vocabulary, and choose an original public brand after checking name rights. The historical project was inspired by Dominic Szablewski’s ZTYPE; this prototype is not affiliated with that game. Accounts, shared leaderboards, payments, and multiplayer are outside this release.
