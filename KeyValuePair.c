/*
 * KeyValuePair.c
 *
 *  Created on: 20 Dec 2022
 *      Author: lior
 */


#include "KeyValuePair.h"
#include "Defs.h"

struct KeyValuePair_t{
	Element Key;
	Element Value;
	//function:
	CopyFunction copykey;
	CopyFunction copyvalue;
	FreeFunction freekey;
	FreeFunction freevalue;
	PrintFunction printkey;
	PrintFunction printvalue;
	TransformIntoNumberFunction transformIntoNum;
	EqualFunction equalkey;
};

KeyValuePair createKeyValuePair(Element key, Element value, CopyFunction copyvalue, CopyFunction copykey, FreeFunction freevalue, FreeFunction freekey, PrintFunction printkey , PrintFunction printvalue, TransformIntoNumberFunction transformIntoNumberFunction, EqualFunction equalkey){
	if (key == NULL || value==NULL || copyvalue == NULL || copykey== NULL || freekey == NULL || freevalue == NULL || printkey == NULL || printvalue == NULL || transformIntoNumberFunction == NULL || equalkey == NULL){
		return NULL;
	}
	KeyValuePair keyvaluepair = (KeyValuePair)malloc(sizeof(struct KeyValuePair_t));
	if (keyvaluepair == NULL){
		return NULL;
	}
	keyvaluepair->Key = copykey(key);
	keyvaluepair->Value = copyvalue(value);
	keyvaluepair->copykey= copykey;
	keyvaluepair->copyvalue = copyvalue;
	keyvaluepair->equalkey = equalkey;
	keyvaluepair->freekey = freekey;
	keyvaluepair->freevalue = freevalue;
	keyvaluepair->printkey = printkey;
	keyvaluepair->printvalue = printvalue;
	keyvaluepair->transformIntoNum = transformIntoNumberFunction;
	return keyvaluepair;
}


status displayValue(KeyValuePair keyvaluepair){
	if (keyvaluepair == NULL){
		return failure;
	}
	//print only the value
	keyvaluepair->printvalue(keyvaluepair->Value);
	return success;
}


status displayKey(KeyValuePair keyvaluepair){
	if (keyvaluepair == NULL){
		return failure;
	}
	//print only the key
	keyvaluepair->printkey(keyvaluepair->Key);
	return success;
}


Element getValue(KeyValuePair keyvaluepair){
	if (keyvaluepair == NULL){
		return NULL;
	}
	return keyvaluepair->copyvalue(keyvaluepair->Value);
}


Element getKey(KeyValuePair keyvaluepair){
	if (keyvaluepair ==NULL){
		return NULL;
	}
	//returns the key
	return keyvaluepair->Key;
}



bool isEqualKey(KeyValuePair keyvaluepair, Element key){
	if (keyvaluepair ==NULL || key == NULL){
		return false;
	}
	Element key1 = getKey(keyvaluepair);
	//equal by key
	return keyvaluepair->equalkey(key1, key);
}


KeyValuePair copyKeyValuePair(KeyValuePair pair){
	if (pair == NULL){
		return NULL;
	}
	Element copy_key = pair->copykey(pair->Key);
	if (copy_key == NULL){
		return NULL;
	}
	Element copy_value = pair->copyvalue(pair->Value);
	if (copy_value == NULL){
		return NULL;
	}
	//allocate new key value pair
	KeyValuePair newpair = createKeyValuePair(copy_key, copy_value,pair->copyvalue, pair->copykey, pair->freevalue, pair->freekey, pair->printkey, pair->freevalue, pair->transformIntoNum, pair->equalkey);
	if (newpair == NULL){
		return NULL;
	}
	return newpair;
}




status destroyKeyValuePair(KeyValuePair keyvaluepair){
	if (keyvaluepair != NULL){
		//first free key
		if(keyvaluepair->Key != NULL){
			keyvaluepair->freekey(keyvaluepair->Key);
		}
		//then free value
		if (keyvaluepair->Value != NULL){
			keyvaluepair->freevalue(keyvaluepair->Value);
		}
		free(keyvaluepair);
		return success;
	}
	return failure;
}








