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
#include <cranbheap.h>
#include "lib.h"
#include <stdlib.h>
/*
 * Helper function for the insert operation
 */

void cbh_insert_helper(cranbheap_t* cbh, void* obj)
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
			cbh->cbh_objects = tmp[i];
		}
		cbh->cbh_size = n;
	}
	
	int i = cbh->cbh_length++;
	cbh->cbh_objects[i] = obj;
	
	while(i != 0 && cbh->cbh_comparator(obj, cbh->cbh_objects[parent(i)]))
	{
		swap(&(cbh->cbh_objects[parent(i)]), &(cbh->cbh_objects[i]));
		i = parent(i);
	}
}
