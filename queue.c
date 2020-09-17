#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/* function declaration */
void q_bubble_sort(queue_t *q);
list_ele_t *q_merge_sort(list_ele_t *);
list_ele_t *q_merge(list_ele_t *, list_ele_t *);

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
    if (q == NULL) {
        return;
    }

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
    } else {
        return false;
    }
    q->head = elem->next;
    q->size -= 1;
    /* set tail to NULL if all element removed */
    if (q->size == 0) {
        q->tail = NULL;
    }

    /* free element */
    free(elem->value);
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
    if (q == NULL) {
        return;
    }
    if (q->size <= 1) {
        return;
    }
    q->tail = q->head;
    // more than 1 elem
    list_ele_t *elem = q->head;
    list_ele_t *e_next = elem->next;
    // elem is last one now
    elem->next = NULL;
    while (e_next != NULL) {
        list_ele_t *tmp = e_next->next;
        e_next->next = elem;
        elem = e_next;
        e_next = tmp;
    }
    q->head = elem;
    return;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (q == NULL || q->size <= 1) {
        return;
    }
    // q_bubble_sort(q);
    list_ele_t *new_head = q_merge_sort(q->head);
    q->head = new_head;
}

/*
void q_bubble_sort(queue_t *q)
{
    list_ele_t *head = q->head;
    list_ele_t *ptr;
    list_ele_t *prev_ptr;
    list_ele_t *tail = NULL;
    list_ele_t *new_tail = NULL;

    while (head->next != tail) {
        ptr = head;
        prev_ptr = head;
        while (ptr != NULL && ptr->next != tail) {
            char *v1 = ptr->value;
            char *v2 = ptr->next->value;
            if (strcmp(v1, v2) <= 0) {
                // order is correct, move on
                prev_ptr = ptr;
                ptr = ptr->next;
            } else {
                list_ele_t *tmp = ptr->next;
                // updte prev elem -> next
                if (ptr == prev_ptr) {
                    // head
                    head = tmp;
                } else {
                    prev_ptr->next = tmp;
                }
                // swap
                ptr->next = tmp->next;
                tmp->next = ptr;
                prev_ptr = tmp;
            }
        }
        if (new_tail == NULL) {
            new_tail = ptr;
        }
        tail = ptr;
    }
    q->head = head;
    q->tail = new_tail;
}
*/

list_ele_t *q_merge_sort(list_ele_t *lt)
{
    // check size
    if (lt == NULL || lt->next == NULL) {
        return lt;
    }

    list_ele_t *fast = lt->next;
    list_ele_t *slow = lt;

    // split
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    fast = slow->next;
    slow->next = NULL;

    // sort each part
    list_ele_t *fast_sorted = q_merge_sort(fast);
    list_ele_t *slow_sorted = q_merge_sort(lt);
    return q_merge(fast_sorted, slow_sorted);
}

list_ele_t *q_merge(list_ele_t *lt1, list_ele_t *lt2)
{
    if (lt1 == NULL) {
        return lt2;
    }
    if (lt2 == NULL) {
        return lt1;
    }

    // process head
    list_ele_t *new_head;
    if (strcmp(lt1->value, lt2->value) <= 0) {
        new_head = lt1;
        lt1 = lt1->next;
    } else {
        new_head = lt2;
        lt2 = lt2->next;
    }

    list_ele_t *ptr = new_head;
    while (lt1 != NULL && lt2 != NULL) {
        if (strcmp(lt1->value, lt2->value) <= 0) {
            ptr->next = lt1;
            lt1 = lt1->next;
        } else {
            ptr->next = lt2;
            lt2 = lt2->next;
        }
        ptr = ptr->next;
    }
    // process rest
    if (lt1 != NULL) {
        ptr->next = lt1;
    }
    if (lt2 != NULL) {
        ptr->next = lt2;
    }
    return new_head;
}
