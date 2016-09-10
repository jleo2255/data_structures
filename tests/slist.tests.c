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

Test(slist, insert_into_empty_after_elem, .init = setup, .fini = teardown)
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
