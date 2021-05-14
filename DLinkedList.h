//Kyle Luster
//1-31-21
//This is my work; with help from the ACE center

#pragma once

#include <iostream>

using namespace std;

template <class T>
class DLinkedList {
	//PROVIDED
	friend ostream & operator<<(ostream & out, const DLinkedList<T> & rhs) {
		DNode * curr = rhs.header->next;
		while (curr != rhs.header) {
			out << curr->data << " ";
			curr = curr->next;
		}
		return out;
	}

public:

	//inner class DNode PROVIDED
	class DNode {
	public:
		DNode * next;
		DNode * prev;
		T data;

		DNode(T val = T()) {
			data = val;
			next = prev = this;
		}
		
	};

	//create an empty list:  PROVIDED
	DLinkedList() {
		//create the header
		header = new DNode();		
	}

	//add method  PROVIDED
	DNode * add(T item) {
		//add a new node and return a 
		//pointer to this node
		DNode * newNode = new DNode(item);
		newNode->prev = header;
		newNode->next = header->next;
		header->next->prev = newNode;
		header->next = newNode;
		return newNode;
	}


  bool remove(T val) {
        DNode* temp = header->next;

        while(temp != header && temp->data != val) {
           temp = temp->next;
        }  
        if(temp->data == val) { 
  //if the value matches the desired value to delete, it is dereferneced
            temp->prev->next = temp->next;                           
            temp->next->prev = temp->prev;
  //becasue C++ does not delete the "floaters" we have to delete it manually
            delete(temp);
            return true;
        }
		return false;
	}


	void insertOrder(T item) {
	  DNode* newDNode = new DNode(item);
    DNode* temp = header->next;
    //inserts in ascending order
    //this loop will go until the value we hold is less than the one in front of it
        while(temp->data <= newDNode->data && temp != header) {
          temp = temp->next; 
        }  
    //if at the end before header, new node is put in before the last value
        if(temp->next == header && temp->data <= newDNode->data) {   
          newDNode->next = temp->next;
          newDNode->prev = temp;
          temp->next->prev = newDNode;
          temp->next = newDNode;
    //if after header, place after and ref header to new node
        } else if(temp == header && temp->data >= newDNode->data) {
          newDNode->next = temp;
          newDNode->prev = temp->prev;
          temp->prev->next = newDNode;
          temp->prev = newDNode;
          header = newDNode; 
        } else {
    //inserted in the middle
          newDNode->next = temp;
          newDNode->prev = temp->prev;
          temp->prev->next = newDNode;
          temp->prev = newDNode;
        }
	}


	bool insertOrderUnique(T item) {
        DNode* newDNode = new DNode(item); //new node with data is created, floating in space
        DNode* temp = header;
        //this compares the new data and progresses through to make sure it is unique
        //Big O Analysis: O(n)
        while(newDNode->data != temp->data && temp->next != header) { temp = temp->next; 
        } 
        //if it passes the test, then it is added
        //Big O Analysis: O(n)
        if(temp->next == header && newDNode->data != temp->data) {
            	  DNode* newDNode = new DNode(item);
    DNode* temp = header->next;
    //using insert order again
        while(temp->data <= newDNode->data && temp != header) {
          temp = temp->next; 
        }  
        if(temp->next == header && temp->data <= newDNode->data) {   
          newDNode->next = temp->next;
          newDNode->prev = temp;
          temp->next->prev = newDNode;
          temp->next = newDNode;
        } else if(temp == header && temp->data >= newDNode->data) {
          newDNode->next = temp;
          newDNode->prev = temp->prev;
          temp->prev->next = newDNode;
          temp->prev = newDNode;
          header = newDNode; 
        } else {
          newDNode->next = temp;
          newDNode->prev = temp->prev;
          temp->prev->next = newDNode;
          temp->prev = newDNode;
        }
            return true;
        }
    //if not unique, it will not be inserted
		return false;
	}


	DLinkedList merge(DLinkedList rhs) {
		DLinkedList result;                                             
		DNode* head = result.header;                                    
		DNode* temp1 = header->next;                                    
		DNode* temp2 = rhs.header->next;      
    //Big O Analysis: O(n): the while loop iterates through each node
		while(temp1 != header && temp2 != rhs.header) {                 
		    DNode* hold;                                               
            if(temp1->data < temp2->data) {   //comparing values and holding onto the lower of them
                hold = temp1;
                temp1->prev->next = temp1->next; 
                temp1->next->prev = temp1->prev;
                temp1 = temp1->next;
            } else {
                hold = temp2;
                temp2->prev->next = temp2->next;
                temp2->next->prev = temp2->prev;
                temp2 = temp2->next;
            }
            //putting the lower value in the lower position
            hold->next = head->next; 
            hold->prev = head;
            head->next->prev = hold;
            head->next = hold;
            head = head->next;
		}
        //Big O Analysis: O(1) it happens instantaneously
        //this will put the rest of the larger list on the end
        if (temp1 == header) { 
            head->next = temp2;
            head->next->prev = head;
            result.header->prev = rhs.header->prev;
            rhs.header->next = rhs.header->prev = rhs.header;
        } else {
            head->next = temp1;
            head->next->prev = head;
            result.header->prev = header->prev;
            header->next = header->prev = header;
        }

        result.header->prev->next = result.header;

		return result;
	}

	
private:
	//DLinkedList fields:  PROVIDED
	DNode * header;	

};
