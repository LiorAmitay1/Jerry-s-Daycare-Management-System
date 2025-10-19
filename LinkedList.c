/*
 * LinkedList.c
 *
 *  Created on: 18 Dec 2022
 *      Author: lior
 */

#include "LinkedList.h"
#include "Defs.h"

typedef struct Node_t* Node;

struct Node_t
{
	Node next;
	Node prev;
	Element data;
};


/*represent a generic LinkedList*/
struct LinkedList_t
{
	Node head;
	int size;
	//function:
	CopyFunction copyElement;
	FreeFunction freeElement;
	PrintFunction printElement;
	EqualFunction equalValueInElement;
	EqualFunction equalAllNode;
};





LinkedList createLinkedList (CopyFunction copyFunction, FreeFunction freeFunction, PrintFunction printFunction, EqualFunction equalvalueinelement, EqualFunction equalAllNode){
	if (copyFunction == NULL || freeFunction == NULL || printFunction == NULL || equalvalueinelement == NULL){
		return NULL;
	}
	LinkedList linkedlist = (LinkedList)malloc(sizeof(struct LinkedList_t));
	if (linkedlist == NULL){
		return NULL;
	}
	//first begin with one node and then create the next
	linkedlist->size = 0;
	linkedlist->head = NULL;
	linkedlist->copyElement = copyFunction;
	linkedlist->freeElement = freeFunction;
	linkedlist->printElement = printFunction;
	linkedlist->equalValueInElement = equalvalueinelement;
	linkedlist->equalAllNode = equalAllNode;
	return linkedlist;
}

status appendNode(LinkedList linkedlist, Element element){
	if (linkedlist == NULL || element == NULL){
		return failure;
	}
	Node newNode = (Node)malloc(sizeof(struct Node_t));
	if (newNode == NULL){
		return failure;
	}
	newNode->data = element;
	newNode->next = NULL;
	//if it is the first node
	if (linkedlist->head == NULL){
		linkedlist->head = newNode;
		newNode->prev = NULL;
	}
	else{
		//need to append to the other nodes
		Node curr = linkedlist->head;
		while(curr->next != NULL){
			curr = curr->next;
		}
		curr->next = newNode;
		newNode->prev = curr;
	}
	linkedlist->size++;
	return success;
}

status deleteNode(LinkedList linkedlist, Element element){
	if (linkedlist == NULL || element == NULL){
		return failure;
	}
	//if it is empty
	Node curr = linkedlist->head;
	if (curr == NULL){
		return failure;
	}
	//if it is empty
	if (linkedlist->size == 0){
		free(curr);
		return failure;
	}
	//if need to delete with only one nose
	if(linkedlist->size == 1){
		if (linkedlist->equalAllNode(curr->data, element)){
			linkedlist->freeElement(curr->data);
			linkedlist->head = NULL;
			linkedlist->size--;
			curr->next = NULL;
			curr->prev = NULL;
			free(curr);
			return success;
		}
		else
			return failure;
	}
	while(curr != NULL){
		//findes the current node
		if (linkedlist->equalAllNode(curr->data, element)){
			if (curr->prev != NULL){
				curr->prev->next = curr->next;
			}
			else{
				linkedlist->head = curr->next;
			}
			if(curr->next != NULL){
				curr->next->prev = curr->prev;
			}
			//free node
			linkedlist->freeElement(curr->data);
			free(curr);
			linkedlist->size--;
			return success;
		}
		curr = curr->next;
	}
	return failure;
}

//print all linked list
status displayList(LinkedList linkedlist){
	if (linkedlist == NULL){
		return failure;
	}
	Node curr = linkedlist->head;
	if (curr == NULL){
		return failure;
	}
	while(curr != NULL){
		linkedlist->printElement(curr->data);
		curr = curr->next;
	}
	return success;
}


//return element by the location in the linked list
Element getDataByIndex(LinkedList linkedlist, int indx){
	if (linkedlist == NULL){
		return NULL;
	}
	Node curr = linkedlist->head;
	if (curr == NULL){
		return NULL;
	}
	if(getLengthList(linkedlist)< indx){
		return NULL;
	}
	for(int i = 0; i < indx-1 ;i++){
		if (curr == NULL){
			return NULL;
		}
		curr = curr->next;
	}
	Element elem =  curr->data;
	if (elem == NULL){
		return NULL;
	}
	return elem;
}

//return the length of the linked list
int getLengthList(LinkedList linkedlist){
	if (linkedlist == NULL){
		return 0;
	}
	return linkedlist->size;
}

//return element by the key in the linked list
Element searchByKeyInList(LinkedList linkedlist, Element element){
	if (linkedlist == NULL || element == NULL){
		return NULL;
	}
	Node curr = linkedlist->head;
	if (curr == NULL){
		return NULL;
	}
	int i = 0;
	while(curr != NULL){
		if (linkedlist->equalValueInElement(curr->data, element) == true){
			return curr->data;
		}
		curr = curr->next;
		i++;
	}
	return NULL;
}

//delete all the list
status destroyList(LinkedList linkedlist){
	if (linkedlist != NULL){
		Node curr = linkedlist->head;
		Node curr2;
		while(curr != NULL){
			curr2 = curr->next;
			linkedlist->freeElement(curr->data);
			free(curr);
			curr = curr2;
		}
		free(linkedlist);
		return success;
	}
	return failure;
}


