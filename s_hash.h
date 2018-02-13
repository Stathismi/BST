#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)
#define STR_SIZE 30
#define PRIME_ARRAY 577867
#define NODE_SIZE 1
#define HASH_NUM 31
#define FIRST_FILE 1
#define SECOND_FILE 2
#define ARGUMENTS_REQUIRED 3

struct node
{
   char data[STR_SIZE];
   struct node *next;
};
typedef struct node node;

FILE* read_file(char* argv, FILE* fp);
node** chained_hashtable(FILE *fp1);
node** array_init(node** array);
node** file_to_hashtable(node** array, FILE* fp1);
node** insert_word(node** array, char* tmp);
unsigned long hash_key(char* tmp);
node* node_init(char* tmp);
node* generate_linked_list(char* tmp, node* first_value);
int is_in(node* array_element, char* tmp);
node** misspelt_chained_hashtable(node** dictionary_hash, FILE* fp2);
void free_list(node* array_position);
void free_all(node** array);

#endif
