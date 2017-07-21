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



/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Description:  allocates the list's sentinel and sets the size
*               the sentinels' next and prev should point to
*               each other or NULL as appropriate.
************************************************************/

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


/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     returns a pointer to 10 students
*
* Purpose:  removes the given link from the list and decrements
*           the list's size
************************************************************/
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


/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  allocates and initializes a list
************************************************************/
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}



/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  deallocates every link in the list including the
*           sentinels, and frees the list itself
************************************************************/
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}


/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  adds a new link to the front of a list
************************************************************/
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
    
    addLinkBefore(list, list->frontSentinel->next, value);
    
}


/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  adds a new link with the given value to the back
*           of the queue
************************************************************/
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
    addLinkBefore(list, list->backSentinel, value);
}



/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  returns the value of the link at the front of 
*           the deque
************************************************************/
TYPE linkedListFront(struct LinkedList* list)
{
    assert(list!=0);
    assert(list->frontSentinel->next!= list->backSentinel);
    return list->frontSentinel->next->value;
}




/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  returns the value of the link at hte back of the 
*           deque.
************************************************************/
TYPE linkedListBack(struct LinkedList* list)
{
    assert(list!=0);
    assert(list->backSentinel->prev!= list->frontSentinel);
    return list->backSentinel->prev->value;
}



/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  removes the link at the front of the deque.
************************************************************/
void linkedListRemoveFront(struct LinkedList* list)
{
    assert(list!=0);
    assert(list->frontSentinel->next!= list->backSentinel);
    removeLink(list, list->frontSentinel->next);
}



/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  removes the link at the back of the deque
************************************************************/
void linkedListRemoveBack(struct LinkedList* list)
{
    assert(list!=0);
    assert(list->backSentinel->prev != list->frontSentinel);
    removeLink(list, list->backSentinel->prev);
}




/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  returns 1 if the deque is empty and 0 otherwise
************************************************************/
int linkedListIsEmpty(struct LinkedList* list)
{
    if(list->size == 0) return 1;
    else return 0;
}




/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  prints the values of the links in the deque from 
*           front to back
************************************************************/
void linkedListPrint(struct LinkedList* list)
{
    assert(list!=0);
    struct Link* temp = list->frontSentinel->next;
    while(temp!= list->backSentinel){
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}





/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  adds a link with the given value to the bag
************************************************************/
void linkedListAdd(struct LinkedList* list, TYPE value)
{
    linkedListAddBack(list, value);
}




/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
* 
* Purpose:  returns 1 if a link with the value is in the bag
*           and 0 otherwise
************************************************************/
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

/***********************************************************
* Entry:    no entry is is requrired
*
* Exit:     nothing returned
*
* Purpose:  adds a new link with the given value before the
*           given link and increments the list's size
************************************************************/
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
