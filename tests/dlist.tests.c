#include "../src/dlist.h"
#include <criterion/criterion.h>

DList *list;

void dlist_setup(void)
{
	list = (DList*)malloc(sizeof(DList));
	dlist_init(list, free);
}

void dlist_teardown(void)
{
	dlist_destroy(list);
}

Test(dlist, initialization, .init = dlist_setup, .fini = dlist_teardown)
{
	cr_assert(list->size == 0, "newly initialized does not have 0 size.");
	cr_assert(list->head == NULL, "newly initialized list must have NULL head.");
	cr_assert(list->tail == NULL, "newly initialized list must have NULL tail.");
}

Test(dlist, insert_into_empty_at_head, .init = dlist_setup, .fini = dlist_teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;

	dlist_ins_next(list, NULL, mallocd_int);

	cr_assert(list->size == 1, "list should have size 1 after insert.");
	cr_assert(list->head->data == mallocd_int, "head data should be set to malloc\'d int.");
	cr_assert(list->tail->data == mallocd_int, "tail data should be set to malloc\'d int.");
	cr_assert(*(int*)(list->head->data) == 5, "head data should point to correct value.");
	cr_assert(*(int*)(list->tail->data) == 5, "tail data should point to correct value.");
}

Test(dlist, insert_after_elem, .init = dlist_setup, .fini = dlist_teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;
	dlist_ins_next(list, NULL, mallocd_int);

	int *mallocd_int_2 = (int*)malloc(sizeof(int));
	*mallocd_int_2 = 6;
	dlist_ins_next(list, list->tail, mallocd_int_2);

	cr_assert(list->size == 2, "list should have size 2 after insert.");
	cr_assert(list->head->data == mallocd_int, "head data should be set to malloc\'d int.");
	cr_assert(list->tail->data == mallocd_int_2, "tail data should be set to malloc\'d int 2.");
	cr_assert(*(int*)(list->head->data) == 5, "head data should point to correct value.");
	cr_assert(*(int*)(list->tail->data) == 6, "tail data should point to correct value.");
	cr_assert(list->tail->next == NULL, "tail next should be NULL.");
}

Test(dlist, remove_after_elem, .init = dlist_setup, .fini = dlist_teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;
	dlist_ins_next(list, NULL, mallocd_int);

	int *mallocd_int_2 = (int*)malloc(sizeof(int));
	*mallocd_int_2 = 6;
	dlist_ins_next(list, list->tail, mallocd_int_2);

	int *removed_elmt = NULL;
	int rem_status = dlist_remove(list, list->tail, (void**)&removed_elmt);

	cr_assert(rem_status == 0, "remove should complete successfully.");
	cr_assert(list->size == 1, "list should have size 1 after remove but was %d.", list->size);
	cr_assert(list->head->data == mallocd_int, "head data should be set to malloc\'d int.");
	cr_assert(list->head->next == NULL, "Next elmt from head should be null.");
	cr_assert(list->tail == list->head, "Tail should be set to head.");
	cr_assert(*(int*)(list->head->data) == 5, "head data should point to correct value.");
}

Test(dlist, insert_100_after_elem, .init = dlist_setup, .fini = dlist_teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;
	dlist_ins_next(list, NULL, mallocd_int);

	int *mallocd_int_2 = NULL; 

	for(int i = 0; i < 100; i++)
	{
		mallocd_int_2 = (int*)malloc(sizeof(int));
		*mallocd_int_2 = i;
		dlist_ins_next(list, list->tail, mallocd_int_2);
	}

	cr_assert(list->size == 101, "list should have size 101 after insert.");
	cr_assert(list->head->data == mallocd_int, "head data should be set to malloc\'d int.");
	cr_assert(list->tail->data == mallocd_int_2, "tail data should be set to malloc\'d int 2.");
	cr_assert(*(int*)(list->head->data) == 5, "head data should point to correct value.");
	cr_assert(*(int*)(list->tail->data) == 99, "tail data should point to correct value.");
}

Test(dlist, rem_all, .init = dlist_setup, .fini = dlist_teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;
	dlist_ins_next(list, NULL, mallocd_int);

	int *mallocd_int_2 = NULL; 

	// insert 100 items to remove
	for(int i = 1; i < 101; i++)
	{
		mallocd_int_2 = (int*)malloc(sizeof(int));
		*mallocd_int_2 = i;
		dlist_ins_next(list, list->tail, mallocd_int_2);
	}

	// remove 100 items from head of list
	for(int i = 0; i < 101; i++)
	{
		int *removed_elmt = NULL;
		int rem_status = dlist_remove(list, list->head, (void**)&removed_elmt);

		int expected_removed_elmt = i == 0 ? 5 : i;
		cr_assert(rem_status == 0, "remove should be successful");
		cr_assert(*removed_elmt == expected_removed_elmt, "Expected removed elmt to be %d but was %d", i, *removed_elmt); 
	}

	cr_assert(list->size == 0, "list should be empty.");
}

Test(dlist, foreach_iterates_correctly, .init = dlist_setup, .fini = dlist_teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;
	dlist_ins_next(list, NULL, mallocd_int);

	int *mallocd_int_2 = NULL; 

	// insert 100 items to remove
	for(int i = 0; i < 100; i++)
	{
		mallocd_int_2 = (int*)malloc(sizeof(int));
		*mallocd_int_2 = i;
		dlist_ins_next(list, list->tail, mallocd_int_2);
	}

	cr_assert(list->size == 101, "list should have 101 els");

	int i = 0;

	dlist_foreach(data, int, list)
	{
		cr_assert(data == i == 0 ? 5 : (i-1), "data has corrected value when iterated.");
		i++;
	}
}

Test(dlist, foreach_reverse_iterates_correctly, .init = dlist_setup, .fini = dlist_teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;
	dlist_ins_next(list, NULL, mallocd_int);

	int *mallocd_int_2 = NULL; 

	// insert 100 items to remove
	for(int i = 0; i < 100; i++)
	{
		mallocd_int_2 = (int*)malloc(sizeof(int));
		*mallocd_int_2 = i;
		dlist_ins_next(list, list->tail, mallocd_int_2);
	}

	cr_assert(list->size == 101, "list should have 101 els");

	int i = 100;

	dlist_foreach_reverse(data, int, list)
	{
		cr_assert(data == i == 0 ? 5 : i, "data has corrected value when iterated.");
		i--;
	}
}
