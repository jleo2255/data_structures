#include "../src/slist.h"
#include <criterion/criterion.h>

SList *list;

void setup(void)
{
	list = (SList*)malloc(sizeof(SList));
	slist_init(list, free);
}

void teardown(void)
{
	slist_destroy(list);
}

Test(slist, initialization, .init = setup, .fini = teardown)
{
	cr_assert(list->size == 0, "newly initialized does not have 0 size.");
	cr_assert(list->head == NULL, "newly initialized list must have NULL head.");
	cr_assert(list->tail == NULL, "newly initialized list must have NULL tail.");
}

Test(slist, insert_into_empty_at_head, .init = setup, .fini = teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;

	slist_ins_next(list, NULL, mallocd_int);

	cr_assert(list->size == 1, "list should have size 1 after insert.");
	cr_assert(list->head->data == mallocd_int, "head data should be set to malloc\'d int.");
	cr_assert(list->tail->data == mallocd_int, "tail data should be set to malloc\'d int.");
	cr_assert(*(int*)(list->head->data) == 5, "head data should point to correct value.");
	cr_assert(*(int*)(list->tail->data) == 5, "tail data should point to correct value.");
}

Test(slist, remove_one_at_head, .init = setup, .fini = teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;

	slist_ins_next(list, NULL, mallocd_int);

	int *removed_elmt = NULL;
	slist_rem_next(list, NULL, (void**)&removed_elmt);

	cr_assert(list->size == 0, "list should be empty.");
	cr_assert(list->head == NULL, "head should be null.");
	cr_assert(list->tail == NULL, "tail should be null.");
	cr_assert(*removed_elmt == 5, "removed_elmt value should be correct.");
}

Test(slist, insert_after_elem, .init = setup, .fini = teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;
	slist_ins_next(list, NULL, mallocd_int);

	int *mallocd_int_2 = (int*)malloc(sizeof(int));
	*mallocd_int_2 = 6;
	slist_ins_next(list, list->tail, mallocd_int_2);

	cr_assert(list->size == 2, "list should have size 2 after insert.");
	cr_assert(list->head->data == mallocd_int, "head data should be set to malloc\'d int.");
	cr_assert(list->tail->data == mallocd_int_2, "tail data should be set to malloc\'d int 2.");
	cr_assert(*(int*)(list->head->data) == 5, "head data should point to correct value.");
	cr_assert(*(int*)(list->tail->data) == 6, "tail data should point to correct value.");
	cr_assert(list->tail->next == NULL, "tail next should be NULL.");
}

Test(slist, remove_after_elem, .init = setup, .fini = teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;
	slist_ins_next(list, NULL, mallocd_int);

	int *mallocd_int_2 = (int*)malloc(sizeof(int));
	*mallocd_int_2 = 6;
	slist_ins_next(list, list->tail, mallocd_int_2);

	int *removed_elmt = NULL;
	int rem_status = slist_rem_next(list, list->head, (void**)&removed_elmt);

	cr_assert(rem_status == 0, "remove should complete successfully.");
	cr_assert(list->size == 1, "list should have size 1 after remove but was %d.", list->size);
	cr_assert(list->head->data == mallocd_int, "head data should be set to malloc\'d int.");
	cr_assert(list->tail->data == mallocd_int, "tail data should be set to malloc\'d int.");
	cr_assert(*(int*)(list->head->data) == 5, "head data should point to correct value.");
	cr_assert(*(int*)(list->tail->data) == 5, "tail data should point to correct value.");
}

Test(slist, insert_100_after_elem, .init = setup, .fini = teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;
	slist_ins_next(list, NULL, mallocd_int);

	int *mallocd_int_2 = NULL; 

	for(int i = 0; i < 100; i++)
	{
		mallocd_int_2 = (int*)malloc(sizeof(int));
		*mallocd_int_2 = i;
		slist_ins_next(list, list->tail, mallocd_int_2);
	}

	cr_assert(list->size == 101, "list should have size 101 after insert.");
	cr_assert(list->head->data == mallocd_int, "head data should be set to malloc\'d int.");
	cr_assert(list->tail->data == mallocd_int_2, "tail data should be set to malloc\'d int 2.");
	cr_assert(*(int*)(list->head->data) == 5, "head data should point to correct value.");
	cr_assert(*(int*)(list->tail->data) == 99, "tail data should point to correct value.");
}

Test(slist, rem_all_but_head, .init = setup, .fini = teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;
	slist_ins_next(list, NULL, mallocd_int);

	int *mallocd_int_2 = NULL; 

	// insert 100 items to remove
	for(int i = 0; i < 100; i++)
	{
		mallocd_int_2 = (int*)malloc(sizeof(int));
		*mallocd_int_2 = i;
		slist_ins_next(list, list->tail, mallocd_int_2);
	}

	// remove 100 items from head of list
	for(int i = 0; i < 100; i++)
	{
		int *removed_elmt = NULL;
		int rem_status = slist_rem_next(list, list->head, (void**)&removed_elmt);

		cr_assert(rem_status == 0, "remove should be successful");
		cr_assert(*removed_elmt == i, "Expected removed elmt to be %d but was %d", i, *removed_elmt); 
	}

	cr_assert(list->size == 1, "list should only have head left");
}

Test(slist, foreach_iterates_correctly, .init = setup, .fini = teardown)
{
	int *mallocd_int = (int*)malloc(sizeof(int));
	*mallocd_int = 5;
	slist_ins_next(list, NULL, mallocd_int);

	int *mallocd_int_2 = NULL; 

	// insert 100 items to remove
	for(int i = 0; i < 100; i++)
	{
		mallocd_int_2 = (int*)malloc(sizeof(int));
		*mallocd_int_2 = i;
		slist_ins_next(list, list->tail, mallocd_int_2);
	}

	cr_assert(list->size == 101, "list should have 101 els");

	int i = 0;

	slist_foreach(data, int, list)
	{
		cr_assert(data == i == 0 ? 5 : (i-1), "data has corrected value when iterated.");
		i++;
	}
}
