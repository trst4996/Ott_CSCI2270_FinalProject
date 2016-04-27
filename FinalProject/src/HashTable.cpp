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
        collisionCount ++;
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
    // broken due to the fact that the find function is fucked
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
    hashElem *temp = hTable[index];
    while (temp -> next != NULL)
    {
        if (temp -> title == name)
        {
            found = temp;
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
    // Hey // Adds the elements to a linked list in order so that the elements can be printed in order. Might try this with an array of structs since it doesn't work terribly well
    // Pulled it off of stack overflow, might scrap the whole idea though since it works about as well as a ten cent whore.
    hashElem *node = new hashElem(name, year);
    hashElem *temp = headName;
    hashElem **temp1 = &headName; // this stores the location of where node should go as the while loop traverses the list.

    while (temp != NULL && name.compare(temp -> title) > 0)
    {
        temp1 = &temp -> next; // storing the new location
        temp = temp -> next;
    }
    *temp1 = node;
    node -> next = temp;


}
void HashTable :: insertOrderYear(string name, int year)
{


    hashElem *node = new hashElem(name, year);

    hashElem *temp = headYear;
    hashElem **temp1 = &headYear; // this stores the location of where node should go as the while loop traverses the list.

    while (temp != NULL && temp -> year < node -> year)
    {
        temp1 = &temp -> next; // storing the new location
        temp = temp -> next;
    }
    *temp1 = node;
    node -> next = temp;


}

void HashTable :: printList()
{
    if (headName != NULL)
    {
        hashElem *temp = headName;
        while (temp -> next != NULL)
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
    if (headYear != NULL)
    {
        hashElem *temp = headYear;
        while (temp -> next != NULL)
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