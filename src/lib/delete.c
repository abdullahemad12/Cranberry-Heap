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
#include <cranbheap.h>
#include "lib.h"

/**
  * EFFECTS: Removes the given object from the heap if it exists
  * MODIFIES: struct cranbheap* cbh
  * RETURNS: the removed object, or NULL if it does not exist
  * PARAMETERS:
  * - struct cranbheap* cbh: pointer to the heap structure
  * - void* obj: the object to be removed from the heap
  */
void* cbh_delete_helper(struct cranbheap* cbh, void* obj)
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

/**
  * EFFECTS: finds the index of the given object in the heap
  * RETURNS: the index of the of the object if found, -1 otherwise
  * PARAMETERS:
  * - struct cranbheap* cbh: pointer to the heap structure
  * - void* obj: the object to be searched for
  */
int cbh_find(struct cranbheap* cbh, void* obj)
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