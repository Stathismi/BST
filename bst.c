#include "bst.h"

#define BST_SIZE 1
#define BST_NODESIZE 1
#define DATA_SIZE 1
#define PRNT_SIZE 1
#define STR_SIZE 30
#define HALF 2
#define PARENTHESIS_SIZE 2
#define NULL_SIZE 1


bstnode* create_bstnode(bst* a, void* v);
void insert_element(bst* b, bstnode* top, void* v);
int traverse_bst(bstnode* top);
int max_depth_recursive(bstnode* top);
bool is_in_recursive(bst* b, bstnode* top, void* v);
void bst_freenode(bstnode* top);
int* in_order_traversal(bst* b, bstnode* top, void* v);
char* print_recursive(bst* b, bstnode* top);
void rebalance_recursive(bst* c, void* words, int start, int end);

bst* bst_init(int sz, int(*comp)(const void* a, const void* b),
char*(*prnt)(const void* a))
{
   bst* b;
   b=(bst*) calloc(BST_SIZE, sizeof(bst));
   if(b==NULL){
      ON_ERROR("Creation of bst Failed\n");
   }
   b->top=NULL;
   b->elsz=sz;
   b->compare=comp;
   b->prntnode=prnt;
   return b;
}

bstnode* create_bstnode(bst* b, void* v)
{
   bstnode* n;
   n=(bstnode*) calloc(BST_NODESIZE, sizeof(bstnode));
   if(n==NULL){
      ON_ERROR("Creation of bstnode Failed\n");
   }
   n->data=(void*) calloc(DATA_SIZE, b->elsz);
   if(n->data==NULL){
      ON_ERROR("Creation of data Failed\n");
   }
   memcpy(n->data, v, b->elsz);
   n->left=NULL;
   n->right=NULL;
   return n;
}

void insert_element(bst* b, bstnode* top, void* v)
{
   if(b->compare(v, top->data)<0){
      if(top->left==NULL){
         top->left=create_bstnode(b, v);
      }
      else{
         insert_element(b, top->left,v);
      }
   }
   else{
      if(top->right==NULL){
         top->right=create_bstnode(b, v);
      }
      else{
         insert_element(b, top->right,v);
      }
   }
}

void bst_insert(bst* b, void* v)
{
   if((bst_isin(b, v))){
      return;
   }
   if(b->top==NULL){
      b->top=create_bstnode(b, v);
      return;
   }
   insert_element(b, b->top, v);
}

int traverse_bst(bstnode *top)
{
   if(top==NULL){
      return 0;
   }
   return 1+traverse_bst(top->left)+traverse_bst(top->right);
}

int bst_size(bst* b)
{
   return traverse_bst(b->top);
}

int max_depth_recursive(bstnode* top)
{
   int left_depth, right_depth;
   if(top==NULL){
      return 0;
   }
   left_depth=max_depth_recursive(top->left);
   right_depth=max_depth_recursive(top->right);
   if(left_depth>right_depth){
      return (left_depth+1);
   }
   else{
      return (right_depth+1);
   }
}

int bst_maxdepth(bst* b)
{
   return max_depth_recursive(b->top);
}

bool is_in_recursive(bst* b, bstnode* top, void* v)
{
   if(top==NULL){
      return false;
   }
   if(b->compare(top->data, v)==0){
      return true;
   }
   if(b->compare(top->data, v)>0){
      return is_in_recursive(b, top->left, v);
   }
   else{
      return is_in_recursive(b, top->right,v);
   }
}

bool bst_isin(bst* b, void* v)
{
   return is_in_recursive(b, b->top, v);
}

void bst_insertarray(bst* b, void* v, int n)
{
   int i;
   for(i=0; i<n; i++){
      bst_insert(b, (char*)v+i*(b->elsz));
   }
}

void bst_freenode(bstnode* top)
{
   if(top==NULL){
      return;
   }
   bst_freenode(top->left);
   bst_freenode(top->right);
   free(top->data);
   free(top);
}

void bst_free(bst** p)
{
   if(p!=NULL){
      bst* a=*p;
      bst_freenode(a->top);
      free(a);
      *p=NULL;
   }
}

int* in_order_traversal(bst* b, bstnode* top, void* v)
{
   static int i=0;
   if(top==NULL){
      return &i;
   }
   in_order_traversal(b, top->left, v);
   memcpy((char*)v+i*(b->elsz), top->data, b->elsz);
   ++i;
   in_order_traversal(b, top->right, v);
   return &i;
}

void bst_getordered(bst* b, void* v)
{
   int *i;
   i=in_order_traversal(b, b->top, v);
   *i=0;
}

char* print_recursive(bst* b, bstnode* top)
{
   char *str, *l, *r;
   int s1=0, s2=0, s3=0;
   if(top==NULL){
      str=(char*) calloc(PRNT_SIZE, sizeof(char));
      if(str==NULL){
         ON_ERROR("Creation of str Failed\n");
      }
      return str;
   }
   l=print_recursive(b, top->left);
   r=print_recursive(b, top->right);
   s1=strlen(l);
   s2=strlen(r);
   s3=strlen(b->prntnode(top->data));
   str=(char*) calloc(PRNT_SIZE, s1+s2+s3+PARENTHESIS_SIZE+NULL_SIZE);
   if(str==NULL){
      ON_ERROR("Creation of str Failed\n");
   }
   sprintf(str, "(%s%s%s)", b->prntnode(top->data), l, r);

   free(l);
   free(r);
   return str;
}

char* bst_print(bst* b)
{
   return print_recursive(b, b->top);
}

void rebalance_recursive(bst* c, void* words, int start, int end)
{
   int median;
   if(start>end){
      return ;
   }
   median= (start+end)/HALF;
   bst_insert(c, (char*)words+median*(c->elsz));
   rebalance_recursive(c, words, start, median-1);
   rebalance_recursive(c, words, median+1, end);
}

bst* bst_rebalance(bst* b)
{
   bst* c;
   void* words;
   int start=0;
   int end=bst_size(b)-1;
   words=(void*) calloc(bst_size(b), b->elsz);
   if(words==NULL){
      ON_ERROR("Creation of words Failed\n");
   }
   bst_getordered(b, words);
   c=bst_init(b->elsz, b->compare, b->prntnode);
   rebalance_recursive(c, words, start, end);
   free(words);
   return c;
}
