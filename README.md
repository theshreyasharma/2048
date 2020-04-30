# 2048

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Shreya Sharma - [`ssharm90@illinois.edu`](mailto:ssharm90@illinois.edu)

#### The classic 2048 game as a cinder app

## How to run the game
### Dependencies needed:
    - CLion
    - Cinder Framework
### External Libraries needed: 
    - gflags
    - sqlite3


## Game
### How to play
The goal is to reach the 2048 tile by combining like tiles. Each turn, a new block with the value 2 appears in a random space. When you combine tiles by shifting the board in any direction, blocks with the same value merge and double in value. Don't let the board fill up. Your score increases by the value of each combined tile during each move. 
### About
This game was originally created by a 19 year old named Gabriele Cirulli in 2014 and has been expanded to several different platforms since then due to its extreme popularity.
### Controls
#### Play
Key|Action
---|------
<kbd>Up</kbd>|Slide the board upwards
<kbd>Down</kbd>|Slide the board downwards
<kbd>Left</kbd>|Slide the board to the left
<kbd>Right</kbd>|Slide the board to the right

#### Other
Key|Action
---|------
<kbd>m</kbd>|Toggle between light and dark mode
<kbd>q</kbd>|Forfeit the current game
    
## Original Project Proposal
Can be found [here](https://github.com/CS126SP20/project-proposal-ssharm90#2048).
