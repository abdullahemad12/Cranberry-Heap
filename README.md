<h1><img src ="docs/Art/cranberries_white_small.png" alt = "cranberries" width="12%">Cranberry Heap</h1>

[![first-timers-only](https://img.shields.io/badge/first--timers--only-friendly-blue.svg?style=flat-square)](https://www.firsttimersonly.com/)
[![Join the chat at https://gitter.im/Cranberry-heap](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/Cranberry-heap)

A binary heap implementation written in C with simple interface. Cranberry Heap can be used as a min or max heap. A binary heap is a binary tree like data structure that stores elements in specific order and useful for quickly answering queries about the maximum or the minimum elements. Visit [Wikipedia](https://en.wikipedia.org/wiki/Binary_heap) to know more. 


# Notation
- n: the number of elements in the heap


# Supported Heap operation

1. Creation: creates a new heap data structure, Min or Max as specified by the user. Performance: O(1)
2. Insertion: inserts a new element in the heap. Performance: O(log(n))
3. Deletion: deletes an existing element in the heap. Performance: O(n)
4. Extraction: removes the min/max element in the heap. Performance: O(log(n))
5. peek: returns the min/max element without removing it. Performance: O(1)
6. clear: removes all the elements from the heap. Performance: O(n)
7. contains: checks if an element is present in the heap. Performance: O(n)

# Interface

<table width="100%">
	<tr>
		<th>Return</th>
		<th>Function and Description</th>
	</tr>
	<tr>
		<td>struct cranbheap*</td>
		<td>
			<b><a href="#create">cbh_create(int (* comparator)(void*, void*))</a></b><br>
			Creates a new cranberry heap structure
		</td>
	</tr>
	<tr>
		<td>void</td>
		<td>
			<b><a href="#insert">cbh_insert(struct cranbheap* cbh, void* obj)</a></b><br>
			Inserts a new element in the heap
		</td>
	</tr>
	<tr>
		<td>void*</td>
		<td>
			<b><a href="#delete">cbh_delete((struct cranbheap* cbh, void* obj)</a></b><br>
			deletes an element from the heap
		</td>
	</tr>
	<tr>
		<td>void*</td>
		<td>
			<b><a href="#extract">cbh_extractmw(struct cranbheap* cbh)</a></b><br>
			removes the root element from the heap (i.e maximum/minimum element)
		</td>
	</tr>
	<tr>
		<td>void*</td>
		<td>
			<b><a href="#peek">cbh_peek(struct cranbheap* cbh)</a></b><br>
			removes the root element from the heap (i.e maximum/minimum element)
		</td>
	</tr>
	<tr>
		<td>void</td>
		<td>
			<b><a href="#clear">cbh_clear(struct cranbheap* cbh)</a></b><br>
			removes all the elements from the heap
		</td>
	</tr>
	<tr>
		<td>bool</td>
		<td>
			<b><a href="#contains">cbh_contains(struct cranbheap* cbh, void* obj)</a></b><br>
			returns true if obj is store in the heap
		</td>
	</tr>
	<tr>
		<td>unsigned int</td>
		<td>
			<b><a href="#length">cbh_length(struct cranbheap* cbh)</a></b><br>
			returns the number of elements store in the heap
		</td>
	</tr>
</table>

## create

**cranbheap* cbh_create(int (* comparator)(void*, void*))**
Creates a new cranberry heap structure

#### Returns: 
Pointer to the created heap

#### Parameters:
int (* comparator)(void*, void*): a pointer to a function that takes as an argument two void* pointers (the objects stored in the tree will be passed to this function) and returns an int according to the following rules: 
1. if the first argument should come before the second argument return -1
2. if the first argument should come after the second argument return 1
3. if both have the same weight return 0

This function will be used to order the objects in the heap

## insert

**void cbh_insert(struct cranbheap* cbh, void* obj)**
Inserts a new object in the tree

#### Parameters: 

- struct cranbheap* cbh: pointer to the heap
- void* obj: object to be inserted in the heap

## delete

 **void cbh_delete((struct cranbheap* cbh, void* obj)**
 Deletes a specific object from the heap
 
#### Parameters:
- struct cranbheap* cbh: pointer to the heap
- void* obj: the object to be removed from the heap


## extract

**void* cbh_extractmw(struct cranbheap* cbh)**
Extracts the the maximum/minimum element (specified by the comparator) from the tree

#### Returns:
returns a pointer to the maximum/minimum element

#### Parameters: 

- struct cranbheap* cbh: pointer to the heap


## peek

**void* cbh_peek(struct cranbheap* cbh)** 
Retrieves but does not remove the head of the heap

#### Returns: 
returns a pointer to the head of the heap

#### Parameters:
- struct cranbheap* cbh: pointer to the heap

## clear

**void cbh_clear(struct cranbheap* cbh)**
Removes all the elements from the heap

#### Parameters:
- struct cranbheap* cbh: pointer to the heap


## contains

**bool cbh_contains(struct cranbheap* cbh, void* obj)**


checks if the given element is present in the heap

#### Returns: 
returns true if the given object is present in the heap, false otherwise

#### Parameters: 
- struct cranbheap* cbh: pointer to the heap
- void* obj: pointer to the object to be searched for


## length

**unsigned int cbh_length(struct cranbheap* cbh)**
gets the number of elements stored in the heap

#### Returns: 
the number of void* objects stored in the heap

#### Parameters:
- struct cranbheap* cbh: pointer to the heap

# Installation on Linux and Unix-like machines

1. Clone this repository or download it as zip and extract it.
2. open up the terminal and `cd` into the project's directory.
3. run: `make`
4. run: `sudo make install`

**compilation**: `clang  your_program.c -lcranbheap -o your_program`

where -lcranbheap tells the compiler where to find the code for the library

**Uninstall**
To uninstall the library run the following command in the terminal: 
`sudo make uninstall`


## Contribution
if you are planning to contribute, it is highly recommended that you read through the docs and go through the [CONTRIBUTING.md](CONTRIBUTING.md) guidlines

#### Opening an issue: 
For this project, there are three main types of issues that you can open: 

1. [Bug Report](.github/ISSUE_TEMPLATE/bug_report.md)
2. [Feature Request](.github/ISSUE_TEMPLATE/feature_request.md)
3. [New Task](.github/ISSUE_TEMPLATE/new-task.md) 

Please follow the format proposed by these templates before opening a new issue.

#### Creating a Pull request 
Please follow that pull request guidelines specified in The [pull Request template](PULL_REQUEST_TEMPLATE.md)


## Contact Me: 

For any inquiries please send me at: **abdullahem1997@hotmail.com**


