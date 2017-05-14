Motif/Xlib/Python program

The program creates a Motif interface to allows the user to simultaneously draw figures in both Xlib  & Python.

Each figure is composed of three concentric shapes:  a circle C and  two pentagons P1 and P2.

    A figure is drawn by clicking twice at two different points’ X and Y:
·        The center of all shape is X.
·        C radios is the distance between X and Y.
·        P1 five edges touches C.
·        P2 five corners touches C.

The color of the center and all shapes borders is black.

The three shapes are filled with three different randomly selected colors from the set:
{red, green, blue, yellow, white, pink, brown, purple, gray, orange }
 
Typing the character “c” inside the drawing canvas clears it.

open xterm and type
./ccp
