/***********************************************************
* Author:                       Romano Garza
* Date Created:                 07/21/17
* Last Modification Date:       07/21/17
* Filename:                     linkedList.c
*
* Overview:
*   This file contains the function definitions for a program
*   that creates and modifies a circular linked list
*
*
* Input:
*   No input is required.
*
* Output:
*   No output
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
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
** Post-Conditions: space allocated for the front/back sentinel
**                  sentinel points to itself
********************************************************************/
static void init(struct CircularList* list)
{
	// FIXME: you must write this
    list->sentinel= (struct Link*)malloc(sizeof(struct Link));
    
    // assert malloc occured properly
    assert(list->sentinel);
    
    // set sentinel to poin to itself
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
    list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */

/*********************************************************************
** Function: createLink
**
** Description: creates a link with the given value and NULL next and
**              prev pointers
**
** Parameters:  a value
**
** Pre-Conditions:  NONE
** Post-Conditions: space allocated for new Link with the passed value
********************************************************************/
static struct Link* createLink(TYPE value)
{
    // allocate memory for newLink
    struct Link * newLink = (struct Link*)malloc(sizeof(struct Link));
    
    // assert memory allocated properly
    assert(newLink!=0);
    
    newLink->value = value;
    
    return newLink;
}


/*********************************************************************
** Function: addLinkAfter
**
** Description: adds a new link with the given value after the given
**              link and increments the list's size
**
**
** Parameters:  a CircularList, Link, and value
**
** Pre-Conditions: list and link are both initialized
** Post-Conditions: new link with given value is added after passed 
**                  link
********************************************************************/
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// check pre-conditions
    assert(list!=0 && link!=0);
    
    // create link
    struct Link * newLink = createLink(value);
    
    // store link next value in temp
    struct Link * temp = link->next;
    
    // old next points back to newLink
    temp->prev = newLink;
    // new link points next to old next
    newLink->next = temp;
    
    // passed link points next to newLink
    link->next = newLink;
    
    // new link points back to passed link
    newLink->prev = link;
    
    list->size++
}


/*********************************************************************
** Function: removeLink
**
** Description: removes the given link from the list and
** decrements the list's size
**
**
** Parameters:  a CircularList and Link
**
** Pre-Conditions: list and link are both initialized
** Post-Conditions: link has been removed
**                  
********************************************************************/
static void removeLink(struct CircularList* list, struct Link* link)
{
	//check pre-conditions
    assert(list!=0 && link!=0);
    
    // store links next and previous values;
    struct Link * tempN = link->next;
    struct Link * tempP = link->prev;
    
    // free the link
    free(link);
    
    // set temps to point to each other
    tempN->prev = tempP;
    tempP->next = tempN;
    
    list->size--;
    
}

/*********************************************************************
** Function: circularListCreate
**
** Description: allocates and initializes a list
**
**
** Parameters:  none
**
** Pre-Conditions: none
** Post-Conditions: returns an allocated and initiallized list
**                  link
********************************************************************/
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/*********************************************************************
** Function: circularListDestroy
**
** Description: destroys a CircularList
**
** Parameters:  a CircularListn
**
** Pre-Conditions: the passed list has space allocated for it
** Post-Conditions: list has been destroyed all allocated mem locations
**                  have been freed
********************************************************************/
void circularListDestroy(struct CircularList* list)
{
	// check that list is not null
    assert(list!=0);
    
    // remove all links
    struct Link* temp = list->sentinel->next;
    
    while(temp != list->sentinel){
        removeLink(list, temp);
        temp = temp->next;
    }
    
    assert(list->sentinel!=0);
    free(list->sentinel);
    free(list);
}


/*********************************************************************
** Function: circularListAddFront
** Description: adds a new link with the given value to the front of 
**              the deque
**
**
** Parameters:  a CircularList and Value
**
** Pre-Conditions: the list has been initialized
** Post-Conditions: a link with the value passed has been positioned
**                  at the front
**
********************************************************************/
void circularListAddFront(struct CircularList* list, TYPE value)
{
    assert(list!=0);
    
    addLinkAfter(list, list->sentinel, value);
}

/*********************************************************************
** Function: circularListAddBack
** Description: adds a new link with the given value to the back of
**              the deque
**
**
** Parameters:  a CircularList and Value
**
** Pre-Conditions: the list has been initialized
** Post-Conditions: a link with the value passed has been positioned
**                  at the front
**
********************************************************************/
void circularListAddBack(struct CircularList* list, TYPE value)
{
    assert(list!=0);
    
    addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
	return 0;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
	return 0;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
	return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXME: you must write this
}
