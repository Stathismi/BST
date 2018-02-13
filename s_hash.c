#include "s_hash.h"


FILE* read_file(char* argv, FILE* fp)
{
   fp=fopen(argv, "r");
   if(fp==NULL){
      ON_ERROR("Opening of a file Failed\n");
   }
   return fp;
}

node** chained_hashtable(FILE* fp1)
{
   node** array=NULL;
   array=array_init(array);
   array=file_to_hashtable(array, fp1);
   return array;
}

node** array_init(node** array)
{
   array=(node**) calloc(PRIME_ARRAY, (sizeof(node)));
   if (array==NULL) {
      ON_ERROR("Creation of array Failed\n");
   }
   return array;
}

node** file_to_hashtable(node** array, FILE* fp1)
{
   char str[STR_SIZE];
   char str1[STR_SIZE];
   while(fgets(str, STR_SIZE, fp1)!=NULL){
      if(sscanf(str, "%s", str1)==1){
         array=insert_word(array, str1);
      }
   }
   return array;
}

node** insert_word(node** array, char* tmp)
{
   int index;
   index=hash_key(tmp);
   if(array[index]==NULL){
      array[index]=node_init(tmp);
   }
   else{
      if(!is_in(array[index], tmp)){
         array[index]=generate_linked_list(tmp, array[index]);
      }
   }
   return array;
}
/*hash function retrieved from The C Programming Language (2nd Edition)
by Brian W. Kernighan,‎ Dennis Ritchie*/
unsigned long hash_key(char* tmp)
{
   unsigned long hashval;
   for (hashval = 0; *tmp != '\0'; tmp++)
   hashval=*tmp + HASH_NUM*hashval;
   return hashval % PRIME_ARRAY;
}

node* node_init(char *tmp)
{
   node* n;
   n=(node*) calloc(NODE_SIZE, sizeof(node));
   if(n==NULL){
      ON_ERROR("Creation of node Failed\n");
   }
   strcpy(n->data, tmp);
   n->next=NULL;
   return n;
}

node* generate_linked_list(char* tmp, node* first_value)
{
   node *start, *current;
   int end=0;
   start = current = first_value;
   while(end==0){
      if(current->next==NULL){
         current->next=node_init(tmp);
         end=1;
      }
      current = current->next;
   }
   return start;
}

int is_in(node* array_element, char* tmp){
   if(array_element==NULL){
      return 0;
   }
   while(array_element!=NULL){
      if(strcmp(array_element->data, tmp)==0){
         return 1;
      }
      array_element=array_element->next;
   }
   return 0;
}

node** misspelt_chained_hashtable(node** dictionary_hash, FILE* fp2)
{
   char str[STR_SIZE];
   char str1[STR_SIZE];
   int index;
   node** misspelt=NULL;
   misspelt=array_init(misspelt);
   while(fgets(str, STR_SIZE, fp2)!=NULL){
      if(sscanf(str, "%s", str1)==1){
         index = hash_key(str1);
         if(!is_in(dictionary_hash[index], str1) && !is_in(misspelt[index], str1)){
            misspelt= insert_word(misspelt, str1);
            printf("%s\n",str1);
         }
      }
   }
   return misspelt;
}

void free_list(node* array_position)
{
   if(array_position==NULL){
      return;
   }
   free_list(array_position->next);
   free(array_position);
}

void free_all(node** a)
{
   int i;
   for (i=0; i<PRIME_ARRAY; i++) {
      free_list(a[i]);
   }
   free(a);
}
