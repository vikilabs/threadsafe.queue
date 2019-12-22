/* This piece of code is free ( free means free. Do whatever useful )
 *
 *                      Author: Viki (a) Vignesh Natarajan
 *                      Lab   : vikilabs.org
 */

#ifndef _QUEUE_H
#define _QUEUE_H
#include <stdint.h>
#include <pthread.h>

struct qnode{
    void *data;
    struct qnode *next, *prev;
};

struct queue{
    uint8_t active;
    int node_count;
    pthread_mutex_t *lock;
    struct qnode *head, *tail;
};

extern struct   queue    *queue_init();
extern int8_t           queue_terminate(struct queue *q);
extern struct   qnode    *queue_create_node(void *data, size_t data_size);
extern int8_t           enqueue(struct queue *q, struct qnode *n);
extern struct   qnode    *dequeue(struct queue *q);
extern void             traverse_queue(struct queue *q);
extern int              get_nodes_count(struct queue *q);

#endif
