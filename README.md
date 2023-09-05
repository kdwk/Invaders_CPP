# Invaders_CPP 
A terminal mini-game in which you have to shoot down a horde of invaders with your starship.

![Screenshot from 2023-05-05 15-24-36](https://user-images.githubusercontent.com/39268094/236399174-e76186be-286a-45a0-a561-bc8b2c0a3fa3.png)

## Description & Rules
In this game, you must control a starship to shoot down a horde of invaders that keep advancing.

1. The starship can only move left and right on the bottom of the screen
2. The starship can fire three shots at the same time, it cannot fire while it is moving
3. The invaders will descend by a row every time they have moved horizontally across the screen and touched one of the edges
4. Every time the invaders descend by a row, they will move faster
5. If the invaders reach the bottom of the screen, you lose
6. If you can kill all invaders before they reach your starship, you win
7. There are four levels of difficulty to choose from. The author does not guarantee that the 'extreme' level can be won

## Features
1. Greeting page with ASCII art and rules

![Screenshot from 2023-05-05 15-44-27](https://user-images.githubusercontent.com/39268094/236402819-eb90c288-c3ca-4d6d-8f71-66713a6901d5.png)

2. 4 levels of difficulty, with corresponding numbers of invaders and their initial speed

![Screenshot from 2023-05-05 15-47-12](https://user-images.githubusercontent.com/39268094/236403354-5a9a9029-d3e7-45d2-a622-db0be2490ebf.png)

3. Keyboard controls

    3.1 Left/ right to control the starship
  
    3.2 Space to shoot
  
    3.3 P to pause, any key to resume, Q to quit

4. Leaderboard to record who can eliminate the invaders quickest. To use the leaderboard, leaderboard.txt must be placed in the working directory. The program will create a new one if leaderboard.txt is not present

![Screenshot from 2023-05-06 11-11-05](https://user-images.githubusercontent.com/39268094/236595690-cbabd982-ed89-44d0-b05b-133aff6f87fd.png)

## Technical features
1. Generation of random game sets or events: the initial positions of each invader are randomly generated within an area
2. Data structures for storing game status: the program makes use of various enums, structs and classes to store the states of objects like invaders and player as well as global game statuses like level of difficulty, pause, continue, win and lose. The code then dynamically responds to changes in these statuses
3. Dynamic memory management: the program makes heavy use of STL containers like vectors to store lists of items, including a list of shots for the player and a list of invaders for the army
4. File input/output: used to write to the leaderboard
5. Program codes in multiple files: classes and related enums are separated from main.cpp in their respective source and header files. The additional lib.h and lib.cpp declares and defines values, enums and functions used throughout the game
6. A Frame class is used for all drawable classes to perform client-side drawing on. The player, shot and invader objects get passed a reference to a frame, which they then draw themselves on. The frame is then rendered on screen as a whole, instead of each object manipulating the screen directly
7. The ncurses library is used for rendering, screen manipulation and input. This presents multiple advantages: there is no flicker thanks to the buffer-flushing mechanism (the screen is not updated until refresh() is called), the screen can be manipulated with a coordinate system, and non-blocking input can be achieved by setting a timeout on get-character operations. Besides, the cursor can be hidden and shown wherever appropriate
8. Timers are achieved by comparing UNIX timestamps. This bypasses the trouble of compensating for putting the thread to sleep
9. A secret test mode for developmental purposes

## Non-standard libraries
This program uses <bits/stdc++.h> for convenience. Users must use g++ for compilation.

This program uses <ncurses.h>. The program is linked to ncurses at compilation. The package libncurses6 (Debian and derivatives) or ncurses-lib must be installed, as is the case on HKU CS Academy servers by default. If not using the HKU CS Academy servers, I recommend running the latest release of Ubuntu or Fedora in Windows Subsystem for Linux or a Podman/ Docker container. The package is installed by default on both operating systems.

## Compilation instructions
You can use the pre-built binaries in GitHub Actions -> most recent workflow run -> 'invaders' artifact. You can also compile with the following instructions:

1. `git clone https://github.com/kdwk/Invaders_CPP.git`
2. `cd Invaders_CPP`
3. `make clean`
4. `make invaders`
5. `./invaders` to execute the binary
