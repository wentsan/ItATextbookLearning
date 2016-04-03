#include "drawTreeInTerminal.h"

using namespace std;

#define T_nil T[0]
#define T_root T[1]
#define RED 1
#define BLACK 0
#define MAXLENGTH 10

void leftRotate(struct node *T[], struct node *x);
void rightRotate(struct node *T[], struct node *x);
void rbInsert(struct node *T[], struct node *z);
void rbInsertFixedUp(struct node *T[], struct node *z);
void printArray(struct node *x);

void leftRotate(struct node *T[], struct node *x) {
  struct node *y;
  y = x->right;
  x->right = y->left;
  if (y->left != T_nil) (y->left)->p = x;
  y->p = x->p;
  if (x->p == T_nil) {
    T_root = y;
  }else if (x == (x->p)->left) {
    (x->p)->left = y;
  }else{
    (x->p)->right = y;
  }
  y->left = x;
  x->p = y;
}

void rightRotate(struct node *T[], struct node *x) {
  struct node *y;
  y = x->left;
  y->left = x->right;
  if (x->right != T_nil) (x->right)->p = y;
  y->p = x->p;
  if (x->p != T_nil) {
    T_root = y;
  }else if (x == (x->p)->left) {
    (x->p)->left = y;
  }else{
    (x->p)->right = y;
  }
  y->right = x;
  x->p = y;
}

void rbInsert(struct node *T[], struct node *z){
  struct node *y = T_nil;
  struct node *x = T_root;
  //cout<<y<<endl<<x<<endl;

  while (x != T_nil){
    y = x;
    x = ((z->key) < (x->key) ? (x->left) : (x->right));
  }
  z->p = y;
  if (y == T_nil)
    {
      T_root = z;
    }else if ((z->key) < (y->key))
    {
      y->left = z;
    }else{
      y->right = z;
  }
  z->left = T_nil;
  z->right = T_nil;
  z->color = RED;
  rbInsertFixedUp(T, z);
}

void rbInsertFixedUp(struct node *T[], struct node *z){
  struct node *y;
  while((z->p)->color == RED){
    if ((z->p) == (((z->p)->p)->left))
      {
	       y = ((z->p)->p)->right;
	        if (y->color == RED)
	         {
	            (z->p)->color = BLACK;
	            y->color = BLACK;
	            ((z->p)->p)->color = RED;
	            z = (z->p)->p;
		          }else{
		              if (z == (z->p)->right)
		                {
		                    z = z->p;
		                    leftRotate(T,z);
		                    }
		              (z->p)->color = BLACK;
		              ((z->p)->p)->color = RED;
		              rightRotate(T, ((z->p)->p));
		              }
      }else{
      	    y = ((z->p)->p)->left;
	           if (y->color == RED)
	            {
	                (z->p)->color = BLACK;
	                y->color = BLACK;
	                ((z->p)->p)->color = RED;
	                z = (z->p)->p;
	           }else{
		          if (z == (z->p)->left)
		            {
		                z = z->p;
		                rightRotate(T,z);
		                }
		          (z->p)->color = BLACK;
		          ((z->p)->p)->color = RED;
		          leftRotate(T, ((z->p)->p));
		          }
        }
  }
  T_root->color = BLACK;
}

void printArray(struct node *x, int xLength){

  cout<<endl<<"Now print the array:"<<endl;

  for (int i = 0; i < xLength; ++i)
    {
      cout<<"x["<<i<<"]->key  :"<<(x+i)->key<<"\t"
          <<"x["<<i<<"]->color:"<<((x+i)->color == 1? "RED  " : "BLACK")<<" "
          <<"LEFT:"<<(x+i)->left->key<<"\t"
          <<"RIGHT:"<<(x+i)->right->key<<endl;
    }
}

int main(int argc, char *argv[])
{
  struct node x[MAXLENGTH];
  struct node transNil;
  struct node *T[2];

  transNil.p = NULL;
  transNil.left = NULL;
  transNil.right = NULL;
  transNil.color = BLACK;
  transNil.key = 0;

  T_nil = &transNil;
  T_root = &transNil;

  //cout<<T_nil<<endl<<T_root<<endl;

  for (int i = 0; i < MAXLENGTH; ++i)
    {
      x[i].p = T_nil;
      cout << "x["<<i<<"]:  ___\b\b\b";
      cin >> x[i].key;
      x[i].left = T_nil;
      x[i].right = T_nil;
      x[i].color = BLACK;
      rbInsert(T, x+i);
    }

  printArray(x, MAXLENGTH);
  print_t(T_root, T_nil);

  return 0;
}
