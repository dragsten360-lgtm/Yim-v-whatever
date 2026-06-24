# idk

This repository contains a small web page and a simple Python paddle game.

## Included game
- `game.py` — a basic paddle game built with Pygame
- `requirements.txt` — lists the dependency needed to run the game locally

## Run locally
1. Install dependencies:
   ```bash
   python3 -m pip install -r requirements.txt
   ```
2. Run the game:
   ```bash
   python3 game.py
   ```

## Package into an executable
If you want a Windows `.exe`, install PyInstaller and run:
```bash
python3 -m pip install pyinstaller
python3 -m pyinstaller --onefile game.py
```
The executable will appear in `dist/game.exe` (Windows) or `dist/game` (Linux/macOS).
