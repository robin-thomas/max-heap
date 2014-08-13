/*
	File:   maxHeap.c
    Desc:   Program showing various operations on a binary max heap along with their time complexities
    Author: Robin Thomas <robinthomas2591@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) x / 2

typedef struct node {
    int data ;
} node ;

typedef struct maxHeap {
    int size ;
    node *elem ;
} maxHeap ;


/*
    Function to initialize the max heap with size = 0
*/
maxHeap initMaxHeap(int size) {
    maxHeap hp ;
    hp.size = 0 ;
    hp.elem = malloc(size * sizeof(node)) ;
    return hp ;
}


/*
    Function to swap data within two nodes of the max heap using pointers
*/
void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}


/*
    Heapify function is used to make sure that the heap property is never violated
    In case of deletion of a node, or creating a max heap from an array, heap property
    may be violated. In such cases, heapify function can be called to make sure that
    heap property is never violated
*/
void heapify(maxHeap *hp, int i) {
    int largest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].data > hp->elem[i].data) ? LCHILD(i) : i ;
    if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)].data > hp->elem[largest].data) {
        largest = RCHILD(i) ;
    }
    if(largest != i) {
        swap(&(hp->elem[i]), &(hp->elem[largest])) ;
        heapify(hp, largest) ;
    }
}


/* 
    Build a Max Heap given an array of numbers
    Instead of using insertNode() function n times for total complexity of O(nlogn),
    we can use the buildMaxHeap() function to build the heap in O(n) time
*/
void buildMaxHeap(maxHeap *hp, int *arr, int size) {
    int i ;

    // Insertion into the heap without violating the shape property
    for(i = 0; i < size; i++) {
        if(hp->size) {
            hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
        } else {
            hp->elem = malloc(sizeof(node)) ;
        }
        node nd ;
        nd.data = arr[i] ;
        hp->elem[(hp->size)++] = nd ;
    }

    // Making sure that heap property is also satisfied
    for(i = (hp->size - 1) / 2; i >= 0; i--) {
        heapify(hp, i) ;
    }
}


/*
    Function to insert a node into the max heap, by allocating space for that node in the
    heap and also making sure that the heap property and shape propety are never violated.
*/
void insertNode(maxHeap *hp, int data) {
    node nd ;
    nd.data = data ;

    int i = (hp->size)++ ;
    while(i && nd.data > hp->elem[PARENT(i)].data) {
        hp->elem[i] = hp->elem[PARENT(i)] ;
        i = PARENT(i) ;
    }
    hp->elem[i] = nd ;
}


/*
    Function to delete a node from the max heap
    It shall remove the root node, and place the last node in its place
    and then call heapify function to make sure that the heap property
    is never violated
*/
void deleteNode(maxHeap *hp) {
    if(hp->size) {
        printf("Deleting node %d\n\n", hp->elem[0].data) ;
        hp->elem[0] = hp->elem[--(hp->size)] ;
        hp->elem = realloc(hp->elem, hp->size * sizeof(node)) ;
        heapify(hp, 0) ;
    } else {
        printf("\nMax Heap is empty!\n") ;
        free(hp->elem) ;
    }
}


/*
    Function to get minimum node from a max heap
    The minimum node shall always be one of the leaf nodes. So we shall recursively
    move through both left and right child, until we find their minimum nodes, and
    compare which is smaller. It shall be done recursively until we get the minimum
    node
*/
int getMinNode(maxHeap *hp, int i) {
    if(LCHILD(i) >= hp->size) {
        return hp->elem[i].data ;
    }

    int l = getMinNode(hp, LCHILD(i)) ;
    int r = getMinNode(hp, RCHILD(i)) ;

    if(l <= r) {
        return l ;
    } else {
        return r ;
    }
}


/*
    Function to clear the memory allocated for the max heap
*/
void deleteMaxHeap(maxHeap *hp) {
    free(hp->elem) ;
}


void inorderTraversal(maxHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        inorderTraversal(hp, LCHILD(i)) ;
    }
    printf("%d ", hp->elem[i].data) ;
    if(RCHILD(i) < hp->size) {
        inorderTraversal(hp, RCHILD(i)) ;
    }
}


void preorderTraversal(maxHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        preorderTraversal(hp, LCHILD(i)) ;
    }
    if(RCHILD(i) < hp->size) {
        preorderTraversal(hp, RCHILD(i)) ;
    }
    printf("%d ", hp->elem[i].data) ;
}


void postorderTraversal(maxHeap *hp, int i) {
    printf("%d ", hp->elem[i].data) ;
    if(LCHILD(i) < hp->size) {
        postOrderTraversal(hp, LCHILD(i)) ;
    }
    if(RCHILD(i) < hp->size) {
        postorderTraversal(hp, RCHILD(i)) ;
    }
}

void levelorderTraversal(maxHeap *hp) {
	int i ;
	for(i = 0; i < hp->size; i++) {
		printf("%d ", hp->elem[i].data) ;
	}
}
