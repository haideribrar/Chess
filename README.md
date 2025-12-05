# Chess 

A complete chess game built in C++ using SFML, featuring fully implemented logic for piece movement, turn handling, legal move generation, check, checkmate, stalemate, promotions, capturing, and a drag-and-drop GUI.

This project is designed with simplicity and minimal dependencies, using only:
- iostream  
- string  
- SFML (Simple and Fast Multimedia Library)

------------------------------------------------------------

## Features

### Complete Chess Mechanics
- All legal moves for King, Queen, Rook, Bishop, Knight, Pawn  
- Turn-based system (White moves first)  
- Check detection  
- Checkmate detection  
- Stalemate detection  
- Capturing pieces  
- Pawn promotion (Queen, Rook, Bishop, Knight)

### Drag & Drop Interface
- Grab pieces with the mouse  
- Highlights all legal squares  
- Smooth drag-and-drop movement  

### SFML GUI
- Fully drawn chessboard  
- Piece rendering using textures  
- Promotion UI with 4 selectable pieces  
- Captured pieces displayed on screen  

### Pure C++ 
- No external logic files  
- Simple and clean implementation  
- Suitable for academic restrictions

------------------------------------------------------------

## Project Structure

main.cpp  
resources/  
    pieces/ (piece textures)  
    board/  (optional board textures)

main.cpp contains:
- Board representation  
- Move generation  
- Drag & drop handling  
- Rendering  
- Promotion system  
- Checkmate / stalemate logic  
- Sprite management  

Everything is implemented inside one file.

------------------------------------------------------------

## Requirements

### SFML 2.5 or newer

Install SFML:

Windows (MinGW / MSVC): download from the official site:  
https://www.sfml-dev.org/download.php

------------------------------------------------------------

## How to Play

- Left-click a piece to select it  
- Drag it to move  
- Legal moves are highlighted  
- Release to place the piece  
- Promotion window appears automatically when needed  
- Game ends on checkmate or stalemate  

------------------------------------------------------------

## Limitations

- No castling yet  
- No en passant  
- No AI (player vs player only)  
- No timers  
- No undo/redo  
- No sound  

------------------------------------------------------------

## Future Improvements

- Add AI using Minimax  
- Add castling and en passant  
- Add move history  
- Add sound effects  
- Add menu and settings  
- Add themes / board styles  

------------------------------------------------------------

## Author

Made by Haider  
A clean, simple, SFML-based chess program written fully from scratch.
