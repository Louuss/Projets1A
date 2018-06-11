# PROJECT FACTORY

## Project organisation

-   All the game sources are in the 'src' folder. In this folder you'll find:

    -   The 'main.rkt', containing the functions you need to launch the game
    -   The 'gen.rkt', containing the basic functions needed in every strategies
    -   The 'parser.rkt', containing the functions needed to parse your input file
    -   A bunch of strategies that we implemented, you can add yours too.

-   The 'tst' folder contains a file testing the main's functions, and one testing the parser's functions. You'll also find some input files, used to test and launch the game.

If you want to write your input file make sure it follows the same syntax as the one already written:

**[inputRessource=number] --> [output1=number,output2=number] cost = yourCost**


## How to launch the game

To launch the game you have to use the function **'resultat'** from the 'main.rkt' with as parameters/
-   The function containing your strategy
-   The nulber of gold you have at the beggining
-   The number of turns you'll play
-   the .txt file containing the input file


## How does the parser work

The parser has two main functions:

-   The first is "(create-list filepath)", it takes a string containing the filepath of your init file and returns a list of all the ressources. Notice that gold will always be first

-   The second method you have to use is "(factorisation filepath)", it takes a string containing the filepath of your init file and returns a list of all your factories ready to be used.


**The parser is already used in the main function, you won't need to use it directly**
