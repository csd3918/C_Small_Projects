/*Creator: Vasileiadis George
        AM:3918
        Email:csd3918@csd.uoc.gr
        Date: 30-3-2021
        Assignment3
        File: ./src/symtablehash.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "symtable.h"

#define S_o_HASH 509

/*Make a new data type in the order of the assignment*/
typedef struct bind
{
    char *key;
    void *value;
}
bind;


struct SymTable
{
    unsigned int numofbinds;
    bind *table[S_o_HASH];
};

static unsigned int SymTable_hash(const char *pcKey)
{
    size_t i=0U;
    unsigned int uiHash = 0U;
    while(pcKey != '\0')
    {
        uiHash = uiHash * S_o_HASH + pcKey[i];
        i++;
    }
    return uiHash % S_o_HASH;
}

/* making a new empty Symbol table */
SymTable_T SymTable_new(void)
{
SymTable_T oSymTable;
size_t i = 0U;
oSymTable = malloc(sizeof(struct SymTable));
assert(oSymTable);
while (i < S_o_HASH)
{
    oSymTable -> table[i] = NULL;
    i++;
}
oSymTable -> numofbinds = 0;
return oSymTable;
}
/* The function 'SymTable_free' frees all the memory that used from
  oSymTable. If 'oSymTable' == NULL, then the function does nothing. */
void SymTable_free(SymTable_T oSymTable)
{
    size_t i = 0U;
    assert(oSymTable);
    while(i<S_o_HASH){
        if(oSymTable -> table[i] != NULL)
        {
            free(oSymTable -> table[i] -> key);
            free(oSymTable -> table[i] );
        }
    }

free(oSymTable);
}

/* The function 'SymTable_getLength' returns the number of bindings
to oSymTable. It is a checked runtime error of the program if oSymTable == NULL.*/
unsigned int SymTable_getLength(SymTable_T oSymTable)
{
    assert(oSymTable);
    return oSymTable -> numofbinds;
}
/* The function 'SymTable_put', if there is no binding with a key 'pcKey'
to oSymTable,  adds a new binding to oSymTable that consists of the key 'pcKey'
and the value 'pvValue', returns 1 (TRUE).Otherwise, the function does not
change the oSymTable, returns 0 (FALSE).
It is checked runtime error if oSymTable or pcKey is NULL.*/
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
    bind *new_bind;
    unsigned int ind = 0U;
    assert(oSymTable);

    if(SymTable_contains (oSymTable,pcKey) == 1) return 0;

    new_bind = malloc (sizeof(bind));
    assert(new_bind);
    new_bind->key = malloc((strlen(pcKey)+1) * sizeof(char));
    strcpy(new_bind->key, pcKey);
    new_bind->value = (void *)pvValue;

    ind = SymTable_hash(pcKey);
    /*if there is not an element in this place , we enter the new one*/
    if(oSymTable->table[ind] == NULL)
    {
        oSymTable->table[ind] = new_bind;
        oSymTable->numofbinds++;
        return 1;
    }
    return 0;
}
/* The function SymTable_remove , if there is a binding with 'pcKey' key
in oSymTable, removes binding from oSymTable and returns 1 (TRUE).
Otherwise, the function does not change oSymTable, and returns 0 (FALSE).
It is checked runtime error if oSymTable or pcKey is NULL.*/
int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
    unsigned int ind = 0U;
    assert(oSymTable);

    if(SymTable_contains(oSymTable,pcKey) == 0) return 0;

    ind = SymTable_hash(pcKey);
    free(oSymTable->table[ind]->key); /* here we free the memory by eliminating the element in this table[index] */
    free(oSymTable->table[ind]);
    oSymTable->table[ind] = NULL;
    oSymTable->numofbinds--;
    return 1;
}
/* The function SymTable_contains returns 1 (TRUE) if oSymTable
contains a binding, which its key is 'pcKey',
or 0 (FALSE) if it does not contain one. It is a checked runtime error
if oSymTable or pcKey is NULL.*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
    unsigned int ind = 0U;
    bind *tmp;

    assert(oSymTable);
    ind = SymTable_hash(pcKey);
    tmp = oSymTable->table[ind];
    if(tmp == NULL) return 1;
    return 0;
}
/* The function SymTable_get returns the value of binding to oSymTable
which its key is 'pcKey', or NULL, if there is not such a binding.
It is a checked runtime error if oSymTable or pcKey is NULL.*/
void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
    unsigned int ind = 0U;
    bind *tmp;

    assert(oSymTable);
    if(SymTable_contains(oSymTable,pcKey)==0) return NULL;
    ind = SymTable_hash(pcKey);
    tmp = oSymTable->table[ind];
    if (tmp != NULL) return (void*)tmp -> value;
return NULL;
}
/* The function SymTable_map applies the function *pfApply on every
binding in oSymTable, applying pvExtra as an extra parameter.
It is checked runtime error if oSymTable or pfApply is NULL.*/
void SymTable_map(SymTable_T oSymTable, void(*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra)
{
    bind *tmp;
      unsigned int i = 0U;
      assert(oSymTable);
      assert(pfApply);

      while (i < S_o_HASH)
      {
          tmp=oSymTable->table[i];
          i++;
      }

	if(tmp != NULL) pfApply(tmp->key,&(tmp->value),(void*)pvExtra);
}
