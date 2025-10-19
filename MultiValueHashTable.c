/*
 * MultiValueHashTable.c
 *
 *  Created on: 21 Dec 2022
 *      Author: lior
 */

#include "Defs.h"
#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "MultiValueHashTable.h"

struct MultiValueHashTable_t{
	hashTable hash;
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
	EqualFunction equalvalue;
};

/*function  for Hash table that created in the multihash*/
status printValue_toHash(Element list){
	if (list == NULL){
		return failure;
	}
	return displayList((LinkedList)list);
}

status freeValue_toHash (Element list){
	if(list == NULL){
		return failure;
	}
	return destroyList((LinkedList) list);
}
Element copyKey_toHash(Element elem){
	if(elem == NULL){
		return NULL;
	}
	return elem;
}

status freeKey_toHash (Element list){
	if(list == NULL){
		return failure;
	}
	return success;
}


//create multihash
MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,EqualFunction equalValue, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
	if(copyKey ==NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL || printValue == NULL || equalKey == NULL || equalValue == NULL||  transformIntoNumber == NULL){
		return NULL;
	}
	MultiValueHashTable multValHashTable = (MultiValueHashTable) malloc(sizeof(struct MultiValueHashTable_t));
	if (multValHashTable == NULL){
		return NULL;}
	multValHashTable->hash = createHashTable(copyKey, freeKey, printKey, copyValue, freeValue_toHash, printValue_toHash, equalKey, transformIntoNumber, hashNumber);
	if (multValHashTable->hash == NULL){
		return NULL;
	}
	multValHashTable->copykey = copyKey;
	multValHashTable->copyvalue = copyValue;
	multValHashTable->freekey = freeKey;
	multValHashTable->freevalue = freeValue;
	multValHashTable->printkey = printKey;
	multValHashTable->printvalue = printValue;
	multValHashTable->transformIntoNum = transformIntoNumber;
	multValHashTable->equalkey = equalKey;
	multValHashTable->equalvalue = equalValue;
	multValHashTable->size = hashNumber;
	return multValHashTable;
}





status addToMultiValueHashTable(MultiValueHashTable multValHashTable, Element key, Element value){
	if (multValHashTable == NULL || key == NULL || value == NULL){
		return failure;
	}
	LinkedList curr_linkeslist = lookupInHashTable(multValHashTable->hash, key);
	if (curr_linkeslist == NULL){
		//if there is not linkedlist in the hash yet then add
		LinkedList list_for_values = createLinkedList(multValHashTable->copyvalue,multValHashTable->freevalue, multValHashTable->printvalue,multValHashTable->equalvalue, multValHashTable->equalvalue);
		if (list_for_values == NULL){
			return failure;
		}
		appendNode(list_for_values,value);
		return addToHashTable(multValHashTable->hash, key, list_for_values);
	}
	return appendNode(curr_linkeslist, value);
}

//search in multihash
Element lookupInMultiValueHashTable(MultiValueHashTable multValHashTable, Element key){
	if (multValHashTable == NULL || key == NULL){
		return NULL;
	}
	LinkedList currect_list = lookupInHashTable(multValHashTable->hash , key);
	if (currect_list == NULL){
		return NULL;
	}
	return currect_list;
}

//remove from multihash
status removeFromMultiValueHashTable(MultiValueHashTable multValHashTable, Element key, Element value){
	if (multValHashTable == NULL || key == NULL || value == NULL){
		return failure;
	}
	LinkedList currect_list = lookupInHashTable(multValHashTable->hash , key);
	if(currect_list == NULL){
		return failure;
	}
	Element elem = searchByKeyInList(currect_list, value);
	if(elem == NULL){
		return failure;
	}
	if (deleteNode(currect_list, elem) == success){
		if(getLengthList(currect_list) == 0){

			if (removeFromHashTable(multValHashTable->hash, key) == success){
				return success;
			}
			else{
				return failure;
			}
		}
		return success;
	}
	return failure;
}

//print multihash
status displayMultiValueHashElementsByKey(MultiValueHashTable multValHashTable, Element key){
	if (multValHashTable == NULL || key == NULL){
		return failure;
	}
	LinkedList currect_pair = lookupInHashTable(multValHashTable->hash , key);

	if (currect_pair == NULL){
		return failure;
	}
	multValHashTable->printkey(key);
	return displayList(currect_pair);
}


//delete all multihash
status destroyMultiValueHashTable(MultiValueHashTable multValHashTable){
	if (multValHashTable == NULL){
		return failure;
	}
	destroyHashTable(multValHashTable->hash);
	free(multValHashTable);
	return success;
}



