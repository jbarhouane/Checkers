# PS4a: Checkers

## Contact
Name: Jessica Barhouane
Section: 11am
Time to Complete: 6 hours


## Description
Explain what the project does.
My program constructs a Checker board and places the pieces. It also has a red player indicator box and a screen at the bottom with "player 1" and "player 2" which highlights whose turn is next after a click.

### Features
Describe what your major decisions were and why you did things that way.
I decided to create a window at the bottom of the game that can indicate which player's turn it is, I did that because I will probably add something to tell how many pieces are left and it will say when the game is over and show the winner.

### Memory
Describe how you stored the game board including if you used smart pointers.
I created a rectangle shape array method that builds the board and returns the array, then created an sf::RectangleShape array in main set it equal to the method.

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
I learned how to to use global bounds, I had trouble with it in Sokoban. I learned more about how to control the mouse in an app. 
I got the mouse to select pieces and detect which pieces, but everytime a specific piece is clicked it prints out a lot of times to the screen instead of just once and when it's black's turn, red can still be clicked. 

### Extra Credit
Anything special you did.  This is required to earn bonus points.
I created a border and a display window with a player indicator that indicates which players turn it is after a click.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.
I looked up on stack overflow and sfml message boards and tutorial site on how to make a sprite clickable and use getGlobalBounds correctly. 
