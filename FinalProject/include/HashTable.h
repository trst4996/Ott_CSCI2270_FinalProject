#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <vector>
using namespace std;

struct hashElem{
	string title;
	int year;
	hashElem *next;
    hashElem *prev;

	hashElem(){};
	hashElem(string in_title, int in_year)
	{
		title = in_title;
		year = in_year;
		next = NULL;
		prev = NULL;
	}

};

class HashTable
{
	public:
		HashTable();
		~HashTable();
		void printTableContents();
		void insertMovie(string name, int year, int h);
		void deleteMovie(string name, int h);
		hashElem *findMovie(string name, int h);
		void hashInit();
		void insertOrderName(string name, int year);
		void printList();
		void insertOrderYear(string name, int year);
		void printListYear();


	private:
		int hashSum(string x, int s, int h);
		int tableSize = 10;
		hashElem* hTable[10];
		hashElem* headName = NULL;
		hashElem* headYear = NULL;

};

#endif // HASHTABLE_H
