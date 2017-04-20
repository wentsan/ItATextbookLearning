#include <iostream>
#include <stdlib.h>

using namespace std;

#define MAXWORD 100

void print_lcs(char *b[], char *x, int i, int j){
  if (i == 0 || j == 0)
    {
      return;
    }
  if (*(*(b+i)+j) == 'r')
    {
      print_lcs(b, x, i-1, j-1);
      printf("%c ", *(x+i));
    } else if (*(*(b+i)+j) == 'u')
    {
      print_lcs(b, x, i-1, j);
    } else {
    print_lcs(b, x, i, j-1);
  }
}

void lcs_length(char *x, char *y, int m, int n) {
  int c[m][n];
  char *b[m];

  for (int i = 1; i < m; ++i)
    {
      c[i][0] = 0;
    }
  for (int i = 1; i < n; ++i)
    {
      c[0][i] = 0;
    }
  for (int i = 1; i < m; ++i)
    {
      b[i] = (char *)malloc(n * sizeof(char));
    }

  for (int i = 1; i < m; ++i)
    {
      for (int j = 1; j < n; ++j)
	{
	  if (*(x+i) == *(y+j))
	    {
	      c[i][j] = c[i-1][j-1] + 1;
	      *(*(b+i)+j) = 'r';
	    } else if (c[i-1][j] >= c[i][j-1])
	    {
	      c[i][j] = c[i-1][j];
	      *(*(b+i)+j) = 'u';
	    } else {
	    c[i][j] = c[i][j-1];
	    *(*(b+i)+j) = 'l';
	  }
	}
    }
  
  print_lcs(b, x, --m, --n);
}

int main(int argc, char *argv[])
{  
  char *x = NULL;
  int m = 0;
  
  cout<<"Please input X: "<<endl
      <<"enter 'e' to next."<<endl;

  while (1){
    char *c;
    
    cout<<"X["<<m<<"]: ";
    fgets(c, 100, stdin);
    if (*c == 'e')
      break;

    x = (char *)realloc(x, sizeof(char) * (++m));
    x[m] = *c;
  }

  cout<<"Please input Y: "<<endl
      <<"enter 'e' to print."<<endl;

  char *y = NULL;
  int n = 0;
  
  while (1){
    char *c;
    
    cout<<"Y["<<n<<"]: ";
    fgets(c, 100, stdin);
    if (*c == 'e')
      break;

    y = (char *)realloc(y, sizeof(char) * (++n));
    y[n] = *c;
  }

  lcs_length(x, y, ++m, ++n);

  free(x);
  free(y);
 
  return 0;
}
