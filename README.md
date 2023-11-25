# Snake Game in C++

## Introduction
This is a simple console-based Snake game implemented in C++. The game utilizes the Windows Console API for handling console operations. The snake moves in the console window, and the player controls its direction using the 'W', 'A', 'S', and 'D' keys. The goal is to eat the randomly placed food to grow the snake and earn points. The game ends if the snake collides with itself or the walls.

## Features
- **Difficulty Levels:** The game offers three difficulty levels - easy, medium, and difficult. The speed of the snake varies based on the selected level.
- **Score Display:** The current score is displayed at the top of the console window during gameplay.
- **Game Over Screen:** When the game ends, a Game Over screen is displayed, showing the player's final score and offering the option to play again.

## Instructions
1. Run the program.
2. Choose a difficulty level (1 for easy, 2 for medium, 3 for difficult) to start the game.
3. Control the snake using 'W' (up), 'A' (left), 'S' (down), and 'D' (right) keys.
4. Eat the food ('@') to grow the snake and increase your score.
5. The game ends if the snake collides with itself or the walls.
6. After the game ends, you can choose to play again ('y') or exit the program ('n').

## Controls
- **W:** Move the snake up.
- **A:** Move the snake left.
- **S:** Move the snake down.
- **D:** Move the snake right.
- **Y:** Play again after Game Over.
- **N:** Exit the program after Game Over.

## Files
- **menu.txt:** Text file containing the game menu.
- **help.txt:** Text file containing instructions and help for the game.

## Code Structure
- **snake:** Class encapsulating the game logic and state.
  - **menu():** Display the game menu.
  - **help():** Display the help instructions.
  - **draw():** Draw the snake and display the current score.
  - **drawWall():** Draw the game walls.
  - **insert(int x, int y):** Insert a new segment into the snake.
  - **drawfood(int x):** Draw the food at a random location.
  - **move():** Move the snake based on the current direction.
  - **collision():** Check for collisions with walls, snake body, and food.
  - **gameOver():** Display the Game Over screen and handle replay or exit.
  - **resetGame():** Reset the game state to its initial conditions.
  - **startGame():** Start the game by displaying the menu and handling user input.
- **loop(snake &ob):** Main game loop where the actual gameplay takes place.
- **main():** Entry point of the program, initializes the game and handles menu choices.

## Compilation
This program can be compiled using a C++ compiler compatible with the Windows Console API. Use an integrated development environment (IDE) or a command-line compiler to build and run the executable.

Feel free to explore and modify the code to enhance the game or add new features!