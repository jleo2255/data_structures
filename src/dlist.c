#include <stdlib.h>
#include <string.h>
#include "dlist.h"

/*
 * Initialize a new Dlist
 */
void dlist_init(DList *list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	return;
}

/*
 * Free all memory associated with the list and remove all elements 
 */
void dlist_destroy(DList *list)
{
	void *data;

	while(dlist_size(list) > 0)
	{
		if(dlist_remove(list, dlist_tail(list), (void**)&data) == 0 && list->destroy != NULL)
		{
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(DList));
	
	return;
}

/*
 * Insert a new element after a specified one
 */
int dlist_ins_next(DList *list, DListElmt *elmt, const void *data)
{
	DListElmt *new_elmt;

	if(elmt == NULL && dlist_size(list) != 0) return -1;

	if((new_elmt = (DListElmt*)malloc(sizeof(DListElmt))) == NULL) return -1;

	new_elmt->data = (void*)data;

	if(dlist_size(list) == 0)
	{
		list->head = new_elmt;
		list->head->prev = NULL;
		list->tail = new_elmt;
		list->tail->prev = NULL;
	}
	else
	{
		new_elmt->next = elmt->next;
		new_elmt->prev = elmt;

		if(elmt->next == NULL) list->tail = new_elmt;
		else elmt->next->prev = new_elmt;

		elmt->next = new_elmt;
	}
	
	list->size++;

	return 0;
}

/*
 * Insert a new element before a specified one
 */
int dlist_ins_prev(DList *list, DListElmt *elmt, const void *data)
{
	DListElmt *new_elmt;

	if(elmt == NULL && dlist_size(list) == 0) return -1;

	if((new_elmt = (DListElmt*)malloc(sizeof(DListElmt))) == NULL) return -1;

	new_elmt->data = (void*)data;

	if(dlist_size(list) == 0)
	{
		list->head = new_elmt;
		list->tail = new_elmt;
		list->head->next = NULL;
		list->tail->next = NULL;
	}
	else
	{
		new_elmt->next = elmt;
		new_elmt->prev = elmt->prev;

		if(elmt->prev == NULL) list->head = elmt;
		else elmt->prev->next = new_elmt;

		elmt->prev = new_elmt;
	}

	list->size++;

	return 0;
}

/*
 * Remove an element from the list
 */
int dlist_remove(DList *list, DListElmt *elmt, void **data)
{
	if(elmt == NULL || dlist_size(list) == 0) return -1;

	*data = elmt->data;

	if(elmt == list->head)
	{
		list->head = elmt->next;

		if(list->head == NULL) list->tail = NULL;
		else elmt->next->prev = NULL;
	}
	else
	{
		elmt->prev->next = elmt->next;

		if(elmt->next == NULL) list->tail = elmt->prev;
		else elmt->next->prev = elmt->prev;
	}

	free(elmt);

	list->size--;

	return 0;
}
 
