/**
 *   It implements the set module
 *
 * @file set.c
 * @author  Jorge Garcia Garrido
 * @version 0
 * @date 18-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "set.h"

/** @brief Structure for the Set type */
struct _Set {
  Id ids[MAX_SET]; /**< Array of ids stored in the set */
  int n_ids;       /**< Number of ids currently in the set */
};

/*   It creates a new empty Set, allocating memory and initializing its members */
Set* set_create() {
  Set *new_set = NULL;
  int i;
  new_set = (Set *) malloc(sizeof (Set)); /* allocates memory for the set */
  if (new_set == NULL) {
    return NULL;
  }
  /* initializes the set */
  new_set->n_ids = 0;
  for (i = 0; i < MAX_SET; i++) {
    new_set->ids[i] = NO_ID; /* fills all positions with NO_ID */
  }
  return new_set;
}

/*   It destroys a Set, freeing the allocated memory */
Status set_destroy(Set* set) {
  if (!set) {
    return ERROR;
  }
  free(set);
  set = NULL;
  return OK;
}

/*   It adds an element to the Set if it does not already exist */
Status set_add(Set* set, Id id) {
  if (!set || id == NO_ID || set->n_ids >= MAX_SET) {
    return ERROR;
  }
  /* if the element already exists, returns OK without adding it */
  if (set_find(set, id) != -1) {
    return OK;
  }
  /* adds the new id at the end */
  set->ids[set->n_ids] = id;
  set->n_ids++;
  return OK;
}

/*   It removes an element from the Set */
Status set_del(Set* set, Id id) {
  int i, index;
  if (!set || id == NO_ID) {
    return ERROR;
  }
  /* searches the position of the element */
  index = set_find(set, id);
  if (index == -1) {
    return ERROR;
  }
  /* shifts following elements to close the gap */
  for (i = index; i < set->n_ids - 1; i++) {
    set->ids[i] = set->ids[i + 1];
  }
  /* clears the last position now left free */
  set->ids[set->n_ids - 1] = NO_ID;
  set->n_ids--;
  return OK;
}

/*   It searches for an id in the Set */
int set_find(Set* set, Id id) {
  int i;
  if (!set || id == NO_ID) {
    return -1;
  }
  /* linear search through the array */
  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) {
      return i; /* returns index if found */
    }
  }
  return -1;
}

/*   It gets the number of elements in the Set */
int set_get_n_ids(Set* set) {
  if (!set) {
    return -1;
  }
  return set->n_ids;
}

/*   It gets the id stored at a given position in the Set */
Id set_get_id(Set *set, int array_position) {
  if (set == NULL || array_position < 0 || array_position >= set->n_ids) {
    return NO_ID;
    }
  return set->ids[array_position];
}

/*   It gets the array of ids stored in the Set */
Id* set_get_ids(Set *set) {
  if (set == NULL || set->n_ids == 0) {
    return NULL; 
    }
  return set->ids;
}

#ifdef DEBUG
/*   It prints the contents of a Set */
Status set_print(Set* set) {
  int i;
  if (!set) {
    return ERROR;
  }
  fprintf(stdout, "--> Set (n_ids: %d): ", set->n_ids);
  for (i = 0; i < set->n_ids; i++) {
    fprintf(stdout, "%ld ", set->ids[i]); /* prints each id in the set */
  }
  fprintf(stdout, "\n");
  return OK;
}
#endif