# ZType — Type to Shoot

A C++ typing game developed as a University of Agder group project. Words move toward the player; typing their letters fires projectiles and clears targets. The implementation explores a game loop, state transitions, menus, levels, sound and a score display.

**DAT220 · Software Development 2 · Group 7 · December 2019 · C++14 / SFML**

[Read the report](docs/reports/ztype-dat220-report-2019.pdf) · [Source walkthrough](docs/architecture.md) · [Restore the original video and assets](archive/README.md)

## Repository guide

| Location | Contents |
|---|---|
| [src/ZType/](src/ZType) | Game source and project CMake file |
| [docs/reports/](docs/reports) | Original 55-page academic report |
| [docs/appendices/](docs/appendices) | Instructions for restoring submitted appendices |
| [archive/parts/](archive/parts) | Lossless parts of the complete original submission |
| [scripts/restore_assets.py](scripts/restore_assets.py) | Restore and verify original archive, game assets, appendices and video |
| [demos/](demos) | Original presentation video after restoration |

## Restore and build

The original video alone is 286 MB. The complete uploaded ZIP is retained as parts so its original bytes can be recovered without committing a single oversized file. Run from the repository root:

```sh
python3 scripts/restore_assets.py
cmake -S . -B build
cmake --build build
cd src/ZType
../../build/src/ZType/ZType
```

Use a C++14 compiler, CMake 3.14 or newer, and an **SFML 2.x** development installation. On Windows, the executable path depends on the generator and configuration. Run it with `src/ZType` as the working directory because assets are loaded by relative path. The official [SFML 2.6 tutorials](https://www.sfml-dev.org/tutorials/2.6/) explain toolchain setup.

The archive was restored and its checksum verified during cleanup. CMake/SFML were unavailable in this environment, so the game was not compiled or played. The original source references `source/image/image2.jpg`, which was not supplied; the affected level screen needs review. See the [implementation notes](docs/architecture.md).

## Authors and inspiration

**Filmon Berhe · Iyad Zidan · Mohamed Ali Abdullahi · Yeronis Assefa Hubena**

Supervisor: **Christian Auby**, University of Agder. The report describes inspiration from Dominic Szablewski's ZTYPE. Group credits and the original report bibliography are retained. No new license or ownership claim is asserted for bundled fonts, sounds or images.
