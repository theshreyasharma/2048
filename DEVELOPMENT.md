# Development

---

- **4/17/20** - Set up Cinder project, imported external library [Box2D](https://github.com/sansumbrella/suBox2D).
    - [x] Show working example
    - [x] Update project proposal with library switch
    - [x] Organize project structure for 2048
    
- **4/20/20** - Imported gflags library.
    - No longer using Box2D, I can accomplish everything with use of Cinder libraries.
    - Decided on class structure and decided functionality of classes.
    - [x] Show working example of gflags
    - [x] Set up game board display

- **4/21/20** - Planned graphics setup
    - Office hours was unable to help me with my issue the last 2 days, so my progress has stalled.
    - Updated project proposal
    - Created functions for drawing background and gameboard
    - Set up example of Box2D working
    - [x] Find out what is causing issue with drawing shapes
    - [x] Create classes and begin game implementation

- **4/22/20** - Set up database, update external library, create database classes
    - Set up database using sqlite
    - Remove Box2d from my library and CMake files
    - [x] Update project proposal and readme with *final* choice of external library (sqlite3)
    - [x] Begin drafting Block class
    - [x] Decide color palettes for light and dark mode
    
- **4/23/20** - Created gameboard and block classes
    - Implemented functions that draw the block objects
    - Added some functions to header
    - [x] Implement game logic
    - [ ] Decide on dark mode palette
    
- **4/24/20** - Began implementing game logic
    - Created adding new tile function and find empty tile functions
    - Added game state enum
    - Implemented functions to move the blocks on the board left and up
    - [x] Figure out logic to merge rows and columns when a button is pressed
    - [x] Winner and loser logic with leaderboard
    - [x] isGameOver logic (is board full and not mergable with no 2048 block, is there a 2048 block, is there a valid move even if board is full)
    - [x] Update score variable
    
- **4/26/20** - Finished game logic mostly, have to include GameOver logic
    - Implemented MoveRight and MoveDown functions
    - Moved score variable from my_app class to gameboard class
    - [x] Implement GameOver logic
    - [x] Fix incorrect merging (might have to do with row/col being greater than the target)
    
- **4/27/20** - Added tests for gameboard and block classes
    - Implemented operator overload for == to check whether a valid move was made
    - Did half of the game over logic, have to add to leaderboard now
    - [x] Add to leaderboard when game is over
    - [ ] Dark mode palette
    - [x] Add more tests
    - [ ] Add timer functionality and music
    - [ ] Update README.md with proper formatting
    - [ ] Make gameboard look better
    
- **4/28/20** - Finished tests for gameboard and block classes
    - Add scores to leaderboard when game is over
    - Wrote game over logic with a enum
    
       