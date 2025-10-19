/*
 * MultiValueHashTable.h
 *
 *  Created on: 21 Dec 2022
 *      Author: lior
 */

#ifndef MULTIVALUEHASHTABLE_H_
#define MULTIVALUEHASHTABLE_H_
#include "Defs.h"

typedef struct MultiValueHashTable_t *MultiValueHashTable;

MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,EqualFunction equalValue, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
status destroyMultiValueHashTable(MultiValueHashTable multValHashTable);
status addToMultiValueHashTable(MultiValueHashTable multValHashTable, Element key, Element value);
Element lookupInMultiValueHashTable(MultiValueHashTable multValHashTable, Element key);
status removeFromMultiValueHashTable(MultiValueHashTable multValHashTable, Element key, Element value);
status displayMultiValueHashElementsByKey(MultiValueHashTable multValHashTable, Element key);

#endif /* MULTIVALUEHASHTABLE_H_ */
