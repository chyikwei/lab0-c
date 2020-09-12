#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Free queue structure */
    list_ele_t *elem = q->head;
    while (elem != NULL) {
        /* free string */
        if (elem->value != NULL) {
            free(elem->value);
        }
        list_ele_t *tmp = elem;
        /* get next elem */
        elem = elem->next;
        /* free current elem */
        free(tmp);
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    if (q == NULL) {
        return false;
    }
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }
    int s_size = strlen(s) + 1;
    char *ss = malloc(s_size);
    if (ss == NULL) {
        free(newh);
        return false;
    } else {
        strncpy(ss, s, s_size);
    }
    newh->value = ss;
    newh->next = q->head;
    /* assign tail if this is the first element */
    if (q->size == 0) {
        q->tail = newh;
    }
    q->head = newh;
    q->size += 1;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newt;
    if (q == NULL) {
        return false;
    }
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
        return false;
    }
    /* allocate string */
    int s_size = strlen(s) + 1;
    char *ss = malloc(s_size);
    if (ss == NULL) {
        free(newt);
        return false;
    } else {
        strncpy(ss, s, s_size);
    }
    newt->value = ss;
    newt->next = NULL;
    /* assign tail if this is the first element */
    if (q->size == 0) {
        q->head = newt;
        q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }
    q->size += 1;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL) {
        return false;
    }

    list_ele_t *elem = q->head;
    if (elem == NULL) {
        return false;
    }
    /* TODO: return false if sp is NULL? */
    if (sp != NULL && elem->value != NULL) {
        int s_size = MIN(strlen(elem->value), bufsize - 1);
        strncpy(sp, elem->value, s_size);
        sp[s_size] = '\0';
    }
    q->head = elem->next;
    q->size -= 1;
    /* set tail to NULL if all element removed */
    if (q->size == 0) {
        q->tail = NULL;
    }
    /* free element */
    if (elem->value != NULL) {
        free(elem->value);
    }
    free(elem);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL) {
        return 0;
    }
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
