#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"

const int tableSize=101;

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
 int sizeInBits = 8*sizeof(unsigned int);
 shift = shift & (sizeInBits - 1);
 if ( shift == 0 )
 return value;
 return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {
 unsigned int result = 0xBAE86554;
 while (*input) {
 result ^= *input++;
 result = rotate_left(result, 5);
 }
 return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
 return pre_hash(key)%tableSize;
}

// NodeObj
typedef struct NodeObj{
   char* key;
   char* value;
   struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// constructor of the Node type
Node newNode(char* x, char* y) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->key = x;
   N->value = y;
   N->next = NULL;
   return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
// Dictionary
// Exported reference type
typedef struct DictionaryObj{
    Node head;
    int size;
    Node hashtable[100];
}DictionaryObj;

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary(void){
    Dictionary D = malloc(sizeof(DictionaryObj));
    assert(D!=NULL);
    D->head = NULL;
    D->size = 0;
    for(int i = 0;i<tableSize;i++){
        D->hashtable[i] = NULL;
    }
    return D;
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* pD){
     if( pD!=NULL && *pD!=NULL ){
      if( !isEmpty(*pD) ) makeEmpty(*pD);
      free(*pD);
      *pD = NULL;
   }
}

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D){
    return(D->size==0);
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D){
    return (D->size);
}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no 
// such value v exists.
// pre: none
char* lookup(Dictionary D, char* k){
    if(D->hashtable[hash(k)] == NULL){
       return NULL;
   }
   else {
       Node W = D->hashtable[hash(k)];
       if(strcmp(W->key,k) == 0){
           return W->value;
       }
       else{
       while(W->next != NULL){
           W = W->next;
           if(strcmp(W->key,k)==0){
               return W->value;
           }
       }
       }
   }
   return NULL;
}
// insert()
// inserts new (key,value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* k, char* v){
    if(lookup(D,k) == NULL) {
        if(D->hashtable[hash(k)] == NULL){
			D->hashtable[hash(k)] = newNode(k,v);
	    }
	    else {
	    Node N = D->hashtable[hash(k)];
	    D->hashtable[hash(k)] = newNode(k,v);
	    D->hashtable[hash(k)]->next = N;
        }
    }
		D->size++;
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* k){
    if(lookup(D,k) != NULL) {
		Node N = D->hashtable[hash(k)];
		if(strcmp(N->key,k) == 0){
		    Node P = N->next;
		    freeNode(&N);
		    D->hashtable[hash(k)] = P;
		}
		else{
		    while(N->next != NULL){
		        if(strcmp(N->next->key,k) == 0){
		            break;
		        }
		        N = N->next;
		    }
		    Node W = N->next;
		    N->next = W->next;
		    freeNode(&W);
		}
			D->size--;
		}
		else {
		 fprintf(stderr, "error: key not found\n");
         exit(EXIT_FAILURE);
		}
}

// makeEmpty()
// re-sets D to the empty state.
// pre: none
void makeEmpty(Dictionary D){
   for( int i = 0;i<tableSize;i++){
      if(D->hashtable[i] != NULL){
          Node N = D->hashtable[i];
          while(N != NULL){
              delete(D,N->key);
              N = N->next;
          }
      }
   }
}

// printDictionary()
// pre: none
// prints a text representation of D to the file pointed to by out
void printDictionary(FILE* out, Dictionary D){
   for(int i = 0;i<tableSize;i++){
      if(D->hashtable[i] != NULL){
          Node N = D->hashtable[i];
          while(N != NULL){
              fprintf(out, "%s %s\n", N->key,N->value);
              N = N->next;
          }
      }
   }
}
