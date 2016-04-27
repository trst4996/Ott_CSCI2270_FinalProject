#include "HashTable.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

HashTable::HashTable()
{
    //ctor
}

HashTable::~HashTable()
{
    //dtor
}
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
        sum = sum ^(x.size()) % s;
        break;
    }



    return sum;
}
void HashTable :: insertMovie(string name, int year, int h)
{
    int index = hashSum(name, tableSize, h);
    hashElem *temp = hTable[index];
    hashElem *hInsert = new hashElem(name, year);
    //cout << "no seg fault" << endl;
    while (temp -> next != NULL)
    {
        temp = temp -> next;
    }
    temp -> next = hInsert;
    hInsert -> prev = temp;
}

void HashTable  :: printTableContents()
{
    bool notEmpty = 0;
    hashElem *temp = NULL;
    for (int k = 0; k < tableSize; k ++ )
    {
        temp = hTable[k];printTableContents();
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
    hashElem *found;
    int index = hashSum(name, tableSize, h);
    bool foundB = 0;
    for (int i = 0; i < tableSize; i ++)
    {
        hashElem *temp = hTable[i];
        while (temp -> next != NULL & !foundB)
        {
            if (temp -> title == name)
            {
                found = temp;
                foundB = 1;
            }
            temp = temp -> next;
        }
    }
    if (foundB)
    {
        return found;
    }else{
        return NULL;
    }
}

void HashTable :: insertOrderName(string name, int year)
{

    hashElem *node = new hashElem(name, year);
    if (headName == NULL)
    {
        headName = node;
        cout << "new head: " << headName -> title << endl;
        tailName = node;
    }else{
        bool flag = 0;
        hashElem *temp = headName;
        while (temp -> next != NULL & !flag)
        {
            if (name.compare(temp-> title) >= 0)
            {
                flag = true;
            }else{
                temp = temp -> next;
            }

        }

        if (temp == headName)
        {
            temp -> prev = node;
            node -> next = temp;
            headName = node;
            cout << "adding to head" << endl;
        }else if(temp == tailName)
        {
            temp -> prev = node;
            node -> next = temp;
            tailName = node;
            cout << "adding to tail" << endl;
        }else{
            node -> next = temp;
            node -> prev = temp -> prev;
            temp -> prev -> next = node;
            temp -> prev = node;
            cout << "adding to the middle" << endl;
        }


    }
}
void HashTable :: printList()
{
    if (headName != NULL)
    {
        hashElem *temp = headName;
        if (temp -> next == NULL)
        {
            cout << "list not built" << endl;
        }
        while (temp -> next != NULL)
        {
            cout << temp -> title << ":" << temp -> year << endl;
            temp = temp -> next;
        }
    }else{
        cout << "empty" << endl;
    }
}

