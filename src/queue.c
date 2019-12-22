/* This piece of code is free ( free means free. Do whatever useful ;-) )
 *
 *                      Author: Viki (a) Vignesh Natarajan
 *                      Lab   : vikilabs.org
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include "queue.h"
#include "lalloc.h"

static void q_lock(struct queue *q)
{
    pthread_mutex_lock(q->lock);
}

static void q_unlock(struct queue *q)
{
    pthread_mutex_unlock(q->lock);
}


struct queue *queue_init()
{
    struct queue *q = NULL;
    q = (struct queue *) lalloc(sizeof(struct queue));
    
    if(!q){
        printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
    }else{
        q->head = NULL;
        q->tail = NULL;
        q->lock = (pthread_mutex_t *) lalloc(sizeof(pthread_mutex_t));
        q->node_count = 0;
        
        if(!q->lock){
            printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
            LFREE(q);
            return NULL;
        }
        
        pthread_mutex_init(q->lock, NULL);
        q->active = 1;
    }

    return q;
}

int8_t queue_terminate(struct queue *q)
{
    struct qnode *itr=NULL, *d=NULL;

    assert( q != NULL);
    
   
    q_lock(q);
    q->active = 0;

    itr = q->head;
    q->head = NULL;
    q->tail = NULL;

    while(itr){
        d = itr;
        itr = itr->next;
        q->node_count -= 1;
        LFREE(d);
    }
    
    q_unlock(q);
    
    pthread_mutex_destroy(q->lock);
    LFREE(q->lock);
    return 0;
}

struct qnode *queue_create_node(void *data, size_t data_size)
{
    struct qnode *n = NULL;
    void *d = NULL;
    int8_t ret = 0;

    /* It is possible to alloc a node with NULL data */
    if( (data) && ( data_size > 0 )){
        d = (void *) lalloc(data_size);
        
        if(!d){
            printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
            ret = -1; goto safe_return;
        }
    
    }

    n = (void *) lalloc(sizeof(struct qnode));

    if(!n){
        printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
        LFREE(d);
        ret = -1; goto safe_return;
    }
    
    if(d){
        memcpy(d, data, data_size);
    }
    
    n->next = NULL;
    n->prev = NULL;
    n->data = d;

safe_return:
    
    if(ret == -1){
        return NULL;
    }

    return n;
}


int8_t enqueue(struct queue *q, struct qnode *n)
{
    assert( q != NULL);
    assert( n != NULL);

    q_lock(q);
 
    if(!q->active){
        q_unlock(q);
        return -1;
    }
   
    if(!q->tail){

        /*
            .........         .........     
            .       .         .       .
            .  HEAD .         . TAIL  . 
            .       .         .       .
            .........         .........

                    |           |
                    V           V
                  ...................
                  .                 .  --> NULL
         NULL <---.   NODE (FIRST)  .
                  ...................

        */      

        q->tail = n;
        q->head = n;
    }else{

        /*

            .........                 .........     
            .       .                 .       .
            .  HEAD .                 . TAIL  . 
            .       .                 .       .
            .........                 .........

                |                       |
                V                       V
            ...........               ........      ............
            .         . --  ----  --> .      . ---> .          .---> NULL
            .  NODE   . <-- ----  --- . NODE . <--- . NEW NODE .  
            ...........               ........      ............

        */

        n->next = NULL;
        n->prev = q->tail;
        q->tail->next = n;

        /*

            .........                               .........     
            .       .                               .       .
            .  HEAD .                               . TAIL  . 
            .       .                               .       .
            .........                               .........

                |                                       |
                V                                       V
            ...........               ........      ............
            .         . --  ----  --> .      . ---> .          .---> NULL
            .  NODE   . <-- ----  --- . NODE . <--- . NEW NODE .  
            ...........               ........      ............

        */

        q->tail = n;
    }
    
    q->node_count += 1;
    
    q_unlock(q);

    return 0;
}


/* adding like a queue fashion. Adding new node to the tail of the queue
 */
struct qnode *dequeue(struct queue *q)
{
    struct qnode *d=NULL;

    assert( q != NULL);

    q_lock(q);

    if(!q->active){
        q_unlock(q);
        return NULL;
    }

    d = q->head;

    if(d){

        /*

           .........                            .........     
           .       .                            .       .
           .  HEAD .                            . TAIL  . 
           .       .                            .       .
           .........                            .........

                |                                  |
                V                                  V
           ............       ............       ........
           .          .  ---> .          . ----> .      .
   NULL<---.   NODE   .  <--- .  NODE (D). <---- . NODE .---> NULL     
           ............       ............       ........

         */

        q->node_count -= 1;

        if(q->head == q->tail){ // only one element in queue
            q->tail   = NULL;
            q->head   = NULL;
        }else{                  // more than one element in queue
            q->head = q->head->next;
            q->head->prev = NULL;
        }

    }else{
        q->head = NULL;
        q->tail = NULL;
    }

    q_unlock(q);

    return d;
}

int get_nodes_count(struct queue *q)
{
    int c = 0;

    q_lock(q);
    c = q->node_count; 
    q_unlock(q);
    
    return c;
}

void traverse_queue(struct queue *q)
{
    struct qnode *itr;
    assert(q);
    
    q_lock(q);
 
    if(!q->active){
        q_unlock(q);
        return;
    }
    
    itr = q->head;
    printf("[ queue ]");
    while(itr){
        printf("[ %d ]->", *((int*)itr->data));
        itr = itr->next;
    }
    printf("\n");
    q_unlock(q);
}

