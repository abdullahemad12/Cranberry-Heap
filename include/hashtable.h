#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <linkedlist.h>


/**
  * Struct for the hashtable
  */
typedef struct hashtable 
{
	int ht_size; /*number of buckets*/
	int ht_length; /*number of objects*/
	struct linked_list* ht_buckets[];
}hashtable_t;


/**
  * int -> struct hashtable*
  * EFFECTS: creates an emtpy hashtable
  * RETURNS: a pointer to the created hashtable, NULL on failure
  */
struct hashtable* create_hashtable(void);



/**
  * struct hashtable* -> void
  * EFFECTS: Deletes all the memory associated with the hashtable 
  * MODIFIES: hashtable ht
  * Note: does not free objects located in the hashtable's buckets
  */

void hashtable_destroy(struct hashtable* ht);


/**
  * struct hashtable*, void* , const char* -> void
  * EFFECTS: inserts a given object with a given key into the hashtable
  * MODIFIES: hashtable_t* ht
  * PARAMETERS: 
  * struct hashtable* ht: the hashtable at whicht the object is going to be inserted
  * void* object: the object that is going to be inserted
  * const char* key: the key that is going to be hashed
  */

void hashtable_insert(struct hashtable* ht, void* object, void* key);


/**
  * struct hashtable*, void* , const char* -> void
  * EFFECTS: removes a given object with a given key into the hashtable
  * MODIFIES: hashtable_t*  
  * RETURNS: the object that was freed
  * PARAMETERS: 
  * struct hashtable* ht: the hashtable at whicht the object is going to be inserted
  * void* object: the object that is going to be removed
  * const char* key: the key that is going to be hashed
  */
void* hashtable_remove(struct hashtable* ht, void* object, const char* key);

bool void* 

#endif /*_HASHTABLE_H*/