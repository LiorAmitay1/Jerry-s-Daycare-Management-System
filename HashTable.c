/*
 * HashTable.c
 *
 *  Created on: 20 Dec 2022
 *      Author: lior
 */

#include "HashTable.h"
#include "Defs.h"
#include "KeyValuePair.h"
#include "LinkedList.h"



/*functions that needed for the key value pair that inside the hash*/
status printKeyValueNode(Element element){
	if (element == NULL)
	        return failure;
	KeyValuePair new_key_val = (KeyValuePair) element;
	if(displayKey(new_key_val) == success && displayValue(new_key_val) == success)
		return success;
	return failure;
}
status freeKeyValueNode (Element element){
	if (element == NULL){
		return failure;
	}
	return  destroyKeyValuePair((KeyValuePair)element);

}
Element copyKeyValueNode(Element element){
	if (element == NULL){
		return NULL;
	}
	KeyValuePair new_key_val = (KeyValuePair) element;
	KeyValuePair key_val = copyKeyValuePair(new_key_val);
	if (key_val == NULL){
		return NULL;
	}
	return key_val;
}

bool EqualKeyInKeyValueNode1(Element element1, Element element2){
	if (element1 == NULL || element2 == NULL){
		return false;
	}
	return isEqualKey(element1, element2);
}



struct hashTable_s{
	LinkedList* array;
	int size;
	//functions
	CopyFunction copykey;
	CopyFunction copyvalue;
	FreeFunction freekey;
	FreeFunction freevalue;
	PrintFunction printkey;
	PrintFunction printvalue;
	TransformIntoNumberFunction transformIntoNum;
	EqualFunction equalkey;
};


hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
	if(copyKey ==NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL || printValue == NULL || equalKey == NULL ||  transformIntoNumber == NULL){
		return NULL;
	}
	hashTable hashtable = (hashTable)malloc(sizeof(struct hashTable_s));
	if (hashtable == NULL){
		return NULL;
	}
	hashtable->size = hashNumber;
	if(hashtable->size == 0){
		free(hashtable);
		return NULL;
	}
	hashtable->array = (LinkedList*)malloc(sizeof(LinkedList)*(hashtable->size));
	if(hashtable->array == NULL){
		free(hashtable->array);
		free(hashtable);
		return NULL;
	}
	for (int i = 0; i< hashNumber; i++){
		hashtable->array[i] = NULL;
	}
	hashtable->copykey = copyKey;
	hashtable->copyvalue = copyValue;
	hashtable->equalkey = equalKey;
	hashtable->freekey = freeKey;
	hashtable->freevalue = freeValue;
	hashtable->printkey = printKey;
	hashtable->printvalue = printValue;
	hashtable->transformIntoNum = transformIntoNumber;
	return hashtable;
}


status addToHashTable(hashTable hashtable, Element key, Element value){
	if(hashtable == NULL || key == NULL || value == NULL){
		return failure;
	}
	int indx_hash = (hashtable->transformIntoNum(key) % hashtable->size);
	KeyValuePair new_key_val = createKeyValuePair(key, value, hashtable->copyvalue, hashtable->copykey, hashtable->freevalue, hashtable->freekey, hashtable->printkey , hashtable->printvalue, hashtable->transformIntoNum, hashtable->equalkey);
	if (hashtable->array[indx_hash] == NULL){
		//create new linked list
		LinkedList linkedlist = createLinkedList(copyKeyValueNode, freeKeyValueNode, printKeyValueNode ,EqualKeyInKeyValueNode1, EqualKeyInKeyValueNode1);
		hashtable->array[indx_hash] = linkedlist;
	}
	if (appendNode(hashtable->array[indx_hash],new_key_val) == failure){
		destroyKeyValuePair(new_key_val);
		return failure;
	}
	return success;
}

//search by key in the hash and return the value
Element lookupInHashTable(hashTable hashtable, Element key){
	if (hashtable == NULL || key == NULL){
		return NULL;
	}
	int indx_hash = (hashtable->transformIntoNum(key)) % (hashtable->size);
	if (hashtable->array[indx_hash] == NULL){
		return NULL;
	}
	KeyValuePair elem_return = searchByKeyInList(hashtable->array[indx_hash], key);
	if (elem_return == NULL){
		return NULL;
	}
	return getValue(elem_return);
}

//remove a specific key in the hash
status removeFromHashTable(hashTable hashtable, Element key){
	if (hashtable == NULL || key == NULL){
		return failure;
	}
	int indx_hash = (hashtable->transformIntoNum(key)) % (hashtable->size);
	if (hashtable->array[indx_hash] == NULL){
		return failure;
	}
	Element elem_return = searchByKeyInList(hashtable->array[indx_hash], key);
	if (elem_return == NULL){
		return failure;
	}
	if( deleteNode(hashtable->array[indx_hash],key)== success){
		if (getLengthList(hashtable->array[indx_hash]) == 0 ){
			free(hashtable->array[indx_hash]);
			hashtable->array[indx_hash] = NULL;
			return success;
		}
		return success;
	}
	return failure;


}

//print all hash table
status displayHashElements(hashTable hashtable){
	if (hashtable == NULL){
		return failure;
	}
	for (int i =0; i< hashtable->size; i++){
		if (hashtable->array[i] != NULL){
			displayList(hashtable->array[i]);
		}
	}
	return success;
}
//delete the hash table
status destroyHashTable(hashTable hash){
	if (hash == NULL){
		return failure;
	}
	for (int i = 0; i< hash->size; i++){
		if(hash->array[i] != NULL){
			destroyList(hash->array[i]);
		}
	}
	free(hash->array);
	free(hash);
	return success;
}


