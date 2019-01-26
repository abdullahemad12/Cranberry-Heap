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
#include <stdlib.h>
#include "lib.h"


/**
  * struct cranbheap* -> void*
  * EFFECTS: extract the head of the heap
  * MODIFIES: struct cranbheap*
  * RETURNS: the head of the heap, or NULL if the heap is empty
  * PARAMETERS:
  * - struct cranbheap* cbh: pointer to the heap struct
  */

void* cbh_extractmw_helper(struct cranbheap* cbh)
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

/**
  * struct cranbheap*, int -> void
  * EFFECTS: preserves the properties of the heap by swapping
  *          the parents and children as neccessary
  * MODIFIES: struct cranbheap* cbh
  * REQUIRES: i < cbh->cbh_length
  * PARAMETERS: 
  * - struct cranbheap* cbh: pointer to the heap struct
  * - int i: the parent element to be swapped
  */
void heapify(struct cranbheap* cbh, int i)
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