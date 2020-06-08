# Development

---

## Week 1
### 6/1/2020
- Created json file to represent the board(may change layout later)
- Created Board and Tile class to read and access json information
### 6/2/2020
- Added gflags and setup to run.cc to allow user to submit name, speed, file, 
whether to collect $200 when passing go, and number of CPUs
### 6/5/2020
- Created Property class that inherits from Tile
- Add property tiles to vector of all tiles
- Draw property tiles on bottom row of board
### 6/6/2020
- Created Utility class that also inherits from Tile
- Added logic to draw all tile outlines and print names and prices
    - [ ] Add property colors and images to other tiles
### 6/7/2020
- Created Player class to hold user info