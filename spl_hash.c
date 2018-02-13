#include "s_hash.h"

int main(int argc, char *argv[])
{
   node** dictionary_hash=NULL;
   node** misspelt_hash=NULL;
   FILE *fp1=NULL, *fp2=NULL;
   if (argc!=ARGUMENTS_REQUIRED){
      ON_ERROR("argc must be three words\n");
   }
   fp1=read_file(argv[FIRST_FILE], fp1);
   fp2=read_file(argv[SECOND_FILE], fp2);

   dictionary_hash=chained_hashtable(fp1);
   misspelt_hash=misspelt_chained_hashtable(dictionary_hash, fp2);

   free_all(&(*dictionary_hash));
   free_all(&(*misspelt_hash));
   fclose(fp1);
   fclose(fp2);
   return 0;
}
