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
  
#ifndef _CRANBHEAP_H_
#define _CRANBHEAP_H_

#include <stdbool.h>
#include <stdio.h>

/**
  * struct for the cranbheap data structutre 
  * This will be used to store the heap metadata
  * and pointers to the actual heap array
  */ 
typedef struct cranbheap
{
	size_t cbh_size; /*the size of the actual array*/
	unsigned int cbh_length; /*the number of elements stored in the array*/
	void** cbh_objects; /*the array of object pointers*/
	int (* cbh_comparator)(void*, void*); /*used to order the objects*/
} cranbheap_t;
  

/**
  * int (*)(void*, void*) -> struct cranbheap*
  * EFFECTS: creates a new cranbheap structure 
  * REQUIRES: the comparator to have the following return values
  * - negative if the first argument comes before the second argument. 
  * - positive if the second argument comes before the first argument.
  * - zero if the order does not matter. i.e both arguments are equal
  * RETURNS: pointer to the created binary heap
  * PARAMETERS: 
  * - int (* comparator)(void*, void*): pointer to the comparator function
  */ 
struct cranbheap* cbh_create(int (* comparator)(void*, void*));


/**
  * cranbheap_t*, void* -> void
  * EFFECTS: inserts a new element obj in the given cranbheap
  * REQUIRES: the obj to be as the same type of objs in the heap
  * MODIFIES: cranbheap_t
  * PARAMETERS: 
  * - struct cranbheap* cbh: pointer to the cranbheap
  * - void* obj: pointer to the element to be inserted in the heap
  */
void cbh_insert(struct cranbheap* cbh, void* obj);


/**
  * cranbheap_t, void* -> void
  * EFFECTS: deletes the given object from the tree if it exits
  * MODIFIES: cranbheap_t cbh
  * RETURNS: the deleted object pointer
  * PARAMETERS:
  * - struct cranbheap* cbh: pointer to the cranbheap
  * - void* obj: pointer to the element to be deleted from the heap
  */
void* cbh_delete(struct cranbheap* cbh, void* obj);


/**
  * struct cranbheap* -> void*
  * EFFECTS: removes the head of the heap
  * MODIFIES: cranbheap* cbh
  * RETURNS: the old head of the heap, NULL if the heap is empty
  * PARAMETERS: 
  * - struct cranbheap* cbh: pointer to the cranbheap
  */
void* cbh_extractmw(struct cranbheap* cbh);

/**
  * struct cranbheap* -> void*
  * EFFECTS: gets the head of the heap without removing it
  * MODIFIES: nothing
  * RETURNS: the head of the heap, NULL if the heap is empty
  * PARAMETERS:
  * - struct cranbheap* cbh: pointer to the cranbheap
  */
void* cbh_peek(struct cranbheap* cbh);

/**
  * struct cranbheap* -> void
  * EFFECTS: removes all the pointers from the heap
  * MODIFIES: cranbheap_t* cbh
  * PARAMETERS:
  * - struct cranbheap* cbh: pointer to the cranbheap
  */
void cbh_clear(struct cranbheap* cbh);

/**
  * struct cranbheap* -> void
  * EFFECTS: checks if the heap contains obj
  * REQUIRES: obj to be the same type as the objects stored in the heap
  * RETURNS: true if the object was found, false otherwise
  * PARAMETERS:
  * - struct cranbheap* cbh: pointer to the heap
  * - void* obj: the object to be searched for in the heap
  */
bool cbh_contains(struct cranbheap* cbh, void* obj);

/**
  * struct cranbheap* -> void
  * EFFECTS: free all the memory associated with the heap
  * MODIFIES: cranbheap* cbh
  * PARAMETERS:
  * - struct cranbheap* cbh: pointer to the heap
  */
void cbh_destroy(struct cranbheap* cbh);


#endif /*_CRANBHEAP_H_*/
