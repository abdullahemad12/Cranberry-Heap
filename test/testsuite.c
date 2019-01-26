#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <time.h>
#include <stdlib.h>
#include <cranbheap.h>


static void pickNRandomNumber(int arr[], int n);
static int pickRandomNumber(int lower, int upper);
static void sort(int* arr, int n);

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
	int n = 1200000;
	int* arr = malloc(sizeof(int) * n);
	CU_ASSERT_PTR_NOT_NULL_FATAL(arr);
	pickNRandomNumber(arr,  n);
	for(int i = 0; i < n; i++)
	{
		cbh_insert(cbh, &(arr[i]));
	}
	CU_ASSERT_PTR_NOT_NULL_FATAL(cbh->cbh_objects);
	CU_ASSERT_EQUAL(*((int*)cbh->cbh_objects[0]), 0);
	free(arr);
	cbh_destroy(cbh);
}

void cbh_insert_test2(void)
{
	struct cranbheap* cbh = cbh_create(comparator);
	int n = 10;
	int* arr = malloc(sizeof(int) * n);
	int min = 2000012;
	for(int i = 0; i < n; i++)
	{	
		arr[i] = pickRandomNumber(-200000, 200000);
		cbh_insert(cbh, &(arr[i]));
		if(min > arr[i])
		{
			min = arr[i];
		}
	}
	CU_ASSERT_PTR_NOT_NULL_FATAL(cbh->cbh_objects);
	CU_ASSERT_EQUAL(*((int*)cbh->cbh_objects[0]), min);
	free(arr);
	cbh_destroy(cbh);
}

void cbh_extractmw_test1(void)
{
	struct cranbheap* cbh = cbh_create(comparator);
	int n = 12000;
	int* arr = malloc(sizeof(int) * n);
	CU_ASSERT_PTR_NOT_NULL_FATAL(arr);
	pickNRandomNumber(arr,  n);
	for(int i = 0; i < n; i++)
	{
		cbh_insert(cbh, &(arr[i]));
	}
	CU_ASSERT_EQUAL(cbh->cbh_length, n);
	for(int i = 0; i < n; i++)
	{
		int* x = (int*) cbh_extractmw(cbh);
		CU_ASSERT_PTR_NOT_NULL_FATAL(x);
		CU_ASSERT_EQUAL(*x, i);
		CU_ASSERT_EQUAL(cbh->cbh_length, n - (i + 1));
	}
	int* x = (int*) cbh_extractmw(cbh);
	CU_ASSERT_PTR_NULL(x);
	free(arr);
	cbh_destroy(cbh);
}

void cbh_extractmw_test2(void)
{
	struct cranbheap* cbh = cbh_create(comparator);
	int n = 12000;
	int* arr = malloc(sizeof(int) * n);
	CU_ASSERT_PTR_NOT_NULL_FATAL(arr);

	for(int i = 0; i < n; i++)
	{	
		arr[i] = pickRandomNumber(-200000, 200000);
		cbh_insert(cbh, &(arr[i]));
	}
	sort(arr, n);
	CU_ASSERT_EQUAL(cbh->cbh_length, n);
	for(int i = 0; i < n; i++)
	{
		int* x = (int*) cbh_extractmw(cbh);
		CU_ASSERT_PTR_NOT_NULL_FATAL(x);
		if(*x != arr[i])
		{
			printf("x: %d, arr[i]: %d\n", *x, arr[i]);
		}
		CU_ASSERT_EQUAL(*x, arr[i]);
		CU_ASSERT_EQUAL(cbh->cbh_length, n - (i + 1));
	}

	free(arr);
	cbh_destroy(cbh);
}

void cbh_peak_test1(void)
{
	struct cranbheap* cbh = cbh_create(comparator);
	int n = 12000;
	int* arr = malloc(sizeof(int) * n);
	CU_ASSERT_PTR_NOT_NULL_FATAL(arr);

	for(int i = 0; i < n; i++)
	{	
		arr[i] = pickRandomNumber(-200000, 200000);
		cbh_insert(cbh, &(arr[i]));
	}
	sort(arr, n);

	for(int i = 0; i < n; i++)
	{
		int* y = (int*) cbh_peek(cbh);
		int* x = (int*) cbh_extractmw(cbh);
		CU_ASSERT_PTR_NOT_NULL_FATAL(x);
		CU_ASSERT_EQUAL(*x, arr[i]);
		CU_ASSERT_PTR_EQUAL(x, y);
	}


	free(arr);
	cbh_destroy(cbh);
}

void cbh_delete_test1(void)
{
	struct cranbheap* cbh = cbh_create(comparator);
	int n = 12000;
	int* arr = malloc(sizeof(int) * n);
	CU_ASSERT_PTR_NOT_NULL_FATAL(arr);

	for(int i = 0; i < n; i++)
	{	
		arr[i] = pickRandomNumber(-200000, 200000);
		cbh_insert(cbh, &(arr[i]));
	}
	CU_ASSERT_EQUAL(cbh->cbh_length, n);
	/*delete nonexisting objects*/	
	for(int i = 0; i < 100; i++)
	{
		int x = pickRandomNumber(200001, 300000);
		void* res = cbh_delete(cbh, &x);
		CU_ASSERT_PTR_NULL(res);
		CU_ASSERT_EQUAL(cbh->cbh_length, n);
	}
	
	free(arr);
	cbh_destroy(cbh);
}

void cbh_delete_test2(void)
{
	struct cranbheap* cbh = cbh_create(comparator);

	/*delete from empty heap*/
	CU_ASSERT_EQUAL(cbh->cbh_length, 0);	
	for(int i = 0; i < 100; i++)
	{
		int x = pickRandomNumber(200001, 300000);
		void* res = cbh_delete(cbh, &x);
		CU_ASSERT_PTR_NULL(res);
		CU_ASSERT_EQUAL(cbh->cbh_length, 0);
	}

	cbh_destroy(cbh);
}


void cbh_delete_test3(void)
{
	struct cranbheap* cbh = cbh_create(comparator);
	int n = 12000;
	int* arr = malloc(sizeof(int) * n);
	CU_ASSERT_PTR_NOT_NULL_FATAL(arr);

	for(int i = 0; i < n; i++)
	{	
		arr[i] = pickRandomNumber(-200000, 200000);
		cbh_insert(cbh, &(arr[i]));
	}

	CU_ASSERT_EQUAL(cbh->cbh_length, n);
	int deleted = 0;
	/*delete random objects objects*/	
	for(int i = 0; i < 100; i++)
	{
		int x = pickRandomNumber(-200000, 200000);
		int* res = (int*)cbh_delete(cbh, &x);
		if(res != NULL)
		{
			++deleted;
			*res = 300000;
			for(int i = 0; i < cbh->cbh_length; i++)
			{
				CU_ASSERT_PTR_NOT_EQUAL(cbh->cbh_objects[i], res);
			}
		}
		CU_ASSERT_EQUAL(cbh->cbh_length, n - deleted);
	}

	sort(arr, n);

	for(int i = 0; i < cbh->cbh_length; i++)
	{
		int* res = (int*) cbh_extractmw(cbh);
		CU_ASSERT_EQUAL(arr[i], *res);
	}
	
	free(arr);
	cbh_destroy(cbh);
} 


static void sort(int* arr, int n)
{
	if(n <= 1)
	{
		return;
	}
	int ln = n / 2;
	int rn = n - ln;
	int* l = malloc(sizeof(int) * ln);
	int* r = malloc(sizeof(int) * rn);
	for(int i = 0; i < ln; i++)
	{
		l[i] = arr[i];
	}
	for(int i = 0; i < rn; i++)
	{
		r[i] = arr[ln + i];
	}

	sort(l, ln);
	sort(r, rn);

	int lptr = 0;
	int rptr = 0;
	for(int i = 0; i < n; i++)
	{
		if(lptr >= ln)
		{
			arr[i] = r[rptr++];
		}
		else if(rptr  >= rn)
		{
			arr[i] = l[lptr++];
		}
		else
		{
			if(l[lptr] < r[rptr])
			{
				arr[i] = l[lptr++];
			}
			else
			{
				arr[i] = r[rptr++];
			}
		}
	}
	free(l);
	free(r);
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