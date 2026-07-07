# File Organizer

A command line C++ tool that automatically sorts files in a directory into subfolders based on their file extension. 

## What it does
- Scans a given directory (defaults to current working directory)
- Groups files by their extensions (.txt, .png, .cpp, etc)
- Creates subfolders for reach extension
- Moves files into their respective subfolders
- Supports a '--dry-run' flag to preview changes without moving anything

## How to build and run
bash
- g++ -std=c++17 -o file-organizer main.cpp
- ./file-organizer                             # sorts the currect directory
- ./file-organizer /path/to/folder             # sorts a specific directory
- ./file-organizer /path/to/folder --dry-run   # preview only
