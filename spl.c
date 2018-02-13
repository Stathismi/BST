#include "bst.h"

#define STR_SIZE 30
#define FIRST_FILE 1
#define SECOND_FILE 2
#define ARGUMENTS_REQUIRED 3

int mystrcmp(const void* a, const void* b);
char* myprintstr(const void* v);
char* myprintchr(const void* v);
void bst_dictionary(bst* b, FILE* fp1);
void bst_misspelt(bst* b, bst* c, FILE* fp );
FILE* read_file(char* argv, FILE* fp);

int main(int argc, char *argv[])
{
   bst *b, *c;
   FILE *fp1=NULL, *fp2=NULL;
   if(argc!=ARGUMENTS_REQUIRED){
      ON_ERROR("argc must be three words\n");
   }
   fp1=read_file(argv[FIRST_FILE], fp1);
   fp2=read_file(argv[SECOND_FILE], fp2);

   b=bst_init(STR_SIZE, mystrcmp, myprintchr);
   bst_dictionary(b, fp1);
   c=bst_init(STR_SIZE, mystrcmp, myprintchr);
   bst_misspelt(b,c, fp2);

   bst_free(&b);
   bst_free(&c);
   fclose(fp1);
   fclose(fp2);
   return 0;
}

FILE* read_file(char* argv, FILE* fp){
   fp=fopen(argv, "r");
   if(fp==NULL){
      ON_ERROR("Opening of a file Failed\n");
   }
   return fp;
}

void bst_dictionary(bst* b, FILE* fp){
   char str[STR_SIZE];
   char str1[STR_SIZE];
   while(fgets(str, STR_SIZE, fp)!=NULL){
      if(sscanf(str, "%s", str1)==1){
         bst_insert(b, str1);
      }
   }
}

void bst_misspelt(bst* b, bst* c, FILE* fp ){
   char str[STR_SIZE];
   char str1[STR_SIZE];
   while(fgets(str, STR_SIZE, fp)!= NULL){
      if(sscanf(str, "%s", str1)==1){
         if(bst_isin(b, str1)==false && bst_isin(c, str1)==false){
            bst_insert(c, str1);
            printf("%s\n",c->prntnode(str1));
         }
      }
   }
}

char* myprintchr(const void* v)
{
   static char str[100];
   sprintf(str, "%s", (char*)v);
   return str;
}
int mystrcmp(const void* a, const void* b)
{
   return strcmp(a, b);
}
