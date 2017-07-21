/***********************************************************
 * Author:                       Romano Garza
 * Date Created:                 07/21/17
 * Last Modification Date:       07/21/17
 * Filename:                     linkedList.c
 *
 * Overview:
 *   This file contains the function definitions for a program
 *   that creates and modifies a linked list
 *
 *
 * Input:
 *   No input is required.
 *
 * Output:
 *   No output
 ************************************************************/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};


/*********************************************************************
** Function: init
**
** Description: allocates the list's sentinel and sets the size, the
**              along with both sentinels' next and prev pointers
**
** Parameters:  a pointer to a list structure
**
** Pre-Conditions:  NONE
** Post-Conditions: space allocated for front and back sentinels 
**                  front points to back and back points to front 
**                   <-front <=> back ->
********************************************************************/
static void init(struct LinkedList* list) {
	// malloc both sentinels
    list->frontSentinel =(struct Link*)malloc(sizeof(struct Link));
    list->backSentinel = (struct Link*)malloc(sizeof(struct Link));
    
    // assert malloc occured properly
    assert(list->frontSentinel!=0);
    assert(list->backSentinel!=0);
    
    // set front and back pointing to each other
    // with front's previous pointing to null
    // and back's next pointing to null 
    list->frontSentinel->next = list->backSentinel;
    list->backSentinel->prev = list->frontSentinel;
    list->size = 0;
    
}




/*********************************************************************
** Function: addLinkBefore
**
** Description: adds a newl link with the given value before the given
**              link and increments the list's size
**
** Parameters: a List, Link, and value
**
** Pre-Conditions:  both the list and the link have space allocated for
**                  them
** Post-Conditions: space has been allocated for a new link, the new
**                  link has been positioned before the
*********************************************************************/
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value){
    
    // assert list and link are not null
    assert(list && link);
    
    // malloc room for new link
    struct Link* new = malloc(sizeof(struct Link));
    assert(new!=0);
    // assign value to new link
    new->value = value;
    
    // store old link previous in temp
    struct Link* temp = link->prev;
    
    assert(temp!=0);
    // position new link before old link
    new->prev = temp;
    new->next = link;
    link->prev = new;
    temp->next = new;
    
    // incremenet size
    list->size++;
}



/*********************************************************************
** Function: removeLink
**
** Description: removes the given link from the list and decrements
**              the list's size
**
** Parameters: a list and Link
**
** Pre-Conditions:  both the list and the link have space allocated for
**                  them
** Post-Conditions: the link is freed, the previous and next links of 
**                  the freed link are now pointing to each other
*********************************************************************/
static void removeLink(struct LinkedList* list, struct Link* link)
{
    // assert list and link are not null
    assert(list && link);
    
    // store links previous and next
    struct Link*tempPrev = link->prev;
    struct Link*tempNext = link->next;
    
    // free the link
    free(link);
    
    // set stored links to point to each other
    tempPrev->next = tempNext;
    tempNext->prev = tempPrev;
    
    //decrement the list size
    list->size--;
}




/*********************************************************************
** Function: linkedListCreate
**
** Description: allocates and initializes a list
**
** Parameters: none
**
** Pre-Conditions:  none
** Post-Conditions: space for a new list has been allocated space for 
**                  the sentinels has been allocated, and the new list
**                  is returned
*********************************************************************/
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}




/*********************************************************************
** Function: linkedListDestroy
**
** Description: deallocates every link in the list including the sentinels
**               and frees the list itself
**
** Parameters: a list
**
** Pre-Conditions:  the passed list has been initialized
** Post-Conditions: each link in the list has been freed and the list
**                  itself has been freed
*********************************************************************/
void linkedListDestroy(struct LinkedList* list)
{
    assert(list!=0);
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
    assert(list->frontSentinel!=0);
    assert(list->backSentinel!=0);
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}



/*********************************************************************
** Function: addLinkBefore
**
** Description: adds a new link to the front of the list
**
** Parameters: a list and value
**
** Pre-Conditions:  list has been initialized
** Post-Conditions: space has been allocated for a new link, the new
**                  link has been positioned after the front sentinel
*********************************************************************/
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
    
    addLinkBefore(list, list->frontSentinel->next, value);
    
}



/*********************************************************************
** Function: linkedListAddBack
**
** Description: adds a new link to the back of the list
**
** Parameters: a list and value
**
** Pre-Conditions:  list has been initialized
** Post-Conditions: space has been allocated for a new link, the new
**                  link has been positioned before the back sentinel
*********************************************************************/
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
    addLinkBefore(list, list->backSentinel, value);
}




/*********************************************************************
** Function: linkedListFront
**
** Description: returns the link at the front of the list
**
** Parameters: a list
**
** Pre-Conditions:  list has been initialized, list has items links other
**                  than the sentinels
** Post-Conditions: returns the value of the link at the front
*********************************************************************/
TYPE linkedListFront(struct LinkedList* list)
{
    assert(list!=0);
    assert(list->frontSentinel->next!= list->backSentinel);
    return list->frontSentinel->next->value;
}




/*********************************************************************
** Function: linkedListFront
**
** Description: returns the link at the front of the list
**
** Parameters: a list
**
** Pre-Conditions:  list has been initialized, list has links other
**                  than the sentinels
** Post-Conditions: returns the value of the link at the front
*********************************************************************/
TYPE linkedListBack(struct LinkedList* list)
{
    assert(list!=0);
    assert(list->backSentinel->prev!= list->frontSentinel);
    return list->backSentinel->prev->value;
}



/*********************************************************************
** Function: linkedListRemoveFront
**
** Description: removes the link at the front of the list
**
** Parameters: a list
**
** Pre-Conditions:  list has been initialized, list has links other
**                  than the sentinels
** Post-Conditions: removes the link at the front
*********************************************************************/
void linkedListRemoveFront(struct LinkedList* list)
{
    assert(list!=0);
    assert(list->frontSentinel->next!= list->backSentinel);
    removeLink(list, list->frontSentinel->next);
}




/*********************************************************************
** Function: linkedListRemoveBack
**
** Description: removes the link at the back of the list
**
** Parameters: a list
**
** Pre-Conditions:  list has been initialized, list has links other
**                  than the sentinels
** Post-Conditions: removes the link at the back of the list
*********************************************************************/
void linkedListRemoveBack(struct LinkedList* list)
{
    assert(list!=0);
    assert(list->backSentinel->prev != list->frontSentinel);
    removeLink(list, list->backSentinel->prev);
}





/*********************************************************************
** Function: linkedListIsEmpty
**
** Description: returns 1 if link is empty, 0 if not
**
** Parameters: a list
**
** Pre-Conditions:  list has been initialized
** Post-Conditions: returns 1 or 0
********************************************************************/
int linkedListIsEmpty(struct LinkedList* list)
{
    if(list->size == 0) return 1;
    else return 0;
}





/*********************************************************************
** Function: linkedListPrint
**
** Description: prints the entire list
**
** Parameters: a list
**
** Pre-Conditions:  list has been initialized
** Post-Conditions: all links have been printf'd
*********************************************************************/
void linkedListPrint(struct LinkedList* list)
{
    assert(list!=0);
    // start with value at the front
    struct Link* temp = list->frontSentinel->next;
    
    // stop when temp is the back sentinel
    while(temp!= list->backSentinel){
        // print the value of the link
        printf("%d ", temp->value);
        
        // move on to the next link
        temp = temp->next;
    }
    printf("\n");
}






/*********************************************************************
** Function: linkedListAdd
**
** Description: adds a link to the list
**
** Parameters: a list and value
**
** Pre-Conditions:  list has been initialized
** Post-Conditions: link has been added
*********************************************************************/
void linkedListAdd(struct LinkedList* list, TYPE value)
{
    linkedListAddBack(list, value);
}




/*********************************************************************
** Function: linkedListContains
**
** Description: searchs the list for a value
**
** Parameters: a list and value
**
** Pre-Conditions:  list has been initialized
** Post-Conditions: returns 1 if value is found and 0 if not
*********************************************************************/
int linkedListContains(struct LinkedList* list, TYPE value)
{
    assert(list!=0);
    struct Link* temp = list->frontSentinel->next;
    while(temp!= list->backSentinel){
        if(EQ(value, temp->value)) return 1;
        temp = temp->next;
    }
    
    return 0;
    
}

/*********************************************************************
** Function: linkedListREMOVE
**
** Description: removes first instance of a link with the value passed
**
** Parameters: a list and value
**
** Pre-Conditions:  list has been initialized
** Post-Conditions: if value is in list then the first instance of the 
**                  value is removed
*********************************************************************/
void linkedListRemove(struct LinkedList* list, TYPE value)
{
    assert(list!=0);
    struct Link* temp = list->frontSentinel->next;

    while(temp!= list->backSentinel){
        if(temp->value == value){
            removeLink(list, temp);
            break;
        }
        temp = temp->next;
    }
}
