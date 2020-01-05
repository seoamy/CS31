//
//  main.cpp
//  project 3
//
//  Created by Amy Seo on 10/23/19.
//  Copyright © 2019 Amy Seo. All rights reserved.
//
#include "grid.h"
#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

const int HORIZ = 0;
const int VERT = 1;
const int FG = 0;
const int BG = 1;

int performCommands(string commandString, char& plotChar, int& mode, int& badPos);

// plots a horizontal line in the foreground
void plotHorizontalLine(int r, int c, int distance, char ch, int fb)
{
    // plotting with positive distance (to the right)
    if (distance >= 0)
    {
        for (int i = 0; i <= distance; i++)
        {
            if (c > getCols())
                break;
            
            // foreground printing
            if (fb == FG)
                setChar(r, c, ch);
            
            // background printing
            else
            {
                if (getChar(r, c) == ' ')
                    setChar(r, c, ch);
            }
            c++;
        }
    }
    
    // plotting with negative distance (to the left)
    else
    {
        for (int i = distance; i <= 0; i++)
        {
            if (c < 1)
                break;
            
            // foreground printing
            if (fb == FG)
                setChar(r, c, ch);
            
            // background printing
            else
            {
                if (getChar(r, c) == ' ')
                    setChar(r, c, ch);
            }
            c--;
        }
    }
}

void plotVerticalLine(int r, int c, int distance, char ch, int fb)
{
    // plotting line with positive distance (downwards)
    if (distance >= 0)
    {
        for (int i = 0; i <= distance; i++)
        {
            if (r > getRows())
                break;
            
            // foreground printing
            if (fb == FG)
                setChar(r, c, ch);
            
            // background printing
            else
            {
                if (getChar(r, c) == ' ')
                    setChar(r, c, ch);
            }
            r++;
        }
    }
    
    // plotting with negative distance (up)
    else
    {
        for (int i = distance; i <= 0; i++)
        {
            if (r < 1)
                break;
            
            // foreground printing
            if (fb == FG)
                setChar(r,c,ch);
            
            // background printing
            else
            {
                if (getChar(r, c) == ' ')
                    setChar(r, c, ch);
            }
            r--;
        }
    }
}

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg)
{
    int startRow = r;
    int startCol = c;
    const int MINROWS = 1;
    const int MINCOLS = 1;
    
    // testing if entered values are valid
    if ((dir != HORIZ && dir != VERT) || (fgbg != FG && fgbg != BG) || (!(isprint(plotChar))) || r < MINROWS || r > getRows() || c < MINCOLS || c > getCols())
        return false;

    // checking horizontal line
    if (dir == HORIZ)
    {
        // positive horizontal line
        if (distance >= 0)
        {
            for (int i = 0; i <= distance; i++)
            {
                if (c > getCols())
                    return false;
                
                c++;
            }
        }
        
        // negative horizontal line
        else
        {
            for (int i = distance; i <= 0; i++)
            {
                if (c < MINCOLS)
                    return false;
                
                c--;
            }
        }
        plotHorizontalLine(startRow, startCol, distance, plotChar, fgbg);
    }
    
    // checking a vertical line
    else
    {
        // positive vertical line
        if (distance >= 0)
        {
            for (int i = 0; i <= distance; i++)
            {
                if (r > getRows())
                    return false;
                r++;
            }
        }
        
        // negative vertical line
        else
        {
            for (int i = distance; i <= 0; i++)
            {
                // check if rows are out of bounds
                if (r < MINROWS)
                    return false;
                r--;
            }
        }
        plotVerticalLine(startRow, startCol, distance, plotChar, fgbg);
    }
    return true;
}

int convertDistanceToInt(string text, int& pos)
{
    int maxCommandLength;
    int convertedDistance = 1;
    int count = 0;
    string distance = "";
    pos++;
    
    if (text[pos] == '-')
        maxCommandLength = 3;
    else
        maxCommandLength = 2;
    
    // collects the distance value as a string
    do
    {
        distance += text[pos];
        pos++;
        count++;
    
    } while (isdigit(text[pos]) && count < maxCommandLength);
    
    // converts distance value to an int
    int m;
    if (distance[0] == '-')
        m = 1;
    else
        m = 0;
    
    for (int i = m; i < distance.size(); i++)
    {
        int b = distance[i] - '0';
        if (i > m)
            convertedDistance = convertedDistance * 10 + b;
        else
            convertedDistance = b;
    }
    
    if (distance[0] == '-')
        convertedDistance *= -1;
    
    return convertedDistance;
}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
    int rowCount = 1;
    int colCount = 1;
    int cDistance = 0;
    int k = 0;
    int syntaxError = 1;
    int outOfBoundsError = 2;
    
    // empty command string
    if (commandString == " " || commandString == "")
        return 0;
    
    // iterating through commandString with k as index
    while (k < commandString.size())
    {
        // invalid syntax, needs to start with a character
        if (!isalpha(commandString[k]))
        {
            badPos = k;
            return syntaxError;
        }
        
        // changes to foreground and the following plot character
        else if (commandString[k] == 'F' || commandString[k] == 'f')
        {
            mode = FG;
            k++;
            if (isprint(commandString[k]))
            {
                plotChar = commandString[k];
                k++;
            }
            
            else
            {
                badPos = k;
                return syntaxError;
            }
        }
        
        // changes to background and the following plot character
        else if (commandString[k] == 'B' || commandString[k] == 'b')
        {
            mode = BG;
            k++;
            if (isprint(commandString[k]))
            {
                plotChar = commandString[k];
                k++;
            }
            
            else
            {
                badPos = k;
                return syntaxError;
            }
        }
        
        // clear command
        else if (commandString[k] == 'c' || commandString[k] == 'C')
        {
            clearGrid();
            plotChar = '*';
            mode = FG;
            k++;
        }
        
        // horizontal and vertical line plotting
        else if (commandString[k] == 'h' || commandString[k] == 'H' || commandString[k] == 'v' || commandString[k] == 'V')
        {
            // retrieve direction
            int theDirection;
            if (commandString[k] == 'h' || commandString[k] == 'H')
                theDirection = HORIZ;
            else
                theDirection = VERT;
            
            // convert inputted distance into an int if next character is digit or negative sign
            if (isdigit(commandString[k+1]) || commandString[k+1] == '-')
                cDistance = convertDistanceToInt(commandString, k);
            
            else
            {
                k++;
                badPos = k;
                return syntaxError;
            }
        
            // check if distance is out of bounds vertically and horizontally in both negative and positve directions
            if (((theDirection == VERT) && ((cDistance > 0 && ((getRows() - rowCount) < cDistance)) || (cDistance < 0 && (rowCount < abs(cDistance))))) || (((theDirection == HORIZ) && ((cDistance > 0 && ((getCols() - colCount ) < cDistance)) || (cDistance < 0 && (colCount < abs(cDistance)))))))
            {
                // call performCommands to check if the rest of the string is syntatically correct before returning 2
                if (performCommands((commandString.substr(k, commandString.length() - 1)), plotChar, mode, badPos) == 1)
                {
                    badPos += k;
                    return syntaxError;
                }
                
                else
                {
                    k -=(to_string(cDistance).length() + 1);
                    badPos = k;
                    return outOfBoundsError;
                }
            }

            // use plotLine function to see if valid and if so, plot it
            if (plotLine(rowCount, colCount, cDistance, theDirection, plotChar, mode))
            {
                if (theDirection == HORIZ)
                    colCount += cDistance;
                else
                    rowCount += cDistance;
            }
            
            // if plotLine returns false, return 2 for inability to perform command
            else
            {
                badPos = k;
                return outOfBoundsError;
            }
        }
        
        else
        {
            badPos = k;
            return syntaxError;
        }
    }
    return 0;
}

int main()
{
    setSize(20, 30);
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = performCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
            case 0:
                draw();
                break;
            case 1:
                cout << "Syntax error at position " << position+1 << endl;
                break;
            case 2:
                cout << "Cannot perform command at position " << position+1 << endl;
                break;
            default:
                // It should be impossible to get here.
                cerr << "performCommands returned " << status << "!" << endl;
        }
    }
}
