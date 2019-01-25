#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "testsuite.c"

/*prototypes*/
static int init(void);
static int run_tests(void);

/*Array of all the tests*/
struct test
{
	const char *name;
	void (*func) (void);
};

static struct test utests[] = {
	{"cbh_create_test1", cbh_create_test1},
	{"cbh_create_test2", cbh_create_test2},
	{"cbh_insert_test1", cbh_insert_test1},
	{"cbh_insert_test2", cbh_insert_test2},
	{NULL, NULL}

};

int main(void)
{

	int err;

	/*initialize */
	err = init();
	if (err != CUE_SUCCESS)
	{
		return err;
	}
	/* Run all tests */
	return run_tests();

}

static int createSuite(const char *suite_name, struct test tests[])
{
	CU_pSuite pSuite = NULL;

	/* add a suite to the registry */
	pSuite = CU_add_suite(suite_name, init_suite, clean_suite);
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	for (int i = 0; tests[i].name != NULL && tests[i].func != NULL; i++)
	{
		if ((NULL == CU_add_test(pSuite, tests[i].name, tests[i].func)))
		{
			CU_cleanup_registry();
			return CU_get_error();
		}
	}
	return CUE_SUCCESS;
}

static int init(void)
{
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	int err = createSuite("Suite 1", utests);

	return err;

}

static int run_tests(void)
{
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
