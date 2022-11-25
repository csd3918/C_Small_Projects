/*Creator: Vasileiadis George 
        AM:3918
        Email:csd3918@csd.uoc.gr
        Date: 30-3-2021
        Assignment3
        File: ./src/symtable.h
*/
/* Here we create the data type SymTable */
typedef struct SymTable *SymTable_T;
/*
The function 'SymTable_new' return a new empty
SymTable_T  (it has no bindings)
*/
SymTable_T SymTable_new(void);
/*
 The function 'SymTable_free' frees all the memory that used from
  oSymTable. If 'oSymTable' == NULL, then the function does nothing.
*/
void SymTable_free(SymTable_T oSymTable);
/*
The function 'SymTable_getLength' returns the number of bindings 
to oSymTable. It is a chacked runtime error of the program if oSymTable == NULL.
*/
unsigned int SymTable_getLength(SymTable_T oSymTable);
/*
The function 'SymTable_put', if there is no binding with a key 'pcKey'
to oSymTable,  adds a new binding to oSymTable that consists of the key 'pcKey' 
and the value 'pvValue', returns 1 (TRUE).Otherwise, the function does not 
change the oSymTable, returns 0 (FALSE).
It is checked runtime error if oSymTable or pcKey is NULL.
*/
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);
/*
The function SymTable_remove , if there is a binding with 'pcKey' key 
in oSymTable, removes binding from oSymTable and returns 1 (TRUE). 
Otherwise, the function does not change oSymTable, and returns 0 (FALSE).
It is checked runtime error if oSymTable or pcKey is NULL.
*/
int SymTable_remove(SymTable_T oSymTable, const char *pcKey);
/*
The function SymTable_contains returns 1 (TRUE) if oSymTable 
contains a binding, which its key is 'pcKey', 
or 0 (FALSE) if it does not contain one. It is a checked runtime error 
if oSymTable or pcKey is NULL.
*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);
/*
The function SymTable_get returns the value of binding to oSymTable 
which its key is 'pcKey', or NULL, if there is not such a binding. 
It is a checked runtime error if oSymTable or pcKey is NULL.
*/
void *SymTable_get(SymTable_T oSymTable, const char *pcKey);
/*
The function SymTable_map applies the function *pfApply on every
binding in oSymTable, applying pvExtra as an extra parameter. 
It is checked runtime error if oSymTable or pfApply is NULL.
*/
void SymTable_map(SymTable_T oSymTable, void(*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra);