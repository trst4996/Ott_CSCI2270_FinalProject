#include "HashTable.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <tgmath.h>

using namespace std;

HashTable::HashTable()
{
    //ctor
}

HashTable::~HashTable()
{
    //dtor
}

/*
The biggest difference you'll see in this program from assignment 12 is that most functions now take the parameter
 "h." This changes which hash function is being used to do things. That's about it. There are a few extra function in here
 that don't do a whole lot but are there anyway

*/
void HashTable :: hashInit()
{
    for (int i = 0; i < tableSize; i ++)
    {
        hashElem *node = new hashElem("empty", -1);
        hTable[i] = node;
    }
}
int HashTable :: hashSum(string x, int s, int h)
{
    int sum = 0;
    float fSum = 0;
    for (int i = 0; i < x.size(); i ++)
    {
        sum = sum + x[i];
    }
    switch (h)
    {
    case 1:
        //division method
        sum = sum % s;
        break;
    case 2:
        //Knuth variance
        sum = (sum * (sum + 3)) % s;
    case 3:
        // The clear best one
        sum = (sum ^(x.size())) % s;
        break;
    }



    return sum;
}
void HashTable :: insertMovie(string name, int year, int h)
{
    // remarkably un-fucked

    int index = hashSum(name, tableSize, h);
    hashElem *temp = hTable[index];
    hashElem *hInsert = new hashElem(name, year);
    if (temp -> next != NULL)
    {
        collisionCount ++; // keeps track of the number of collisions occurring
    }
    while (temp -> next != NULL)
    {
        temp = temp -> next;
    }
    temp -> next = hInsert;
    hInsert -> prev = temp;
    itemCount ++;
}

void HashTable  :: printTableContents()
{
    // not fucked function that prints everything just fine
    bool notEmpty = 0;
    hashElem *temp = NULL;
    for (int k = 0; k < tableSize; k ++ )
    {
        temp = hTable[k];
        if(temp -> next != NULL)
        {
            notEmpty = 1;
        }
    }
    if (notEmpty)
    {
        for (int i = 0; i < tableSize; i ++)
        {
            hashElem *temp1 = hTable[i];
            while (temp1 -> next != NULL)
            {
                temp1 = temp1->next;
                cout << temp1 -> title<<  ":" << temp1 -> year<< endl;
            }

        }
    }else{
        cout << "empty" << endl;
    }

}
void HashTable  :: deleteMovie(string name, int h)
{

    hashElem *found = findMovie(name, h);
    if (found != NULL)
    {
        found -> prev -> next = found -> next;
        found -> next -> prev = found -> prev;
        delete found;
    }else{
        cout << "not found" << endl;
    }

}
hashElem *HashTable :: findMovie(string name, int h)
{

    hashElem *found = NULL;
    int index = hashSum(name, tableSize, h);
    bool foundB = 0;
    hashElem *temp = hTable[index];
    while (temp != NULL && !foundB)
    {
        if (temp -> title == name)
        {
            found = temp;
            foundB = 1;
        }else{
            temp = temp -> next;
        }
    }

    if (found != NULL)
    {
        return found;
    }else{
        return NULL;
    }
}

void HashTable :: insertOrderName(string name, int year)
{
    // Adds the elements to a linked list in order so that the elements can be printed in order.

    hashElem *node = new hashElem(name, year);
    bool orderFlag = 0;
    if (headName == NULL)
    {
        headName = node;
    }else{

        if (name.compare(headName-> title) < 0)
        {
           // name comes before head
           node -> next = headName;
           headName = node;
        }else{
            // name comes after temp
            hashElem *temp = headName;
            while (temp -> next != NULL && !orderFlag)
            {
                // while name keeps going after temp, and temp -> next != NULL
                if (name.compare(temp -> next -> title) < 0)
                {
                    //meaning we hit a point where name should go after temp and before temp -> next, flag = true and the while loop will exit
                    orderFlag = true;
                }else{

                    temp = temp -> next;
                }
            }
            node -> next = temp -> next;
            temp -> next = node;
        }

    }
}


void HashTable :: insertOrderYear(string name, int year)
{
    // Adds the elements to a linked list in order so that the elements can be printed in order.
    hashElem *node = new hashElem(name, year);
    bool orderFlag = 0;
    if (headYear == NULL)
    {
        headYear = node;
    }else{

        if (year < headYear -> year)
        {
           // node goes before head
           node -> next = headYear;
           headYear = node;
        }else{
            // year > temp -> year
            hashElem *temp = headYear;
            while (temp -> next != NULL && !orderFlag)
            {
                // while node keeps going after temp, and temp -> next != NULL
                if (year < temp -> next -> year)
                {
                    //meaning we hit a point where name should go after temp and before temp -> next, flag = true and the while loop will exit
                    orderFlag = true;
                }else{

                    temp = temp -> next;
                }
            }
            node -> next = temp -> next;
            temp -> next = node;
        }

    }
}

void HashTable :: printList()
{
    //Prints the items in alphabetical order.
    if (headName != NULL)
    {
        hashElem *temp = headName;
        //cout << temp -> title << ":" << temp -> year << endl;
        while (temp != NULL)
        {
            cout << temp -> title << ":" << temp -> year << endl;
            temp = temp -> next;
        }
    }else{
        cout << "empty" << endl;
    }
}

void HashTable :: printListYear()
{
    //Prints items in numerical order by year
    if (headYear != NULL)
    {
        hashElem *temp = headYear;
        while (temp != NULL)
        {
            cout << temp -> year << ":" << temp -> title << endl;
            temp = temp -> next;
        }
    }else{
        cout << "empty" << endl;
    }
}
void HashTable :: colCount(int h)
{
    // Displays all of the
    switch (h)
    {
    case 1:
        cout << "Using Division Method:" << endl;
        break;
    case 2:
        cout << "Using the Knuth Variant on Division:" << endl;
        break;
    case 3:
        cout << "Using the clearly superior hash function by yours truly:" << endl;
        break;

    }
    cout << "Current number of collisions: " << collisionCount << endl;
    cout << "Current number of items: " << itemCount << endl;
    cout << "Hash Table size: " << tableSize << endl;
}
