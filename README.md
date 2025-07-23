<<<<<<< HEAD
# Raylib Tetris

A polished, customizable Tetris clone built using [Raylib](https://www.raylib.com/) in C++. Designed as a learning project to explore graphics programming, state machines, object-oriented design, and game development fundamentals.

## 🎮 Features

- ✅ Smooth block movement and rotation
- ✅ Pause and resume with `P`
- ✅ Game Over and Restart functionality
- ✅ High score saved to file (`highscore.txt`)
- ✅ Glowing blocks using sinusoidal color effects
- ✅ Difficulty levels (Easy, Medium, Hard)
- ✅ Clean UI with shadowed text and rounded panels

## 🧱 Technologies Used

- **C++**
- **Raylib** (2D game development library)
- Standard C++ file I/O
- Custom state management

## 🚀 Controls

| Key        | Action              |
|------------|---------------------|
| ← / →      | Move block          |
| ↓          | Drop block faster   |
| ↑          | Rotate block        |
| `P`        | Pause / Resume      |
| `ENTER`    | Start / Restart     |
| `1/2/3`    | Select difficulty   |
| `Q`        | Quit game           |

## 🏁 Getting Started

### 🔧 Prerequisites

- C++ compiler (e.g., g++, clang++)
- [Raylib installed](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)
- Git (optional for cloning)

### 🛠️ Build

```bash
g++ main.cpp game.cpp grid.cpp block.cpp blocks.cpp colors.cpp position.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o tetris
=======
# 2203175-Tetris
🎮 A feature-rich Tetris clone built with Raylib in C++. Includes level selection, glowing blocks, score tracking, pause functionality, and persistent high score saving.
>>>>>>> fca0b62200e665b05a7f32b4500d95bd91acc80e
