#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "HashTable.h"

using namespace std;

int menuSelect() // function that gets the user's selection for later
{
    string selection;
    cout << "======Main Menu======" << endl;
    cout << "1. Insert movie" << endl;
    cout << "2. Delete movie" << endl;
    cout << "3. Find movie" << endl;
    cout << "4. Print table contents" << endl;
    cout << "5. Print table contents in order by title" << endl;
    cout << "6. Print table contents in order by year" << endl;
    cout << "7. Quit" << endl;


    getline(cin, selection);
    int selectionInt = atoi(selection.c_str());
    while ((selectionInt < 1) || (selectionInt > 7))
    {
        cout << "Please choose a number from the menu" << endl;
        getline(cin, selection);
        selectionInt = atoi(selection.c_str());
    }
    return selectionInt;
}
int chooseHash()
{
    string selection;
    cout << "Before doing anything, set the hash function to use." << endl;
    cout << "This cannot be changed without exiting the program." << endl;
    cout << "   1. Division Method." << endl;
    cout << "   2. Knuth Variant on Division." << endl;
    cout << "   3. Hash function I made up just now." << endl;
    cout << "   4. Hash function information." << endl;

    getline(cin, selection);
    int selectionInt = atoi(selection.c_str());
    while ((selectionInt < 1) || (selectionInt > 4))
    {
        cout << "Please choose a number from the menu" << endl;
        getline(cin, selection);
        selectionInt = atoi(selection.c_str());
    }
    return selectionInt;
}
void infoDisplay()
{
    //  function made just to describe the different hash functions
    cout << "Division Method: This is the most basic method of hashing data." << endl;
    cout << "The index is found by summing all of the ASCII values of the characters in" << endl;
    cout << "the title and modding that value with the size of the hash table. " << endl;
    cout << "Very prone to collisions." << endl;
    cout << "\nKnuth Variant on Division: This method takes the sum" << endl;
    cout << "of the ASCII values k and performs the operation k(k+3) % s where" << endl;
    cout << "s is the size of the hash table. This method is supposedly less " << endl;
    cout << "prone to collisions (Fleck). " << endl;
    cout << "\nMy own special method that I made up just for this project: This method " << endl;
    cout << "is not proven to be efficient or not efficient. This method uses k, the sum " << endl;
    cout << "of the ASCII values in the string, p, the size of the string, and s, the " << endl;
    cout << "size of the hash table. It then performs the operation floor(k^p) % s in " << endl;
    cout << "order to get the index. I believe this to be an efficient function because " << endl;
    cout << "it is based on more than one aspect of the data, which allows more " << endl;
    cout << "possibilities for indices than from just using one aspect of the data.\n" << endl;
}
void mainFuntions(int hashFunc)
{
    HashTable h;
    h.hashInit();
    string inName, inYear, dName, fName;
    int yearInt;
    int select = menuSelect();
    hashElem *foundNode = NULL;
    while (select != 5)
    {
        switch(select)
        {
        case 1:
            // choose hash function
            cout << "Enter title:" << endl;
            getline(cin, inName);
            cout << "Enter year:" << endl;
            getline(cin, inYear);
            yearInt = atoi(inYear.c_str());

            h.insertMovie(inName, yearInt, hashFunc);
            h.insertOrderYear(inName, yearInt);
            h.insertOrderName(inName, yearInt);
            break;

        case 2:
            cout << "Enter title:" << endl;
            getline(cin, dName);
            h.deleteMovie(dName, hashFunc);
            break;
        case 3:
            cout << "Enter title:" << endl;
            getline(cin, fName);
            foundNode = h.findMovie(fName, hashFunc);
            if (foundNode != NULL)
            {
                cout << foundNode -> title <<  ":" << foundNode -> year << endl;
            }else{
                cout << "not found" << endl;
            }
            break;
        case 4:
            h.printTableContents();
            break;
        case 5:
            h.printList();
            break;
        case 6:
            h.printListYear();
            break;
        }
        select = menuSelect();
    }
    cout << "Goodbye!" << endl;
}

int main()
{

    int hashSelect;
    hashSelect = chooseHash();
    switch (hashSelect)
    {
        case 1:
            mainFuntions(1);
            break;
        case 2:
            mainFuntions(2);
            break;
        case 3:
            mainFuntions(3);
            break;
        case 4:
            infoDisplay();
            break;
    }
        //hashSelect = chooseHash();
    return 0;
}
