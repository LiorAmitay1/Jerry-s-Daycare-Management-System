/*
 * LinkedList.h
 *
 *  Created on: 18 Dec 2022
 *      Author: lior
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "Defs.h"



typedef struct LinkedList_t* LinkedList;



LinkedList createLinkedList (CopyFunction copyFunction, FreeFunction freeFunction, PrintFunction printFunction, EqualFunction equalvalueinelement, EqualFunction equalAllNode);

//destroy the struct LinkedList
status destroyList(LinkedList linkedlist);

//append the node to the end of the linked list
status appendNode(LinkedList linkedlist, Element element);

//delete node from linked list, if the element is not inside failure.
status deleteNode(LinkedList linkedlist, Element element);

//print all the linked list from beginning to end.
status displayList(LinkedList linkedlist);

//return the value of the node in index int that given. if dosen't exist
Element getDataByIndex(LinkedList linkedlist, int indx);

//return the size of linked list
int getLengthList(LinkedList linkedlist);

//Checks whether there is a link in which a value that contains the same is stored Part received, and returns the value stored in the link
Element searchByKeyInList(LinkedList linkedlist, Element element);




#endif /* LINKEDLIST_H_ */


