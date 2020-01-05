//
//  main.cpp
//  proj5
//  Created by Amy Seo on 11/8/19.
//  Copyright © 2019 Amy Seo. All rights reserved.
//
#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <cstring>

using namespace std;

const char WORDFILENAME[] = "/Users/amyseo/Desktop/CS31/words.txt";
const int MAXWORDS = 9000;

int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum);
void flowers(char mysteryWord[], char testWord[]);

int main()
{
    // establishes wordList with words from textfile
    // sets n equal to the number of words in wordList
    char wordList[MAXWORDS][MAXWORDLEN + 1];
    int n = getWords(wordList, MAXWORDS, WORDFILENAME);
    double trialCount = 0.0;
    int min = 0;
    int max = 0;
    
    if (n < 1)
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return -1;
    }
    
    // get input for number of rounds
    cout << "How many rounds do you want to play? ";
    int nRounds;
    cin >> nRounds;
    cin.ignore(1000, '\n');
    cout << endl;
    
    // error if nRounds is negative
    if (nRounds < 0)
    {
        cout << "The number of rounds must be positive.";
        return -1;
    }

    // if number of rounds is positive, run a for loop for each round
    for (int i = 1; i <= nRounds; i++)
    {
        cout << "Round " << i << endl;
        
        // get random word from wordList
        int ran = randInt(0, n-1);
        char mystery[MAXWORDLEN + 1];
        strcpy(mystery, wordList[ran]);
                                                                                                                                             
        // length of word
        cout << "The mystery word is " << strlen(mystery) << " letters long." << endl;
        
        // run each round through this function and add to num of trials
        int nTrials = playOneRound(wordList, n, ran);
        trialCount += nTrials;
       
        // set min and max
        if (nTrials < min || i == 1)
            min = nTrials;
               
        if (nTrials > max)
            max = nTrials;
        
        // print statement for number of tries
        if (nTrials == 1)
            cout << "You got it in 1 try." << endl;
        
        else if (nTrials > 1)
            cout << "You got it in " << nTrials << " tries." << endl;
        
        double average = static_cast<double>(trialCount / i);
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Average: " << average << ", minimum: " << min << ", maximum: " << max << endl;
        cout << endl;
    }
}

// words[wordnum] is set as the mysteryword (not randomized)
int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum)
{
    if (nWords < 0 || wordnum < 0 || wordnum >= nWords)
        return -1;
    
    int numTrials = 0;
    char trialWord[MAXWORDLEN + 1] = "";
    
    // get the mystery word from the array
    char mysteryWord[MAXWORDLEN + 1];
    strcpy(mysteryWord, words[wordnum]);

    // while user keeps guessing
    while(strcmp(trialWord, mysteryWord) != 0)
    {
        // user input trial word
        cout << "Trial word: ";
        cin.getline(trialWord, 100);
       
        // check if trial word length is valid
        if (strlen(trialWord) > MAXWORDLEN || strlen(trialWord) < MINWORDLEN)
        {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
       
        // check if trial word is all lowercase
        bool isUpper = false;
        for (int i = 0; i < strlen(trialWord); i++)
        {
            if (isupper(trialWord[i]))
            {
                isUpper = true;
                cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
                break;
            }
        }
        
        if(isUpper)
            continue;
           
        // check if trial word is in word list
        int i = 0;
        bool checkList = true;
        while (i < nWords && checkList)
        {
            // if word is found, calculate flowers & bees
            if (strcmp(words[i], trialWord) == 0)
            {
                flowers(mysteryWord, trialWord);
                numTrials++;
                checkList = false;
            }
            
            else if (i == nWords - 1)
            {
                cout << "I don't know that word." << endl;
                checkList = false;
            }
            
            i++;
        }
    }
    return numTrials;
}

void flowers(char mysteryWord[], char testWord[])
{
    int flowerCount = 0;
    int beeCount = 0;
    int longerLength;
    int shorterLength;
    char longer[MAXWORDLEN + 1];
    char shorter[MAXWORDLEN + 1];

    // compare lengths of trialword and mysteryword and make copies of them
    if (strlen(mysteryWord) > strlen(testWord))
    {
        longerLength = strlen(mysteryWord);
        shorterLength = strlen(testWord);
        strcpy(longer, mysteryWord);
        strcpy(shorter, testWord);
    }
    
    else
    {
        longerLength = strlen(testWord);
        shorterLength = strlen(mysteryWord);
        strcpy(longer, testWord);
        strcpy(shorter, mysteryWord);
    }
    
    if (strcmp(longer, shorter) == 0)
        return;
           
    // check for flowers
    for (int i = 0; i < shorterLength; i++)
    {
        if (longer[i] == shorter[i])
        {
            // increment flower count and change character to uppercase
            // to prevent it from being used in a bee
            // can do this because longer and shorter are copies of the originals
            flowerCount++;
            longer[i] = toupper(longer[i]);
            shorter[i] = toupper(shorter[i]);
            continue;
        }
    }
    
    // check for bees
    // if characters are uppcase continue to next iteratation
    // because they have already been checked
    for (int j = 0; j < longerLength; j++)
    {
        if (isupper(longer[j]))
            continue;
        
        for (int k = 0; k < shorterLength; k++)
        {
            if (isupper(shorter[k]))
                continue;
            
            else if (longer[j] == shorter[k])
            {
                beeCount++;
                longer[j] = toupper(longer[j]);
                shorter[k] = toupper(shorter[k]);
                break;
            }
        }
    }
    cout << "Flowers: " << flowerCount << ", " << "Bees: " << beeCount << endl;
    return;
}
