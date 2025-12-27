# ♟️ Professional Chess Engine (C & SDL2)

![Alexandria University](https://img.shields.io/badge/University-Alexandria-blue)
![Faculty](https://img.shields.io/badge/Faculty-Engineering-green)
![Course](https://img.shields.io/badge/Course-CSE212:_Programming_I-red)

A robust, cross-platform Chess application representing a sophisticated fusion of a high-performance logical engine and a modern graphical interface. Engineered from the ground up to ensure 100% FIDE rule compliance.

---

## 👥 Prepared By
* **Mohamed Saber Abaas Elsayed** (ID: 24010617)
* **Fares Tahseen Mohamed Nageeb** (ID: 24010493)
* *Under the supervision of Alexandria University, Faculty of Engineering.*

---

## 🚀 Key Technical Features

### 1. 🧠 Core Logic & Game Physics (board.c)
* **FIDE Compliance:** Full implementation of **Castling**, **En Passant**, and **Pawn Promotion**.
* **Movement Engine:** Uses a **Directional Vector Algorithm** for sliding pieces and pre-computed offset arrays for Knights.
* **Virtual Simulation:** A "Look-ahead" layer that clones the board using `malloc` to validate moves and prevent illegal King exposure (Pinned pieces logic).
* **State Detection:** Advanced logic for **Checkmate**, **Stalemate**, **Insufficient Material**, and **Threefold Repetition**.

### 2. 🎨 Graphical User Interface (main.c & SDL2)
* **High-Res Rendering:** Optimized pipeline using SDL2 for sub-pixel precision textures.
* **Visual Feedback:** Dynamic translucent Green overlays to highlight legal moves.
* **Auditory Experience:** Integrated `SDL_mixer` for distinct acoustic signatures (moves, checks, captures, and illegal moves).
* **Material Tracking:** Sidebars to monitor captured pieces and material advantage in real-time.

### 3. 💾 Persistence & Standardization (file.c)
* **FEN Engine:** Complete support for **Forsyth-Edwards Notation** (FEN) for game serialization.
* **Secure Storage:** Robust I/O system with automated naming to prevent data overwriting and syntax validation for loaded files.

---

## 🛠️ Data Architecture
The engine is built on a modular three-layer architecture as defined in `board.h`:
* **Atomic Layer:** Individual piece history and state tracking (`has_moved`).
* **Entity Layer:** Player-specific data and cached King positions for $O(1)$ check detection.
* **Global Layer:** The "Single Source of Truth" board state, synchronizing the logical grid with the SDL2 graphical grid.

---

## ⚙️ Installation & How to Run

This project uses a structured **GNU Makefile** for automated compilation.

```bash
# 1. Clean previous builds
make clean

# 2. Compile the project
make

# 3. Run the engine
./chess
