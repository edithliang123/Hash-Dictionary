#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

#define MAX_LEN 180

int main(int argc, char* argv[]){
	//create Dictionary Object A
	Dictionary A = newDictionary();
	char* k;
	char* v;
	char* word1[] = {"one","two","three","aa","df df"};
	char* word2[] = {"foo","bar","blah","bb","cc"};
	int i;

	//test insert method works correctly
	for(i=0;i<3;i++){
		insert(A, word1[i], word2[i]);
	}

	//test if printDictionary method can print the whole Dictionary
	printDictionary(stdout,A);

	//test if isEmpty method determine the Dictionary correctly
	prinf("%s\n", (isEmpty(A)?"true":"false"));

	//test if the size method determine the size of Dictionary correctly
	printf("%d\n", size(A));

	//test if the delete method delete the key that user wants to remove
	delete(A,"three");

	//test if insert still works after delete
	insert(A,"four","gar");

	printDictionary(stdout,A);

	//test if the makeEmpty method can reset the Dictionary
	makeEmpty(A);

	printf("%s\n", (isEmpty(A)?"true":"false"));

	freeDictionary(&A);

	return(EXIT_SUCCESS);
}


