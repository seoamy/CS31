//
//  fine.cpp
//  Project 2
//
//  Created by Amy Seo on 10/10/19.
//  Copyright © 2019 Amy Seo. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    //collecting defendant name input
    cout << "Defendant: ";
    string name;
    getline(cin, name);
    
    //collecting amount paid input
    cout << "Amount paid (in thousands): ";
    double amountPaid;
    cin >> amountPaid;
    cin.ignore(1000, '\n');
    
    //collecting fake athlete or not input
    cout << "Fake athlete? (y/n): ";
    string athlete;
    getline(cin, athlete);
    
    //checking for errors after receiving inputs
    if (name.length() == 0)
    {
        cout << "---" << endl << "You must enter a defendant name." << endl;
        return 1;
    }
    
    else if (amountPaid < 0)
    {
        cout << "---" << endl << "The amount paid must not be negative." << endl;
        return 1;
    }
    
    else if (athlete != "y" && athlete != "n")
    {
        cout << "---" << endl << "You must enter y or n." << endl;
        return 1;
    }
    
    // base fine amount is $20 thousand
    double fine = 20;
  
    //calculating fees
    if (amountPaid >= 40)
    {
        fine += 40 * 0.66;
        amountPaid -= 40;
        
        //additional fee if faked athelete
        if (athlete == "y")
        {
            if (amountPaid <= 210)
            {
                fine += amountPaid * 0.22;
                amountPaid -= amountPaid;
            }
            
            else
            {
                fine += 210 * 0.22;
                amountPaid -= 210;
            }
        }
        
        // if defendant is not a faked athlete a lesser fee is added
        else
        {
            if (amountPaid <= 210)
            {
                fine += amountPaid * 0.1;
                amountPaid -= amountPaid;
            }
            
            else
            {
                fine += 210 * 0.1;
                amountPaid -= 210;
            }
        }
        
        // additional fee if amount paid is greater than 250K
        if (amountPaid > 0)
        {
            fine += amountPaid * 0.14;
        }
    }
    
    // if the amount paid is less than 40 thousand, 66% fine will be added
    else
    {
        fine += amountPaid * 0.66;
    }
    
    cout.setf(ios::fixed);
    cout.precision(1);
    cout << "---" << endl << "The suggested fine for " << name << " is $" << fine << " thousand." << endl;
    
}
