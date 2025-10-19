/*
 * KeyValuePair.h
 *
 *  Created on: 20 Dec 2022
 *      Author: lior
 */

#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_
#include "Defs.h"

typedef struct KeyValuePair_t* KeyValuePair;

//create key value pair with all the function that needed
KeyValuePair createKeyValuePair(Element key, Element value, CopyFunction copyvalue, CopyFunction copykey, FreeFunction freevalue, FreeFunction freekey, PrintFunction printkey , PrintFunction printvalue, TransformIntoNumberFunction transformIntoNumberFunction, EqualFunction equalkey);

//delete all key value pair
status destroyKeyValuePair(KeyValuePair keyvaluepair);

//print the value of the key value pair
status displayValue(KeyValuePair keyvaluepair);

//print the key of the key value pair
status displayKey(KeyValuePair keyvaluepair);

//return the element key off the key value pair
Element getValue(KeyValuePair keyvaluepair);

//return the element value off the key value pair
Element getKey(KeyValuePair keyvaluepair);

//return the if the two element are equal in the key inside the key value pair
bool isEqualKey(KeyValuePair keyvaluepair, Element key);

//copy the key value pair
KeyValuePair copyKeyValuePair(KeyValuePair pair);



#endif /* KEYVALUEPAIR_H_ */
