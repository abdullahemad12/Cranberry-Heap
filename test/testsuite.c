#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <time.h>
#include <stdlib.h>
#include <cranbheap.h>


static void pickNRandomNumber(int arr[], int n);
static int pickRandomNumber(int lower, int upper);

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
	CU_ASSERT_PTR_NOT_NULL(cbh->cbh_objects);
	CU_ASSERT_PTR_NOT_NULL(cbh->cbh_comparator);
	CU_ASSERT_EQUAL(cbh->cbh_length, 0);
	CU_ASSERT_EQUAL(cbh->cbh_size, 1);
	cbh_destroy(cbh);
}


void cbh_insert_test1(void)
{
	struct cranbheap* cbh = cbh_create(comparator);
	int n = 12000000;
	int* arr = malloc(sizeof(int) * n);
	CU_ASSERT_PTR_NOT_NULL_FATAL(arr);
	pickNRandomNumber(arr,  n);
	for(int i = 0; i < n; i++)
	{
		cbh_insert(cbh, &arr[i]);
	}
	CU_ASSERT_PTR_NOT_NULL_FATAL(cbh->cbh_objects);
	CU_ASSERT_EQUAL(*((int*)&cbh->cbh_objects[0]), 0);

	free(arr);
	cbh_destroy(cbh);
}

void cbh_insert_test2(void)
{
	struct cranbheap* cbh = cbh_create(comparator);
	int n = 12000;
	int* arr = malloc(sizeof(int) * n);
	int min = INFINITY;
	for(int i = 0; i < n; i++)
	{	
		arr[i] = pickRandomNumber(-200000, 200000);
		cbh_insert(cbh, &arr[i]);
		if(min > arr[i])
		{
			min = arr[i];
		}
	}
	CU_ASSERT_PTR_NOT_NULL_FATAL(cbh->cbh_objects);
	CU_ASSERT_EQUAL(*((int*)&cbh->cbh_objects[0]), min);
	
	free(arr);
	cbh_destroy(cbh);
}


/**
  * int[], int -> void
  * EFFECTS: Given an array of length N fills it with Random numbers from 1 to n
  * MODIFIES: arr
  */
static void pickNRandomNumber(int* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = i;
	}
	srand(time(NULL));
	int r = 0;

	for (int i = 0; i < n; i++)
	{
		r = rand() % n;
		int swap = arr[r];

		arr[r] = arr[i];
		arr[i] = swap;
	}

}

static int pickRandomNumber(int lower, int upper)
{
	srand(time(NULL));
	float random = rand();
	random = random / RAND_MAX;
	random = (lower - upper) * random;
	return lower + random;
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