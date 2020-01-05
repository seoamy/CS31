# CS31
My projects for CS31 - Introduction to Computer Science 1 - Fall 2019

Here are the condensed versions of the specs to provide context into each project's code.

# Project 1
The purpose of this assignment was to start learning how to use the g++ and the Xcode environment and understand a variety of programming errors.

1. Obtain a copy of Xcode and install it.

2. Enter this given C++ program into your development environment. Do not change the program:

  // Code for Project 1
	// Report poll results
	
	#include <iostream>
	using namespace std;   // pp. 38-39 in Savitch 6/e explains this line
	
	int main()
	{
	    int numberSurveyed;
	    int forImpeachment;
	    int antiImpeachment;
	
	    cout << "How many people were surveyed? ";
	    cin >> numberSurveyed;
	    cout << "How many of them support impeachment of the president? ";
	    cin >> forImpeachment;
	    cout << "How many of them oppose impeachment of the president? ";
	    cin >> antiImpeachment;
	
	    double pctFor = 100.0 * forImpeachment / numberSurveyed;
	    double pctAnti = 100.0 * antiImpeachment / numberSurveyed;

	    cout.setf(ios::fixed);       // see pp. 32-33 in Savitch 6/e
	    cout.precision(1);
	
	    cout << endl;
	    cout << pctFor << "% say they support impeachment." << endl;
	    cout << pctAnti << "% say they oppose impeachment." << endl;

	    if (forImpeachment > antiImpeachment)
	        cout << "More people support impeachment than oppose it." << endl;
	    else
	        cout << "More people oppose impeachment than support it." << endl;
	}

3. Build the executable from the program. (Fix any typos you may have made when entering the program.)

4. Execute the program with a variety of reasonable input integers to see if it runs as one would expect from reading the source code. 

5. Using the program as given, without changing it in any way, run it with input integers that cause it to produce incorrect, unusual, or nonsensical output. (Notice we're saying to try input integers, not input like 124765.23 or Article II section 4.)

6. Starting from the program as given, introduce into the source code at least one error that someone might make that, while not preventing a successful build, causes the program when it runs to produce incorrect results from reasonable input.

7. Again starting from the program as given, introduce at least two distinct types of mistakes that someone might make, each of which would cause the program to fail to compile correctly.

You should create a separate project for each of steps 2, 6, and 7, since you're not allowed to have multiple files in the same project if more than one has a main routine.

# Project 2
The federal judge in the college admissions scandal has devised a formula for determining a suggested amount for the fine to be imposed on a defendant convicted of fraud in the scandal. The amount of the fine depends on the amount the defendant paid to Slick Stinger, who arranged for cheating on the SAT or ACT or for faking athletic competition credentials, the latter being a more serious offense that should be penalized more. The job of writing the program that implements the formula has come to you.

Your program must accept as input the name of the defendant, the amount the defendant paid Stinger to facilitate cheating (in thousands), and whether or not the fraud involved faking athletic achievement.

Here is an example of a dialog with the program (user input is shown in boldface):

	Defendant: Horton Lapland
	Amount paid (in thousands): 75
	Fake athlete? (y/n): n
	---
	The suggested fine for Horton Lapland is $49.9 thousand.
According to the fine formula:

The base amount of the fine is $20 thousand.
For up to the first $40 thousand paid to Stinger, 66% of that amount is added to the fine.
In addition, for up to the next $210 thousand paid (beyond the initial $40 thousand), the fine will be increased by of 10% of that additional amount paid. However, if athletic achievement was faked, the addition to the fine will be 22% of that additional amount paid instead of 10%.
In addition, a further fine will be imposed in the amount of 14% of the amount paid to Stinger above $250 thousand.
As an example, the suggested fine for Horton Lapland above would be the $20 thousand base amount, plus $26.4 thousand for the first $40 thousand paid, plus $3.5 thousand for the next $35 thousand paid (10% of $35 thousand instead of 22%, since there was no athletic fakery), for a total suggested fine of $49.9 thousand.

Here's another example:

	Defendant: Duplicity Muffin
	Amount paid (in thousands): 15
	Fake athlete? (y/n): n
	---
	The suggested fine for Duplicity Muffin is $29.9 thousand.
  
  # Project 3
  You have been hired by Twisted Plots to write a program allowing an artist to draw lines to produce amazing computer graphics. The software works by having the artist type a series of drawing commands that dictate what lines it should plot on the screen.

The display grid of the system is comprised of "pixels" and is 20 pixels high by 30 pixels wide (pixel stands for "picture element"). The pixel in the upper left corner of the grid is considered to be at row 1, column 1. The pixel in the bottom right corner of the grid is at row 20, column 30. This image shows the grid and illustrates several coordinates:

                  111111111122222222223
         123456789012345678901234567890
        +------------------------------+
       1|A                            C|    A is at (1,1)
       2|  B                           |    B is at (2,3)
       3|                              |    C is at (1,30)
       4|                              |    D is at (7,11)
       5|                              |    E is at (19,28)
       6|                              |    F is at (20,1)
       7|          D                   |    G is at (20,30)
       8|                              |
       9|                              |
      10|                              |
      11|                              |
      12|                              |
      13|                              |
      14|                              |
      15|                              |
      16|                              |
      17|                              |
      18|                              |
      19|                           E  |
      20|F                            G|
        +------------------------------+
        
1. Write the line plotting function:

          const int HORIZ = 0;
          const int VERT = 1;
          const int FG = 0;
          const int BG = 1;
          bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);
    
  The dir value is either HORIZ or VERT (i.e., either 0 or 1).
  The fgbg value is either FG or BG (i.e., either 0 or 1).
  Every position of the line to be plotted must be within the grid.
  The plotChar must be a character for which the library function isprint returns a value that tests as true (i.e. if (isprint(that character)) would select the true branch of the if statement). isprint is declared in the header <cctype>, and returns an integer that tests as true for any "printable" character (letters, digits, punctuation, and the space character), and an integer that tests as false for any other character.
  If the function does not succeed (i.e., at least one of the above conditions doesn't hold), then it must not modify any characters in the grid.
  
  2. Write the command string interpreter
  The final version of the program will repeatedly:
    Prompt the user for a command string, which is a line of text containing a sequence of plotting commands.
    Read a command string.
    If the command string is the empty string, terminate the program. Otherwise, for each plotting command in the command string, perform the action specified by that plotting command.
    After all the plotting commands in the command string have been performed, draw the resulting grid.

When the program starts, the current character is * and the current mode is foreground mode. This can be changed by a plotting command described below. For each command string, the current position is set to row 1, column 1 of the grid, and then the plotting commands in the command string are performed. Plotting commands in the command string will cause the current position to change as the virtual pen moves as it plots draw lines.

Here is an example of a command string, one that contains five plotting commands:

	h12V3H-1B@v-3
Each plotting command starts with a single letter indicating the action to perform (e.g, H or h to draw a horizontal line). (The action is the same whether the letter is upper or lower case.) Following the letter is the argument to that command. (The argument for each command are described later.) Arguments that are numbers are written with a possible minus sign character (-) followed by exactly one or two digits. The command string above contains the five plotting commands:

	h12
	V3
	H-1
	B@
	v-3

 # Project 4
 Here are the functions to implement:

    int appendToAll(string a[], int n, string value);
Append value to the end of each of the n elements of the array and return n. [Of course, in this and other functions, if n is negative, the paragraph above that starts "Notwithstanding" trumps this by requiring that the function return −1. Also, in the description of this function and the others, when we say "the array", we mean the n elements that the function is aware of.] For example:
  
    int lookup(const string a[], int n, string target);
Return the position of a string in the array that is equal to target; if there is more than one such string, return the smallest position number of such a matching string. Return −1 if there is no such string. As noted above, case matters: Do not consider "RUdy" to be equal to "rUdY". Here's an example:

    int positionOfMax(const string a[], int n);
Return the position of a string in the array such that that string is >= every string in the array. If there is more than one such string, return the smallest position number of such a string. Return −1 if the array has no interesting elements. For example:

    int rotateLeft(string a[], int n, int pos);
Eliminate the item at position pos by copying all elements after it one place to the left. Put the item that was thus eliminated into the last position that was copied from. Return the original position of the item that was moved to the end. Here's an example:
  
    int countRuns(const string a[], int n);
Return the number of sequences of one or more consecutive identical items in a.

    int flip(string a[], int n);
Reverse the order of the elements of the array and return n. 

    int differ(const string a1[], int n1, const string a2[], int n2);
Return the position of the first corresponding elements of a1 and a2 that are not equal. n1 is the number of interesting elements in a1, and n2 is the number of interesting elements in a2. If the arrays are equal up to the point where one or both runs out, return whichever value of n1 and n2 is less than or equal to the other. For example,

    int lookupAny(const string a1[], int n1, const string a2[], int n2);
Return the smallest position in a1 of an element that is equal to any of the n2 elements in a2. Return −1 if no element of a1 is equal to any element of a2. For example,

    int separate(string a[], int n, string separator);
Rearrange the elements of the array so that all the elements whose value is < separator come before all the other elements, and all the elements whose value is > separator come after all the other elements. Return the position of the first element that, after the rearrangement, is not < separator, or n if there are no such elements. For example,

# Project 5
You have been hired to write a program that plays the Flowers and Bees word guessing game. Here's how one round of the game works: The computer picks a mystery word of four to six letters and tells the player how many letters are in the word. The player tries to determine the mystery word by presenting the computer with a series of trial words. Each trial word is a four to six letter word. If the trial word is the mystery word, the player wins. Otherwise, the computer responds to the trial word with two integers: the number of flowers and the number of bees. Flowers and bees are pairings between a letter in the trial word and the same letter in the mystery word:

A flower is a pairing of a letter in the trial word and the same letter in the mystery word in the same position. For example, if the mystery word is EGRET and the trial word is AGATE, there's one flower: The Gs in both words are in the same position, the second letter.

A bee is a pairing between a letter in the trial word and the same letter in the mystery word, but not in the same position as in the trial word, provided that neither of the two letters are involved in a flower or another bee. For example, if the mystery and trial words are EGRET and AGATE, the Ts form a bee, since we can pair them up but they're not in the same position, since one is the fifth letter of EGRET and the other is the fourth letter of AGATE. The E in AGATE and, say, the first E in EGRET can be paired up to form another bee; the second E in EGRET would then not be part of a bee — we can't pair it up with the E in AGATE because that E is already paired up with the first E in EGRET. If instead we paired the E in AGATE with the second E in EGRET, then the first E in EGRET would have to remain unpaired.

If a letter at a particular position in a word could be considered part of a flower or part of a bee, it must be treated as part of a flower. For example, if the mystery and trial words were EGRET and VIXEN, the E in VIXEN must be paired up with the second E in EGRET to form a flower; that takes priority over pairing it with the first E in EGRET to form a bee.

The player's score for each round is the number of trial words needed to determine the correct word (counting the trial word that matched the mystery word).
  
Your program must ask the player how many rounds to play, and then play that many rounds of the game. After each round, the program must display some statistics about how well the player has played the rounds so far: the average score, the minimum score, and the maximum score.

# Project 6
This project is designed to help you master pointers. To that end, you'll get the most out of it by working through the problems by hand. Only after that should you resort to running the programs (and stepping through them with the debugger) to check your understanding. Remember, on the final exam you'll have to be able to do problems like this by hand.

This "project" is more like a homework. There are five problems. In problems that ask you to change code, make the few changes necessary to fix the code without changing its overall approach. 

# Project 7
Your assignment is to complete this C++ program skeleton to produce a program that implements the described behavior.The program skeleton you are to flesh out defines four classes that represent the four kinds of objects this program works with: Game, Arena, Vampire, and Player.  

1. Game

      To create a Game, you specify a number of rows and columns and the number of vampires to start with. The Game object creates an appropriately sized Arena and populates it with the Player and the Vampires.
      A game may be played.

2. Arena

      When an Arena object of a particular size is created, it has no positions occupied by vampires or the player. In the Arena coordinate system, row 1, column 1 is the upper-left-most position that can be occupied by a vampire or the player. If an Arena created with 10 rows and 20 columns, then the lower-right-most position that could be occupied would be row 10, column 20.
      You may tell an Arena object to put a poisoned blood vial at a particular position.
      You may ask an Arena object whether there's a poisoned blood vial at a particular position.
      You may tell an Arena object to create a Vampire at a particular position.
      You may tell an Arena object to create a Player at a particular position.
      You may tell an Arena object to have all the vampires in it make their move.
      You may ask an Arena object its size, how many vampires are at a particular position, and how many vampires altogether are in the Arena.
      You may ask an Arena object for access to its player.
      An Arena object may be displayed on the screen, showing the locations of the vampires, the player, and the poisoned blood vials, along with other status information.

3. Player

      A Player is created at some position (using the Arena coordinate system, where row 1, column 1 is the upper-left-most position, etc.).
      You may tell a Player to move in a direction or to drop a poisoned blood vial.
      You may tell a Player that it has died.
      You may ask a Player for its position and its alive/dead status.

4. Vampire

      A Vampire is created at some position.
      You may tell a Vampire to move.
      You may ask a Vampire object for its position and its alive/dead status.

At each turn the player may take one of these actions:
Move one step north, east, south, or west, and do not drop a poisoned blood vial. If the player attempts to move out of the arena (e.g., south, when on the bottom row), the player does not move, and does not drop a vial. If the player moves to a grid point currently occupied by a vampire, the player dies.
Do not move, but attempt to drop a vial of poisoned blood. If there is already a vial of poisoned blood at that grid point, no additional vial is dropped; a grid point may have at most one vial of poisoned blood. The player has an unlimited supply of poisoned blood vials.
The game allows the user to select the player's action: n/e/s/w for movement, or x for dropping a poisoned blood vial. The user may also just hit enter to have the computer select the player's move.

After the player moves, it's the vampires' turn. Each vampire has an opportunity to move. A vampire that has previously drunk a vial of poisoned blood will not move if it attempted to move on the previous turn. Otherwise, it will pick a random direction (north, east, south, west) with equal probability. The vampire moves one step in that direction if it can; if the vampire attempts to move off the grid, however, it does not move (but this still counts as a poisoned vampire's attempt to move, so it won't move on the next turn). More than one vampire may occupy the same grid point; in that case, instead of V, the display will show a digit character indicating the number of vampires at that point (where 9 indicates 9 or more).

If after a vampire moves, it occupies the same grid point as the player (whether or not there's a vial of poisoned blood at that point), the player dies. If the vampire lands on a grid point with a poisoned blood vial on it, it drinks all the blood in the vial (and the vial is no longer part of the game). If this is the second vial of poisoned blood the vampire has drunk, it dies. If more than one vampire lands on a spot that started the turn with a poisoned blood vial on it, only one of them drinks the vial of poisoned blood.



