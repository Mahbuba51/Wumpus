# Wumpus World

## Overview

Wumpus World is a grid-based game where the player navigates a 4x4 grid to find the hidden gold while avoiding the dangers of encountering the Wumpus or falling into a Pit. The objective of the game is to locate the gold and successfully return to the starting position.

## Game Elements

1. **Grid**: The game takes place on a 4x4 grid, with each cell identified by its row and column coordinates ranging from [0,0] to [3,3].

2. **Wumpus**: The Wumpus is a dangerous creature that inhabits one of the cells on the grid. It emits a foul odor that can be detected when the player is adjacent to its cell.

3. **Pit**: There is a single Pit located in one of the cells on the grid. Falling into the Pit results in the player losing the game. A breeze can be felt when the player is adjacent to the Pit.

4. **Gold**: The gold is hidden in one of the cells on the grid. The player must locate the gold and return to the starting position while avoiding the Wumpus and Pit.

## Player Actions

The player has the following actions to navigate the grid:

1. **Turn Right**: Changes the direction of movement to the right.
2. **Turn Left**: Changes the direction of movement to the left.
3. **Move Forward**: Moves the player to the next cell in the current direction.
4. **Shoot**: The player can use one of their three arrows to shoot in the current direction. If the Wumpus is in the targeted cell, it is killed.
