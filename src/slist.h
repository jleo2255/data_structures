#ifndef ISLIST_H
#define ISLIST_H

#include <stdlib.h>

/*
 * The defining struct for linked list elements
 *
 */

typedef struct SListElmt_
{

	void				 *data;
	struct SListElmt_	 *next; 

} SListElmt;

/*
 * The defining struct for a linked list
 *
 */

typedef struct SList_
{

	int			size;

	int			(*match)(const void *key1, const void *key2);
	void 		(*destroy)(void *data);

	SListElmt	*head;
	SListElmt	*tail;

} SList;

/*
 * public interface
 *
 */

void slist_init(SList *list, void (*destroy)(void *data));

void slist_destroy(SList *list);

int slist_ins_next(SList *list, SListElmt *elmt, const void *data);

int slist_rem_next(SList *list, SListElmt *elmt, void **data);

#define slist_size(list) ((list)->size)

#define slist_head(list) ((list)->head)

#define slist_tail(list) ((list)->tail)

#define slist_is_head(list, elmt) ((elmt) == (list)->head ? 1 : 0)

#define slist_is_tail(elmt) ((elmt)->next == NULL ? 1 : 0)

#define slist_data(elmt) ((elmt)->data)

#define slist_next(elmt) ((elmt)->next)

#define slist_foreach(data, datatype, list)\
	SListElmt *i_slist_elmt;\
	datatype (data);\
	for(i_slist_elmt = (list)->head, (data) = *(datatype*)(i_slist_elmt->data); i_slist_elmt != NULL; i_slist_elmt = i_slist_elmt->next, (data) = *(datatype*)(i_slist_elmt->data))

#endif
