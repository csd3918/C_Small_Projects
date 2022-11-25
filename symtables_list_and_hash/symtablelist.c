/*Creator: Vasileiadis George
        AM:3918
        Email:csd3918@csd.uoc.gr
        Date: 30-3-2021
        Assignment3
        File: ./src/symtablelist.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "symtable.h"

typedef struct bind
{
    char *key;
    void *value;
    struct bind *next;
}bind;

struct SymTable
{
    unsigned int numofbinds;
    bind *head;
};

/*
The function 'SymTable_new' return a new empty
SymTable_T  (it has no bindings)
*/
SymTable_T SymTable_new(void)
{
	SymTable_T table;
	table = malloc(sizeof(struct SymTable));
	assert(table != NULL);
	table->numofbinds=0;
	table->head = NULL;

	return table;
}

/*
 The function 'SymTable_free' frees all the memory that used from
  oSymTable. If 'oSymTable' == NULL, then the function does nothing.
*/
void SymTable_free(SymTable_T oSymTable)
{
	bind *temp;
	bind *temp2;
	assert(oSymTable);
	temp=oSymTable->head;

	/*runs through the list and frees every key, then frees every bind.*/
	while(temp != NULL)
    {
	      temp2 = temp->next;
	      free(temp->key);
	      free(temp);
	      temp = temp2;
	}
	free(oSymTable);
}

/*
The function 'SymTable_getLength' returns the number of bindings 
to oSymTable. It is a chacked runtime error of the program if oSymTable == NULL.
*/
unsigned int SymTable_getLength(SymTable_T oSymTable)
{
      assert(oSymTable);
      return oSymTable->numofbinds;
}

/* The function 'SymTable_put', if there is no binding with a key 'pcKey'
to oSymTable,  adds a new binding to oSymTable that consists of the key 'pcKey' 
and the value 'pvValue', returns 1 (TRUE).Otherwise, the function does not change the oSymTable,
returns 0 (FALSE).It is checked runtime error if oSymTable or pcKey is NULL. */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
      bind *newbind;
      assert(oSymTable);
      assert(pcKey);

	  /*if the element exists we don't add it.*/
      if(SymTable_contains(oSymTable,pcKey) == 1) return 0;

	  /*otherwise we create a new bind and we add it to the head of the list*/
      newbind = malloc(sizeof(bind));
      assert(newbind);
      newbind->key = malloc((strlen(pcKey)+1)*sizeof(char));
      assert(newbind->key);
      strcpy(newbind->key,pcKey);
      newbind->value = (void*)pvValue;

      newbind->next = oSymTable->head;
      oSymTable->head = newbind;
      oSymTable->numofbinds++;
      return 1;
}

/* The function SymTable_remove , if there is a binding with 'pcKey' key 
in oSymTable, removes binding from oSymTable and returns 1 (TRUE). 
Otherwise, the function does not change oSymTable, and returns 0 (FALSE).
It is checked runtime error if oSymTable or pcKey is NULL. */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
      bind *temp1;
      bind *temp2;
      assert(oSymTable);
      assert(pcKey);

      if(SymTable_contains(oSymTable,pcKey) == 0) return 0;

      oSymTable->numofbinds--;
      temp1= oSymTable->head;
      temp2=temp1;

	  /*case that the head is NULL*/
      if(temp1==NULL) return 0;

     /*run through the list until na vroume to stoixeio pou theloume na diagrapsoume*/
      while(temp1 != NULL){
	  if(strcmp(temp1->key, pcKey)==0) break;
	  temp2=temp1;
	  temp1 = temp1->next;
      }
	   /*the element we want to eliminate is the head*/
      if(temp1==temp2)
	  {
	  oSymTable->head = temp1->next;
	  free(temp1->key);
	  free(temp1);
	  return 1;
      }
      else
	  {  /*any other element*/
	  temp2->next = temp1->next;
	  free(temp1->key);
	  free(temp1);
	  return 1;
      }
      return 0;

}
/* The function SymTable_contains returns 1 (TRUE) if oSymTable 
contains a binding, which its key is 'pcKey', 
or 0 (FALSE) if it does not contain one. It is a checked runtime error 
if oSymTable or pcKey is NULL. */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
	bind *temp;
	assert(pcKey);
	assert(oSymTable);
	temp=oSymTable->head;

	while(temp!=NULL)
	{
	  if(strcmp(pcKey,temp->key)==0) return 1;
	      temp = temp->next;
	}
	return 0;
}
/* The function SymTable_get returns the value of binding to oSymTable 
which its key is 'pcKey', or NULL, if there is not such a binding. 
It is a checked runtime error if oSymTable or pcKey is NULL. */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
	bind * temp;
	assert(pcKey);
	assert(oSymTable);
	temp=oSymTable->head;

	while(temp!=NULL){
	  if(strcmp(pcKey,temp->key)==0){
	    return (void *) temp->value;
	  }
	  temp = temp->next;
	}
	return NULL ;
}

/* The function SymTable_map applies the function *pfApply on every
binding in oSymTable, applying pvExtra as an extra parameter. 
It is checked runtime error if oSymTable or pfApply is NULL. */
void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra)
{
	bind *temp;
	assert(oSymTable);
	assert(pfApply);
	temp=oSymTable->head;

	/*run through the list and apply 'pfApply' in every element of the list*/
	while(temp!=NULL){
	  pfApply(temp->key,&(temp->value),(void*)pvExtra);
	  temp = temp->next;
	}
}
