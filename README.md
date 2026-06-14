# 🚀 Space Shooter

A 2D arcade-style space shooter game built with **C++** and **SFML**. Survive waves of alien invaders, rack up your score, and level up before they reach you!

---

## 🎮 Gameplay

- Move your rocket **left/right** with arrow keys
- Press **Space** to shoot bullets
- Destroy enemies to earn points and level up
- Watch out for the **red danger enemy** — it's faster and worth more points!
- You have **3 lives** — don't let enemies slip past you
- Reach **Level 5** to win!

---

## 🕹️ Controls

| Key | Action |
|-----|--------|
| `←` Left Arrow | Move rocket left |
| `→` Right Arrow | Move rocket right |
| `Space` | Shoot bullet |

---

## 📊 Scoring

| Enemy | Points |
|-------|--------|
| Regular enemy (green) | +5 |
| Danger enemy (red/yellow) | +15 |

Every **50 points**, you level up — enemies get faster!

---

## 🏗️ Build Instructions

### Requirements
- [SFML 2.x](https://www.sfml-dev.org/download.php)
- A C++ compiler (g++, MSVC, clang++)

### Windows (g++ with MinGW)

```bash
g++ main.cpp -o SpaceShooter -lsfml-graphics -lsfml-window -lsfml-system
```

### Linux

```bash
sudo apt install libsfml-dev
g++ main.cpp -o SpaceShooter -lsfml-graphics -lsfml-window -lsfml-system
```

### Run the game

Make sure the executable is in the **same folder** as the `assets/` directory, then run:

```bash
./SpaceShooter
```

---

## 📁 Project Structure

```
SpaceShooter/
├── main.cpp
├── assets/
│   ├── background.jpg
│   ├── startBackground.jpg
│   ├── rocket.png
│   ├── enemy.png
│   ├── enemyRed.png
│   ├── bullet.png
│   └── Battle-Tough.otf
└── README.md
```

---

## 🛠️ Built With

- **C++** — Game logic
- **SFML** — Graphics, window, and input handling

---

## 📸 Screenshots

(assets/spaceshooter.png)

---

## 👤 Author

Made for SFML learning.
