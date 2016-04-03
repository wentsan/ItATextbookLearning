/**This file is based on the code@http://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console
*/

#include <iostream>

struct node{
  int key;
  struct node *p;
  struct node *left;
  struct node *right;
  int color;
};

int _print_t(struct node *tree, int is_left, int offset, int depth, char s[20][255], struct node *transNil)
{
    char b[20];
    int width = 6;          //set the char length of "key" value when printed.

    if (tree == transNil) return 0;

    sprintf(b, "(%03d)%s", tree->key, (tree->color == 1? "R" : "B"));

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s, transNil);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s, transNil);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2 - 1] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2 - 1] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2 - 1] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }

    return left + width + right;
}

void print_t(struct node *tree, struct node *tnil)
{
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s, tnil);

    std::cout<<std::endl<<"Now draw the tree:"<<std::endl;
    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}
