#include <stdlib.h>
#include <string.h>

#include "slist.h"

/*
 * slist_init: initialize a list
 *
 */
void slist_init(SList *slist, void (*destroy)(void *data))
{
	slist->size = 0;
	slist->destroy = destroy;
	slist->head = NULL;
	slist->tail = NULL;

	return;
}

/*
 * slist_destroy: remove each element
 *
 */
void slist_destroy(SList *slist)
{
	void *data;

	while(slist_size(slist) > 0)
	{
		if(slist_rem_next(slist, NULL, (void**)&data) == 0 &&
				slist->destroy != NULL)
		{
			slist->destroy(data);
		}
	}

	// prevent use after free
	memset(slist, 0, sizeof(SList));

	return;
}

int slist_ins_next(SList *slist, SListElmt *elmt, const void *data)
{
	SListElmt *new_elmt;

	if((new_elmt = (SListElmt*)malloc(sizeof(SListElmt))) == NULL)
		return -1;

	new_elmt->data = (void*)data;

	if(elmt == NULL)
	{
		if(slist_size(slist) == 0)
		{
			slist->tail = new_elmt;
		}

		new_elmt->next = slist->head;
		slist->head = new_elmt;
	}
	else
	{
		if(elmt->next == NULL)
			slist->tail = new_elmt;

		new_elmt->next = elmt->next;
		elmt->next = new_elmt;
	}

	slist->size++;

	return 0;	
}

int slist_rem_next(SList *slist, SListElmt *elmt, void **data)
{
	SListElmt *old_elmt;

	if(slist_size(slist) == 0)
		return -1;
	
	if(elmt == NULL)
	{
		*data = slist->head->data;
		old_elmt = slist->head;
		slist->head = slist->head->next;

		if(slist_size(slist) == 1)
			slist->tail = NULL;

	}
	else
	{
		if(elmt->next == NULL)
			return -1;

		*data = elmt->next->data;
		old_elmt = elmt->next;
		elmt->next = elmt->next->next;

		if(elmt->next == NULL)
			slist->tail = elmt;
	}

	free(old_elmt);
	slist->size--;

	return 0;
}
