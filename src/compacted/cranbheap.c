/** MIT License
  *
  * Copyright (c) 2019 Abdullah Emad
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all
  * copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  */

  
#include <stdio.h>
#include <stdlib.h>
#include <cranbheap.h>
  
/**
  * The compacted version of the heap
  * This file (along with headers) can
  * be compiled and used directly
  */


/**************
 * Prototypes *
 **************/
static void cbh_insert_helper(cranbheap_t* cbh, void* obj);
static int parent(int i);
static int left(int i);
static void swap(void** x, void** y);
static void* cbh_extractmw_helper(struct cranbheap* cbh);
static void heapify(struct cranbheap* cbh, int i);
static void* cbh_delete_helper(struct cranbheap* cbh, void* obj);
static int cbh_find(struct cranbheap* cbh, void* obj);

/******************************
 *                            *
 *        Interface           *
 *                            *
 ******************************/


struct cranbheap* cbh_create(int (* comparator)(void*, void*))
{
	if(comparator == NULL)
	{
		return NULL;
	}

	struct cranbheap* cbh = malloc(sizeof(struct cranbheap));
	if(cbh == NULL)
	{
		return NULL;
	}
	cbh->cbh_length = 0;
	cbh->cbh_size = 1;
	cbh->cbh_comparator = comparator;
	cbh->cbh_objects = malloc(sizeof(void*));
	if(cbh->cbh_objects == NULL)
	{
		cbh_destroy(cbh);
		cbh = NULL;
	}
	return cbh;
}

void cbh_insert(struct cranbheap* cbh, void* obj)
{
	cbh_insert_helper(cbh, obj);
}


void* cbh_delete(struct cranbheap* cbh, void* obj)
{
	return cbh_delete_helper(cbh, obj);
}


void cbh_clear(struct cranbheap* cbh)
{
	free(cbh->cbh_objects);
	cbh->cbh_objects = malloc(sizeof(void*));
	cbh->cbh_length = 0;
	cbh->cbh_size = 1;
}

void* cbh_extractmw(struct cranbheap* cbh)
{
	return cbh_extractmw_helper(cbh);
}

void* cbh_peek(struct cranbheap* cbh)
{
	return cbh->cbh_objects[0];
}

void cbh_destroy(struct cranbheap* cbh)
{
	if(cbh == NULL)
	{
		return;
	}
	if(cbh->cbh_objects != NULL)
	{
		free(cbh->cbh_objects);
		cbh->cbh_objects = NULL;
	}
	cbh->cbh_comparator = NULL;
	cbh->cbh_length = 0;
	cbh->cbh_size = 0;
	free(cbh);
}

bool cbh_contains(struct cranbheap* cbh, void* obj)
{
	int i = cbh_find(cbh, obj);
	return i != -1;
}

/****************************************
 *                                      *
 *               Helpers                *
 *                                      *
 ****************************************/
static int parent(int i)
{
	return (i - 1) / 2;
}

static int left(int i)
{
	return ((2 * i) + 1);
}

static int right(int i)
{
	return ((2 * i) + 2);
}

static void swap(void** x, void** y)
{
	void* tmp = *x;
	*x = *y;
	*y = tmp;
}

static void cbh_insert_helper(cranbheap_t* cbh, void* obj)
{
	if(cbh->cbh_length == cbh->cbh_size)
	{
		int n = cbh->cbh_size * 2;
		void** tmp = cbh->cbh_objects;
		cbh->cbh_objects = malloc(sizeof(void*) * n);
		/*failed*/
		if(cbh->cbh_objects == NULL)
		{
			cbh->cbh_objects = tmp;
			return;
		}
		for(int i = 0; i < cbh->cbh_length; i++)
		{
			cbh->cbh_objects[i] = tmp[i];
		}
		cbh->cbh_size = n;
		free(tmp);
	}
	
	int i = cbh->cbh_length++;
	cbh->cbh_objects[i] = obj;
	
	while(i != 0 && cbh->cbh_comparator(cbh->cbh_objects[parent(i)], obj) >= 0)
	{
		swap(&(cbh->cbh_objects[parent(i)]), &(cbh->cbh_objects[i]));
		i = parent(i);
	}
}


static void* cbh_extractmw_helper(struct cranbheap* cbh)
{
	if(cbh->cbh_length == 0)
	{
		return NULL;
	}

	void* ret = cbh->cbh_objects[0];

	cbh->cbh_objects[0] = cbh->cbh_objects[--cbh->cbh_length];
	if(cbh->cbh_length > 1)
	{
		heapify(cbh, 0);
		float loadFactor = (float)cbh->cbh_length / (float)cbh->cbh_size;
		if(loadFactor <= 0.25)
		{
			void** tmp = cbh->cbh_objects;
			cbh->cbh_objects = malloc(sizeof(void*) * (cbh->cbh_size / 2));
			if(cbh->cbh_objects == NULL)
			{
				cbh->cbh_objects = tmp;
			}
			else
			{
				cbh->cbh_size = cbh->cbh_size / 2;
				for(int i = 0; i < cbh->cbh_length; i++)
				{
					cbh->cbh_objects[i] = tmp[i];
				}
				free(tmp);
			}
		}
	}
	

	return ret;
}

static void heapify(struct cranbheap* cbh, int i)
{
	int leftN = left(i);
	int rightN = right(i);
	int min = i;
		
	if(leftN < cbh->cbh_length && cbh->cbh_comparator(cbh->cbh_objects[leftN], cbh->cbh_objects[min]) < 0)
	{
		min = leftN;
	}
	if(rightN < cbh->cbh_length && cbh->cbh_comparator(cbh->cbh_objects[rightN], cbh->cbh_objects[min]) < 0)
	{
		min = rightN;
	}
	
	if(min != i)
	{
		swap(&cbh->cbh_objects[i], &cbh->cbh_objects[min]);
		heapify(cbh, min);
	}
}


static void* cbh_delete_helper(struct cranbheap* cbh, void* obj)
{
	int i = cbh_find(cbh, obj);
	if(i == -1)
	{
		return NULL;
	}
	while (i != 0) 
	{
		swap(&cbh->cbh_objects[i], &cbh->cbh_objects[parent(i)]);
		i = parent(i);
	}

	return cbh_extractmw(cbh);	
}


static int cbh_find(struct cranbheap* cbh, void* obj)
{
	for(int i = 0; i < cbh->cbh_length; i++)
	{
		if(cbh->cbh_objects[i] == obj || cbh->cbh_comparator(cbh->cbh_objects[i], obj) == 0)
		{
			return i;
		}
	}
	return -1;
}