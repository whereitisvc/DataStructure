#include<stdio.h>
#include<stdlib.h>

	typedef struct node 
	   {
	    void*        dataPtr;
	    struct node* link;
	   } NODE; 

	typedef struct list
	   {
	    int   count; 
	    NODE* pos;
	    NODE* head; 
	    NODE* rear;
	    int    (*compare) (void* argu1, void* argu2); 
	   } LIST; 
	
//	Prototype Declarations 
	LIST* createList   (void);
	LIST* destroyList  (LIST* list);

	int   addNode   (LIST* pList, void* dataInPtr);

	bool  removeNode   (LIST*  pList,
	                    void*  keyPtr,
	                    void** dataOutPtr);

	bool  searchList   (LIST*  pList,
	                    void*  pArgu,
	                    void** pDataOut);

	static bool  retrieveNode (LIST*  pList,
	                    void*  pArgu,
	                    void** dataOutPtr);

	bool  traverse     (LIST*  pList,
	                    int    fromWhere,
	                    void** dataOutPtr);

	int   listCount    (LIST*  pList);
	bool  emptyList    (LIST*  pList);
	bool  fullList     (LIST*  pList); 

	static bool _insert   (LIST* pList,
	                      NODE* pPre,
	                      void* dataInPtr);

	static void _delete  (LIST*  pList,
	                      NODE*  pPre,
	                      NODE*  pLoc,
	                      void** dataOutPtr);
	static bool _search  (LIST*  pList,
	                      NODE** pPre,
	                      NODE** pLoc,
	                      void*  pArgu);
	                      
//	End of List ADT Definitions 


//

LIST* createList (void)
{
//	Local Definitions 
	LIST* list;

//	Statements 
	list = (LIST*) malloc(sizeof (LIST));
	if (list)
	   {
	    list->head    = NULL;
	    list->pos     = NULL;
	    list->rear    = NULL;
	    list->count   = 0;
	    //list->compare = compare;
	   } // if 

	return list;
}	// createList 

int addNode (LIST* pList, void* dataInPtr)
{
    NODE* newp = (NODE*)malloc(sizeof(NODE));
    newp->dataPtr = dataInPtr;
    newp->link = NULL;
    
    if( pList->rear == NULL )
    {
        pList->head = newp;
        pList->rear = newp;
        pList->count++;
    }    
    else
    {
        pList->rear->link = newp;
        pList->rear = newp;
        pList->count++;
    }
    
    /*
//	Local Definitions 
	bool found;
	bool success;
	
	NODE* pPre;
	NODE* pLoc;
	
//	Statements 
	found = _search (pList, &pPre, &pLoc, dataInPtr);
	if (found)
	   // Duplicate keys not allowed 
	   return (+1);

	success = _insert (pList, pPre, dataInPtr);
	if (!success)
	   // Overflow 
	   return (-1);
	return (0);*/
}	// addNode 

static bool _insert (LIST* pList, NODE* pPre,
                     void* dataInPtr)
{
//	Local Definitions 
	NODE* pNew;

//	Statements 
	if (!(pNew = (NODE*) malloc(sizeof(NODE))))
	   return false;

	pNew->dataPtr   = dataInPtr; 
	pNew->link      = NULL; 
 
	if (pPre == NULL)
	   {
	    // Adding before first node or to empty list. 
	    pNew->link       = pList->head;
	    pList->head      = pNew;
	    if (pList->count == 0)
	       // Adding to empty list. Set rear 
	       pList->rear = pNew;
	   } // if pPre 
	else
	   {
	    // Adding in middle or at end 
	    pNew->link  = pPre->link;
	    pPre->link  = pNew;
 
	    // Now check for add at end of list 
	    if (pNew->link     == NULL)
	         pList->rear   =  pNew;
	   } // if else 

	(pList->count)++;
	return true;
}	// _insert 

bool removeNode  (LIST*  pList, void*  keyPtr,
                  void** dataOutPtr)
{
//	Local Definitions 
	bool found;
	
	NODE* pPre;
	NODE* pLoc;
	
//	Statements 
	found = _search (pList, &pPre, &pLoc, keyPtr);
	if (found)
	   _delete (pList, pPre, pLoc, dataOutPtr);
	
	return found;
}	// removeNode 

void _delete (LIST* pList, NODE*  pPre,
              NODE* pLoc,  void** dataOutPtr)
{
//	Statements 
	*dataOutPtr = pLoc->dataPtr;
	if (pPre == NULL)
	   // Deleting first node 
	   pList->head = pLoc->link;
	else
	   // Deleting any other node 
	   pPre->link = pLoc->link;
	 
	// Test for deleting last node 
	if (pLoc->link == NULL)
	    pList->rear = pPre;

	(pList->count)--;
	free (pLoc);

	return;
}	// _delete 

bool searchList (LIST*  pList, void* pArgu,
                 void** pDataOut)
{
//	Local Definitions 
	bool  found;
	
	NODE* pPre;
	NODE* pLoc;

//	Statements 
	found = _search (pList, &pPre, &pLoc, pArgu);
	if (found)
	    *pDataOut = pLoc->dataPtr;
	else
	    *pDataOut = NULL;
	return found;
}	// searchList 

bool _search (LIST*  pList, NODE** pPre,
              NODE** pLoc,  void*  pArgu)
{
//	Macro Definition 
#define COMPARE \
	( ((* pList->compare) (pArgu, (*pLoc)->dataPtr)) )

#define COMPARE_LAST \
	((* pList->compare) (pArgu, pList->rear->dataPtr))

//	Local Definitions 
	int result;
	
//	Statements 
	*pPre  = NULL;
	*pLoc  = pList->head;
	if (pList->count == 0)
	    return false;
	
	// Test for argument > last node in list 
	if ( COMPARE_LAST > 0) 
	   {
	    *pPre = pList->rear;
	    *pLoc = NULL;
	    return false;
	   } // if 

	while ( (result = COMPARE) > 0 )
	   {
	    // Have not found search argument location 
	    *pPre = *pLoc;
	    *pLoc = (*pLoc)->link;
	   } // while 
	
	if (result == 0)
	   // argument found--success 
	   return true;
	else
	   return false;
}	// _search 

static bool retrieveNode (LIST*  pList,
                          void*  pArgu, 
                          void** dataOutPtr)
{
//	Local Definitions 
	bool  found;
	
	NODE* pPre;
	NODE* pLoc;
	
//	Statements 
	found = _search (pList, &pPre, &pLoc, pArgu);
	if (found)
	   {
	    *dataOutPtr = pLoc->dataPtr;
	    return true;
	   } // if 

	*dataOutPtr = NULL;
	return false;
}	// retrieveNode 

bool emptyList (LIST* pList) 
{
//	Statements 
	return (pList->count == 0);
}	// emptyList 



bool traverse (LIST*  pList,
              int    fromWhere,
              void** dataPtrOut)
{
//	Statements 
	if (pList->count == 0)
	    return false;

	if (fromWhere == 0)
	   {
		 //Start from first node 
	    pList->pos  = pList->head;
	    *dataPtrOut = pList->pos->dataPtr;
	    return true;
	   } // if fromwhere 
	else
	   {
	    // Start from current position 
	    if (pList->pos->link == NULL)
	        return false;
	    else
	       {
	        pList->pos  = pList->pos->link;
	        *dataPtrOut = pList->pos->dataPtr;
	        return true;
	       } // if else 
	   } // if fromwhere else 
}	// traverse 

bool fullList (LIST* pList) 
{
//	Local Definitions 
NODE* temp;

//	Statements 
	if ((temp = (NODE*)malloc(sizeof(*(pList->head)))))
	   {
	    free (temp);
	    return false;
	   } // if 

	// Dynamic memory full 
	return true;

}	// fullList 

int listCount(LIST* pList) 
{
//	Statements 

	return pList->count; 
	
}	// listCount 

LIST* destroyList (LIST* pList) 
{
//	Local Definitions 
	NODE* deletePtr;

//	Statements 
	if (pList)
	   {
	    while (pList->count > 0) 
	       {
	        // First delete data 
	        free (pList->head->dataPtr);
 
	        // Now delete node 
	        deletePtr    = pList->head;
	        pList->head  = pList->head->link; 
	        pList->count--;
	        free (deletePtr); 
	       } // while 
	    free (pList);
	   } // if 
	return NULL;
}	// destroyList 

