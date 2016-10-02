#ifndef IDLIST_H
#define IDLIST_H

#include <stdlib.h>

/*
 * Doubly linked el structure
 */
typedef struct DListElmt_
{
	void				*data;
	struct DListElmt_	*prev;
	struct DListElmt_	*next;
} DListElmt;

/*
 * Doubly linked list structure
 */
typedef struct DList_
{
	int 				size;

	int					(*match)(const void *key1, const void *key2);
	void				(*destroy)(void *data);

	DListElmt 			*head;
	DListElmt 			*tail;

} DList;

/*
 * Public interface
 */

void dlist_init(DList *list, void (*destroy)(void *data));

void dlist_destroy(DList *list);

int dlist_ins_next(DList *list, DListElmt *elmt, const void *data);

int dlist_ins_prev(DList *list, DListElmt *elmt, const void *data);

int dlist_remove(DList *list, DListElmt *elmt, void **data);

#define dlist_size(list) ((list)->size)

#define dlist_head(list) ((list)->head)

#define dlist_tail(list) ((list)->tail)

#define dlist_is_head(elmt) ((elmt)->prev == NULL ? 1 : 0)

#define dlist_is_tail(elmt) ((elmt)->next == NULL ? 1 : 0)

#define dlist_data(elmt) ((elmt)->data)

#define dlist_next(elmt) ((elmt)->next)

#define dlist_prev(elmt) ((elmt)->prev)

#define dlist_foreach(data, datatype, list)\
	DListElmt *i_dlist_elmt;\
	datatype (data);\
	for(i_dlist_elmt = (list)->head, (data) = *(datatype*)(i_dlist_elmt->data);\
			i_dlist_elmt != NULL;\
			i_dlist_elmt = i_dlist_elmt->next, (data) = *(datatype*)(i_dlist_elmt->data))

#endif
