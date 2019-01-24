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
5. Peak: returns the min/max element without removing it. Performance: O(1)
6. clear: removes all the elements from the heap


# Interface

<table width="100%">
	<tr>
		<th>Return</th>
		<th>Function and Description</th>
	</tr>
	<tr>
		<td>struct cranbheap*</td>
		<td>
			<b><a href="#create">cbh_create(int (* comparator)(void*))</a></b><br>
			Creates a new cranberry heap structure
		</td>
	</tr>
	<tr>
		<td>void</td>
		<td>
			<b><a href="#create">cbh_insert(struct cranbheap* cbh, void* obj)</a></b><br>
			Inserts a new element in the heap
		</td>
	</tr>
	<tr>
		<td>void*</td>
		<td>
			<b><a href="#create">cbh_delete((struct cranbheap* cbh, void* obj)</a></b><br>
			deletes an element from the heap
		</td>
	</tr>
	<tr>
		<td>void*</td>
		<td>
			<b><a href="#create">cbh_extractmw(struct cranbheap* cbh)</a></b><br>
			removes the root element from the heap (i.e maximum/minimum element)
		</td>
	</tr>
	<tr>
		<td>void*</td>
		<td>
			<b><a href="#create">cbh_peak(struct cranbheap* cbh)</a></b><br>
			removes the root element from the heap (i.e maximum/minimum element)
		</td>
	</tr>
	<tr>
		<td>void</td>
		<td>
			<b><a href="#create">cbh_clear(struct cranbheap* cbh)</a></b><br>
			removes all the elements from the heap
		</td>
	</tr>
</table>

