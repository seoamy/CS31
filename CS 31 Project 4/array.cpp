//
//  main.cpp
//  proj 4
//
//  Created by Amy Seo on 11/2/19.
//  Copyright © 2019 Amy Seo. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;


// appends value to n elements in the array
int appendToAll(string a[], int n, string value)
{
    if (n < 0)
        return -1;
    
    for (int i = 0; i < n; i++)
        a[i] += value;
    
    return n;
}

// finds index of the target string
int lookup(const string a[], int n, string target)
{
    if (n < 0)
        return -1;

    // iterates through array
    // if target found, return index
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target)
            return i;
    }
        
    return -1;
}

// finds index of the greatest string
int positionOfMax(const string a[], int n)
{
    if (n < 0)
        return -1;
    
    int maxIndex = 0;
    
    // iterate through array
    for (int i = 1; i < n; i++)
    {
        // if item at index is greater than current max,
        // set maxIndex to current index
        if (a[i] > a[maxIndex])
            maxIndex = i;
    }
    return maxIndex;
}

// moves element at pos to the end of the array, rotating the rest of the array to the left
int rotateLeft(string a[], int n, int pos)
{
    if (n < 0 || pos < 0)
        return -1;
    
    string lastEntry = a[pos];
    
    // iterate through array starting at after pos
    // swap word with the word after it
    for (int i = pos; i < n - 1; i++)
    {
        string temp = a[i+1];
        a[i] = temp;
    }
    
    // set the last item in array to the lastEntry
    a[n - 1] = lastEntry;
    return pos;
}

// counts number of sequences of consecutive distinct items
int countRuns(const string a[], int n)
{
    int counter  = 0;
    
    if (n < 0)
        return -1;

    // iterate through array and check if item equals next item
    for (int i = 0; i < n; i++)
    {
        // if item does not equal next item, increment counter
        if (a[i] != a[i+1])
            counter++;
    }
    return counter;
}

// reverse order of elements in array
int flip(string a[], int n)
{
    if (n < 0)
        return -1;
    
    int k = n;
    
    // iterate through half of the items to flip
    for (int i = 0; i < (k / 2); i++)
    {
        // use temporary variables to swap elements
        string temp1 = a[i];
        string temp2 = a[k - 1];
        a[i] = temp2;
        a[k-1] = temp1;
        k--;
    }
    return n;
}

// returns position of first corresponding elements of both arrays that are not equal
int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    
    // set n to the smaller value of n1 or n2
    int n;
    if (n1 < n2)
        n = n1;
    else
        n = n2;
    
    // iterate through both arrays n times and find index of when they have elements that are not equal
    for (int i = 0; i < n; i++)
    {
        if (a1[i] != a2[i])
            return i;
    }
    return n;
}

// finds index of when all elements in array2 appear in array1
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    
    if (n2 == 0)
        return 0;
    
    // assume there is no pointOfSubsequence unless found
    int pointOfSubsequence = -1;
    int i = 0;
    int j = 0;
    
    // iterate through the first array
    while (i < n1)
    {
        // if first element in second array found in first array, increment pointOfSubsequence
        if (a1[i] == a2[j])
        {
            pointOfSubsequence = i;

            // iterate through the rest of the second array to check if the rest of elements are equal
            int l = i;
            for (int k = 0; k < n2; k++)
            {
                if (a1[l] != a2[k])
                {
                    pointOfSubsequence = -1;
                    break;
                }
                
                if (k == n2 - 1)
                    return pointOfSubsequence;
                
                l++;
            }
        }
        i++;
    }
    return pointOfSubsequence;
}

// finds index of when any element in second array is found in the first array
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    
    // iterate through the first array
    for (int  i = 0; i < n1; i++)
    {
        // iterate through the second array to check if any of its elements match the element in the first array
        for (int j = 0; j < n2; j++)
        {
            if (a1[i] == a2[j])
                return i;
        }
    }
    
    return -1;
}

// divides the array based on whether the items come before or after the separator string
int separate (string a[], int n, string separator)
{
    if (n < 0)
        return -1;
    
    int counter = 0;
    int index = 0;
    
    // iterate through array to find words that are greater than separator
    // swap word greater than separator with the next word in array that comes before separator
    for (int i = 0; i < n; i++)
    {
        if (a[i] > separator)
        {
            counter++;
            for (int j = i + 1; j < n; j++)
            {
                if (a[j] <= separator)
                {
                    string s1 = a[i];
                    string s2 = a[j];
                    a[i] = s2;
                    a[j] = s1;
                    index = i+1;
                    break;
                }
            }
        }
    }

    // loop through organized array and return index of first element that is not less than separator
    for (int i = 0; i < n; i++)
    {
        if (a[i] >= separator)
            return i;
    }
    
    return n;
}


int main()
{

    string people[5] = { "donald" , "lindsey", "fiona", "rudy", "mick" };
    string p[5] = {"donald", "lindsey", "rudy", "rudy", "mick" };
    string d[6] = {"amy", "amy", "viv", "pat", "ed", "ed" };
    string f[4] = { "bob", "chad", "kyle", "john" };
    string g[6] = {"bob", "chad", "kyle", "john", "john", "john" };
    string n1[9] = { "A", "B", "C", "D", "E", "F", "B", "C", "F" };
    string n2[3] = { "C", "D", "E"};
    string n3[3] = { "B", "C", "F"};
    string n4[6] = { "a", "A", "b", "B", "c", "C"};
    string n5[4] = { "marie", "nancy", "lindsey", "mike" };
    string n6[6] = { "donald", "lindsey", "marie", "rudy", "fiona", "adam" };


    assert(lookup(people, 5, "rudy") == 3);
    assert(lookup(people, 5, "RUDy") == -1);
    assert(lookup(people, -2, "rudy") == -1);
    assert(lookup(p, 5, "rudy") == 2);
    assert(lookup(people, 5, "lisa") == -1);

    assert(positionOfMax(people, 5) == 3);
    assert(positionOfMax(people, -5) == -1);
    assert(positionOfMax(people, 0) == 0);
    assert(positionOfMax(p, 5) == 2);
    assert(positionOfMax(n4, 6) == 4);
 
    assert(rotateLeft(people, 5, 1) == 1 && people[1] == "fiona" && people[4] == "lindsey");
    assert(rotateLeft(people, -5, 1) == -1);
    assert(rotateLeft(people, 5, -2) == -1);

    assert(countRuns(people, 5) == 5);
    assert(countRuns(d, 6) == 4);
    assert(countRuns(d, -3) == -1);
    assert(countRuns(d, 0) == 0);
     
    //assert(flip(people, 3) == 3 && people[0] == "fiona" && people[1] == "lindsey" && people[2] == "donald");
    //assert(flip(people, -1) == -1);

    assert(differ(f, 4, g, 6) == 4);
    assert(differ(f, -1, g, -1) == -1);

    assert(subsequence(n1, 9, n2, 3) == 2);
    assert(subsequence(n1, 9, n3, 3) == 6);
    assert(subsequence(n1, 0, n3, 0) == 0);
    assert(subsequence(n1, -2, n3, -2) == -1);

    assert(lookupAny(n1, 9, n2, 3) == 2);
    assert(lookupAny(f, 4, n2, 3) == -1);
    assert(lookupAny(n1, 9, n2, -1) == -1);

    assert(separate(n5, 4, "mike") == 2);
    assert(separate(n6, 6, "gordon") == 3);
    assert(separate(g, 6, "john") == 2);

    cout << "Test cases were successful" << endl;
}
