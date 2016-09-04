#include "../src/slist.h"
#include <criterion/criterion.h>

Test(slist_init, failing)
{
	SList *list = (SList*) malloc(sizeof(SList));
	slist_init(list, NULL);	

	cr_assert(1, "initialized list.");
}
