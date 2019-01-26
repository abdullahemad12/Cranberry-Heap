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
#include "lib/lib.h"

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
	for(int i = 0; i < cbh->cbh_length; i++)
	{
		if(cbh->cbh_objects[i] ==  obj)
		{
			return true;
		}
	}
	return false;
}