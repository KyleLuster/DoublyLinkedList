//Kyle Luster
//1-31-21
//This is my work; with help from the ACE center

#include "DLinkedList.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string cleanUp(string str);

int main() {
	DLinkedList<string> lst1;
	DLinkedList<string> lst2;

	ifstream fin("Text1.in");

	string str;

	while (fin>>str) {		
		str = cleanUp(str);
		lst1.insertOrderUnique(str);
	}
	fin.close();

	fin.open("Text2.in");
	while (fin>>str) {
		str = cleanUp(str);
		lst2.insertOrderUnique(str);
	}

//using remove
lst2.remove("fish");

//using insert Order. I commented out to avoid a double cold
//lst1.insertOrder("cold");

//using insert order unique
lst2.insertOrderUnique("house");
//note: it did not insert because the word is not unique




	cout << "List 1: " << lst1 << endl;
	cout << "List 2: " << lst2 << endl;
	
//using the merge
	DLinkedList<string> combined = lst1.merge(lst2);

	cout << "\nAFTER MERGE" << endl;
	cout << "List 1: " << lst1 << endl;
	cout << "List 2: " << lst2 << endl;
	cout << "\nCombined: " << combined << endl;

  

	return 0;
}


string cleanUp(string str) {  //gets rid of all non-alpha chars at the ends
    int first = str.length();
    int last = 0;
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]); //sets all strings to lowercase
        if (str[i] > 97 && str[i] < 122) { 
          if (i < first) first = i;
          last = i;
        }
    }

    return str.substr(first, last - first + 1); //returns only the alphas
}
