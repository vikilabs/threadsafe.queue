#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"
#include "test_util.h"
#include "lalloc.h"

#define HUNDRED_MS 100000

typedef void (*testcase_t) (void);

void queue_test1_create_queue()
{
    size_t start_mem = GetDynMemoryUsage();
    struct queue *q = queue_init();

    if(q==NULL){
        TEST_FAIL("queue should not be NULL");
    }else{
        TEST_PASS("queue should not be NULL");
    }

    if(q->head == NULL){
        TEST_PASS("head should be NULL");
    }else{
        TEST_FAIL("head should be NULL");
    }

    if(q->tail == NULL){
        TEST_PASS("tail should be NULL");
    }else{
        TEST_FAIL("tail should be NULL");
    }

    if( (start_mem + sizeof(struct queue) + sizeof(pthread_mutex_t)) != GetDynMemoryUsage()){
        TEST_FAIL("struct queue memory check");
    }else{
        TEST_PASS("struct queue memory check");
    }

    LFREE(q);
}


void queue_test1_create_node()
{
    int i = 0xFF;

    struct qnode *n = NULL;
    
    n = queue_create_node(&i, sizeof(int));

    if(!n){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(*((int*)n->data) == 0xFF){
        TEST_PASS("node should store the data properly");
    }else{
        TEST_FAIL("node should store the data properly");
    }

    LFREE(n);

    n = queue_create_node(NULL, sizeof(int));

    if(!n){
        TEST_FAIL("node should be created even if (data = NULL)");
    }else{
        TEST_PASS("node should be created even if (data = NULL)");
    }

    if(n->data == NULL){
        TEST_PASS("n->data should be NULL");
    }else{
        TEST_FAIL("n->data should be NULL");
    }

    LFREE(n);

    n = queue_create_node(&i, 0);

    if(!n){
        TEST_FAIL("node should be created even if (data_size = 0)");
    }else{
        TEST_PASS("node should be created even if (data_size = 0)");
    }

    if(n->data == NULL){
        TEST_PASS("n->data should be NULL");
    }else{
        TEST_FAIL("n->data should be NULL");
    }
    
    LFREE(n);

}


void queue_test1_add_element()
{
    size_t start_mem = 0;
    size_t calc_mem = 0;
    int i = 2;
    struct queue *q = queue_init();
    
    struct qnode *n1 = NULL;
    struct qnode *n2 = NULL;
    struct qnode *n3 = NULL;
    struct qnode *n4 = NULL;

    if(q==NULL){
        TEST_FAIL("queue should not be null");
    }else{
        TEST_PASS("queue should not be null");
    }

    start_mem = GetDynMemoryUsage();

    //first element
    n1 = queue_create_node(&i, sizeof(int));

    calc_mem += sizeof(struct qnode) + sizeof(i) + start_mem;

    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct queue node memory check");
    }else{
        TEST_PASS("struct queue node memory check");
    }


    if(!n1){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }


    if(enqueue(q, n1) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if( (*( (int *) q->head->data ) == 2 ) &&\
          ( q->head->prev  == NULL ) &&\
          ( q->tail->next  == NULL ))
    {
        TEST_PASS("queue first element added properly");
    }else{
        TEST_FAIL("queue first element not added properly");
    }

    //second element
    i = 4;
    n2 = queue_create_node(&i, sizeof(int));

    if(!n2){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(enqueue(q, n2) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if(   (*( (int *) q->head->data ) == 2 ) &&\
          (*( (int *) q->head->next->data ) == 4 ) &&\
          ( q->head->prev  == NULL ) &&\
          ( q->tail->next  == NULL ))
    {
        TEST_PASS("queue second element added properly");
    }else{
        TEST_FAIL("queue second element not added properly");
    }

    calc_mem += sizeof(struct qnode) + sizeof(i);

    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct queue node memory check");
    }else{
        TEST_PASS("struct queue node memory check");
    }

    //third element
    i = 6;
    n3 = queue_create_node(&i, sizeof(int));

    if(!n3){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(enqueue(q, n3) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if(   (*( (int *) q->head->data ) == 2 ) &&\
          (*( (int *) q->head->next->data ) == 4 ) &&\
          (*( (int *) q->head->next->next->data ) == 6 ) &&\
          ( q->head->prev  == NULL ) &&\
          ( q->tail->next  == NULL ))
    {
        TEST_PASS("queue third element added properly");
    }else{
        TEST_FAIL("queue third element not added properly");
    }

    calc_mem += sizeof(struct qnode) + sizeof(i);

    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct queue node memory check");
    }else{
        TEST_PASS("struct queue node memory check");
    }



    //fourth element
    i = 8;
    n4 = queue_create_node(&i, sizeof(int));

    if(!n4){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(enqueue(q, n4) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if(   (*( (int *) q->head->data ) == 2 ) &&\
          (*( (int *) q->head->next->data ) == 4 ) &&\
          (*( (int *) q->head->next->next->data ) == 6 ) &&\
          (*( (int *) q->head->next->next->next->data ) == 8 ) &&\
          ( q->head->prev  == NULL ) &&\
          ( q->tail->next  == NULL ))
    {
        TEST_PASS("queue fourth element added properly");
    }else{
        TEST_FAIL("queue fourth element not added properly");
    }

    calc_mem += sizeof(struct qnode) + sizeof(i);

    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct queue node memory check");
    }else{
        TEST_PASS("struct queue node memory check");
    }

}

void queue_test1_delete_element()
{
    int i = 2;
    struct queue *q = queue_init();
    struct qnode *n1 = NULL, *n2 = NULL, *n3 = NULL, *n4 = NULL;

    if(q==NULL){
        TEST_FAIL("queue should not be null");
    }else{
        TEST_PASS("queue should not be null");
    }

    //first element
    n1 = queue_create_node(&i, sizeof(int));

    if(!n1){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }


    if(enqueue(q, n1) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if( *( (int *) q->head->data ) == 2 ){
        TEST_PASS("queue first element added properly");
    }else{
        TEST_FAIL("queue first element not added properly");
    }

    //second element
    i = 4;
    n2 = queue_create_node(NULL, 0);

    if(!n2){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(enqueue(q, n2) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if( (*( (int *) q->head->data ) == 2) && q->head->next->data  == NULL ){
        TEST_PASS("queue second element added properly");
    }else{
        TEST_FAIL("queue second element not added properly");
    }

    //third element
    i = 6;
    n3 = queue_create_node(&i, sizeof(int));

    if(!n3){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(enqueue(q, n3) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if( *( (int *) q->head->next->next->data ) == 6 ){
        TEST_PASS("queue third element added properly");
    }else{
        TEST_FAIL("queue third element not added properly");
    }

    //fourth element
    i = 8;
    n4 = queue_create_node(&i, sizeof(int));

    if(!n4){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(enqueue(q, n4) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if( *( (int *) q->head->next->next->next->data ) == 8 ){
        TEST_PASS("queue fourth element added properly");
    }else{
        TEST_FAIL("queue fourth element not added properly");
    }

    //                     H                    T
    //delete           |   2 <-> NULL <-> 6 <-> 8

    n1 = dequeue(q);
    if(n1 != NULL){
        TEST_PASS("queue element dequeued");
    }else{
        TEST_FAIL("queue element not dequeued");
    }

    if( *((int*)n1->data) == 2){
        TEST_PASS("dequeue success");
    }else{
        TEST_FAIL("dequeue failure");
    }

    if(     (q->head->data == NULL) \
        && ( *( (int *) q->head->next->data) == 6) \
        && ( *( (int *) q->head->next->next->data) == 8) \
        && (            q->head->next->next->next == NULL) \
        && (            q->head->prev  == NULL) \
        && (            q->tail->next  == NULL )){
        TEST_PASS("queue third element(6) deleted properly");
    }else{
        TEST_FAIL("queue third element(6) deleted properly");
    }

    //                      H              T
    //delete           |    NULL <-> 6 <-> 8

    n1 = dequeue(q);
    if(n1 != NULL){
        TEST_PASS("queue element dequeued");
    }else{
        TEST_FAIL("queue element not dequeued");
    }

    if( n1->data == NULL){
        TEST_PASS("dequeue success");
    }else{
        TEST_FAIL("dequeue failure");
    }

    if( (    *( (int *) q->head->data) == 6) \
        && ( *( (int *) q->head->next->data) == 8) \
        && (            q->head->next->next == NULL) \
        && (            q->head->prev  == NULL) \
        && (            q->tail->next  == NULL )){
        TEST_PASS("queue head element(2) deleted properly");
    }else{
        TEST_FAIL("queue head element(2) deleted properly");
    }

    //                      H     T
    //delete           |    6 <-> 8

    n1 = dequeue(q);
    if(n1 != NULL){
        TEST_PASS("queue element dequeued");
    }else{
        TEST_FAIL("queue element not dequeued");
    }

    if( *((int*)n1->data) == 6){
        TEST_PASS("dequeue success");
    }else{
        TEST_FAIL("dequeue failure");
    }

    if( (    *( (int *) q->head->data) == 8) \
        && ( *( (int *) q->tail->data) == 8) \
        && (            q->head->next  == NULL) \
        && (            q->head->prev  == NULL) \
        && (            q->tail->next  == NULL) \
        && (            q->tail->prev  == NULL )){
        TEST_PASS("queue third element deleted properly");
    }else{
        TEST_FAIL("queue third element deleted properly");
    }

    //                      HT
    //delete           |    8

    n1 = dequeue(q);
    if(n1 != NULL){
        TEST_PASS("queue element dequeued");
    }else{
        TEST_FAIL("queue element not dequeued");
    }

    if( *((int*)n1->data) == 8){
        TEST_PASS("dequeue success");
    }else{
        TEST_FAIL("dequeue failure");
    }

    if( ( q->head  == NULL) &&\
        ( q->tail  == NULL))
    {
        TEST_PASS("queue last element deleted properly");
    }else{
        TEST_FAIL("queue last element deleted properly");
    }


}

void queue_terminate_test()
{
    int i = 2;
    struct queue *q = queue_init();
    struct qnode *n1 = NULL, *n2 = NULL, *n3 = NULL, *n4 = NULL;

    struct rusage r_usage;

    if(q==NULL){
        TEST_FAIL("queue should not be null");
    }else{
        TEST_PASS("queue should not be null");
    }

    //first element
    n1 = queue_create_node(&i, sizeof(int));

    if(!n1){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }


    if(enqueue(q, n1) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if( *( (int *) q->head->data ) == 2 ){
        TEST_PASS("queue first element added properly");
    }else{
        TEST_FAIL("queue first element not added properly");
    }

    //second element
    i = 4;
    n2 = queue_create_node(&i, sizeof(int));

    if(!n2){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(enqueue(q, n2) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if( *( (int *) q->head->next->data ) == 4 ){
        TEST_PASS("queue second element added properly");
    }else{
        TEST_FAIL("queue second element not added properly");
    }

    //third element
    i = 6;
    n3 = queue_create_node(&i, sizeof(int));

    if(!n3){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(enqueue(q, n3) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if( *( (int *) q->head->next->next->data ) == 6 ){
        TEST_PASS("queue third element added properly");
    }else{
        TEST_FAIL("queue third element not added properly");
    }

    //fourth element
    i = 8;
    n4 = queue_create_node(&i, sizeof(int));

    if(!n4){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(enqueue(q, n4) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    if( *( (int *) q->head->next->next->next->data ) == 8 ){
        TEST_PASS("queue fourth element added properly");
    }else{
        TEST_FAIL("queue fourth element not added properly");
    }

    if(queue_terminate(q) == 0){
        TEST_PASS("queue terminate");
    }else{
        TEST_FAIL("queue terminate");
    }

}

void *th_create_n_add_node(void *args)
{
    int val = HUNDRED_MS * (rand()%7);
    usleep(val);

    int i = (int)GetDynMemoryUsage();
    struct queue *q = (struct queue *) args;
    struct qnode *n = NULL;
    n = queue_create_node(&i, sizeof(int));

    if(!n){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(enqueue(q, n) == 0){
        TEST_PASS("enqueue() success");
    }else{
        TEST_FAIL("enqueue() success");
    }

    return NULL;
}

void *th_delete_node(void *args)
{
    int val = HUNDRED_MS * (rand()%7);
    usleep(val);

    struct queue *q = (struct queue *) args;
    struct qnode *n = NULL;

    n = dequeue(q);
    if(n){
        printf("[ status ] dequeued item - %d\n", *((int *)n->data));
        LFREE(n->data);
        LFREE(n);
    }else{
        printf("[ status ] dequeued item - NULL - Q Empty\n");
    }
    return NULL;
}

void queue_test1_multithreaded()
{
    int i = 0;
    struct queue *q = queue_init();
    struct qnode *itr = NULL;
    pthread_t tid[100], dtid[100]; 

    for(i=0;i<100;i++){
        pthread_create(&tid[i], NULL, &th_create_n_add_node, (void *)q);
    }

    traverse_queue(q);
    
    for(i=0;i<100;i++){
        pthread_join(tid[i], NULL);
    }

    traverse_queue(q);
    
    if(get_nodes_count(q) != 100){
        TEST_FAIL("threaded queue create");
    }else{
        TEST_PASS("threaded queue create");
    }

    for(i=0;i<100;i++){
        pthread_create(&dtid[i], NULL, &th_delete_node, (void *)q);
    }
 
    traverse_queue(q);
    
    for(i=0;i<100;i++){
        pthread_join(dtid[i], NULL);
    }
    
    traverse_queue(q);


    if(get_nodes_count(q) != 0){
        TEST_FAIL("threaded queue delete");
    }else{
        TEST_PASS("threaded queue delete");
    }

}

void queue_test2_multithreaded()
{
    int i = 0;
    struct queue *q = queue_init();
    struct qnode *itr = NULL;
    pthread_t tid[100], dtid[100]; 

    for(i=0;i<100;i++){
        pthread_create(&tid[i], NULL, &th_create_n_add_node, (void *)q);
        pthread_create(&dtid[i], NULL, &th_delete_node, (void *)q);
    }
    
    traverse_queue(q);

    for(i=0;i<100;i++){
        pthread_join(dtid[i], NULL);
        pthread_join(tid[i], NULL);
    }


    traverse_queue(q);
    queue_terminate(q);
}



int main()
{
    int i = 0;
    testcase_t testcases[] = {
        queue_test1_create_node,
        queue_test1_create_queue,
        queue_test1_add_element,
        queue_test1_delete_element,
        queue_terminate_test,
        queue_test1_multithreaded,
        queue_test2_multithreaded, 
        NULL
    };
    
    while(testcases[i] != NULL){
        testcases[i](); 
        i++;
    }

    return 0;
}
