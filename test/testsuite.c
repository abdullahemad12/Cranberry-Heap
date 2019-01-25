#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <time.h>
#include <stdlib.h>
#include <cranbheap.h>

static int comparator(void* arg0, void* arg1)
{
	int x = *((int*) arg0);
	int y = *((int*) arg1);
	if(x < y)
	{
		return -1;
	}
	else if(x > y)
	{
		return 1;
	}
	return 0;
}

void cbh_create_test1(void)
{
	struct cranbheap* cbh = cbh_create(NULL);
	CU_ASSERT_PTR_NULL(cbh);
	if(cbh != NULL)
	{
		cbh_destroy(cbh);
	}

}
void cbh_create_test2(void)
{
	struct cranbheap* cbh = cbh_create(comparator);
	CU_ASSERT_PTR_NOT_NULL_FATAL(cbh);
	CU_ASSERT_PTR_NULL(cbh->cbh_objects);
	CU_ASSERT_PTR_NOT_NULL(cbh->cbh_comparator);
	CU_ASSERT_EQUAL(cbh->cbh_length, 0);
	CU_ASSERT_EQUAL(cbh->cbh_size, 0);
	cbh_destroy(cbh);
}


/*****************************
 * before and after functions*
 *****************************/

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite(void)
{
	return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite(void)
{
	return 0;
}