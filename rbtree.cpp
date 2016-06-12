#include "drawTreeInTerminal.h"

using namespace std;

#define T_nil T[0]
#define T_root T[1]
#define RED 1
#define BLACK 0
#define MAXLENGTH 10

struct node *treeMinimum(struct node *T[], struct node *x);
void leftRotate(struct node *T[], struct node *x);
void rightRotate(struct node *T[], struct node *x);
void rbInsert(struct node *T[], struct node *z);
void rbInsertFixedUp(struct node *T[], struct node *z);
void rbDelete(struct node *T[], struct node *z);
void rbDeleteFixedUp(struct node *T[], struct node *x);
void printArray(struct node *x);

struct node *treeMinimum(struct node *T[], struct node *x) {
  while (x->left != T_nil) {
    x = x->left;
  }
  return x;
}

void leftRotate(struct node *T[], struct node *x) {
  struct node *y = T_nil;
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
  struct node *y = T_nil;
  y = x->left;
  y->left = x->right;
  if (x->right != T_nil) (x->right)->p = y;
  y->p = x->p;
  if (x->p == T_nil) {
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
  struct node *y = T_nil;
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

void rbTransPlant(struct node *T[], struct node *u, struct node *v){
  if (u->p == T_nil)
    T_root = v;
  else if (u == (u->p)->left)
    (u->p)->left = v;
  else
    (u->p)->right = v;
  v->p = u->p;
}

void rbDelete(struct node *T[], struct node *z) {
  struct node *x = T_nil;
  struct node *y = T_nil;
  int y_orginal_color;

  y = z;
  y_orginal_color = y->color;

  if (z->left == T_nil) {
    x = z->right;
    rbTransPlant(T, z, z->right);
  }else if (z->right == T_nil) {
    x = z->left;
    rbTransPlant(T, z, z->left);
  }else{
    y = treeMinimum(T, z->right);
    //y_orginal_color = y->color;  No need for this line
    x = y->right;
    if (y->p == z) {
      x->p = y;
    }else{
      rbTransPlant(T, y, y->right);
      y->right = z->right;
      (y->right)->p = y;
    }
    rbTransPlant(T, z, y);
    y->left = z->left;
    (y->left)->p = y;
    y->color = z->color;
  }
  if (y_orginal_color == BLACK) {
    rbDeleteFixedUp(T, x);
  }
}

void rbDeleteFixedUp(struct node *T[], struct node *x) {
  struct node *w = T_nil;
  while (x != T_root && x->color == BLACK) {
    if (x == (x->p)->left) {
      w = (x->p)->right;
      if (w->color == RED) {
        w->color = BLACK;
        (x->p)->color = RED;
        leftRotate(T, x->p);
        w = (x->p)->right;
      }
      if ((w->left)->color == BLACK && (w->right)->color == BLACK) {
        w->color = RED;
        x = x->p;
      }else{
        if ((w->right)->color == BLACK) {
          (w->left)->color = BLACK;
          w->color = RED;
          rightRotate(T, w);
          w = (x->p)->right;
        }
        w->color = (x->p)->color;
        (x->p)->color = BLACK;
        (w->right)->color = BLACK;
        leftRotate(T, x->p);
        x = T_root;
      }
    }else{
      w = (x->p)->left;
      if (w->color == RED) {
        w->color = BLACK;
        (x->p)->color = RED;
        leftRotate(T, x->p);
        w = (x->p)->left;
      }
      if ((w->right)->color == BLACK && (w->left)->color == BLACK) {
        w->color = RED;
        x = x->p;
      }else{
        if ((w->left)->color == BLACK) {
          (w->right)->color = BLACK;
          w->color = RED;
          leftRotate(T, w);
          w = (x->p)->left;
        }
        w->color = (x->p)->color;
        (x->p)->color = BLACK;
        (w->left)->color = BLACK;
        rightRotate(T, x->p);
        x = T_root;
      }
    }
  }
  x->color = BLACK;
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

  char modifyOrNot;

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

  while (1) {
    cout << "Continue to modify the tree?[y/n]: ";
    cin >> modifyOrNot;
    if (modifyOrNot == 'y') {
      int index;
      cout << "Please enter the array index that you want to delete: ";
      cin >> index;
      rbDelete(T, x + index);
      print_t(T_root, T_nil);
    }else{
      return 0;
    }
  }
}
