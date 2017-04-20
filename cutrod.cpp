#include <iostream>

using namespace std;

#define MAXWORD 100

void extened(int *r, int *s, int *p, int n){
  int q = -1;
  for (int i = 1; i < n; ++i)
    {
      q = -1;
      for (int j = 1; j < i + 1; ++j)
	{
	  if (q < *(p+j) + *(r+i-j))
	    {
	      q = *(p+j) + *(r+i-j);
	      *(s+i) = j;
	    }
	}
      *(r+i) = q;
    }
}

void printSolution(int *r, int *s, int *p, int n){
  extened(r, s, p, n);
  int temp = n;
  --n;
  
  cout<<"The best solution is: ";
  while (n>0){
    cout<<s[n]<<" ";
    n = n - s[n];
  }
  
  cout<<endl<<"script: "<<endl
      <<"n:\t";
  for (int i = 0; i < temp; ++i)
    {
      printf("%3d|", i);
    }
  
  cout<<endl<<"s:\t";
  for (int i = 0; i < temp; ++i)
    {
      printf("%3d|", s[i]);
    }
  cout<<endl;
}

int main(int argc, char *argv[])
{
  int *r = NULL;
  int *s = NULL;
  int *p = NULL;
  int n = 0;

  cout<<"Please input the price: "<<endl
      <<"enter 'p' to print."<<endl;

  while (1){
    char c[MAXWORD];

    cout<<"p["<< n << "]: ";
    fgets(c, MAXWORD, stdin);
    if (*c == 'p')
      break;

    p = (int *)realloc(p, sizeof(int) * (++n));
    p[n-1] = atoi(c);
  }

  r = (int *)malloc(sizeof(int) * n);
  s = (int *)malloc(sizeof(int) * n);
  for (int i = 0; i < n; ++i)
    {
      r[i] = 0;
      s[i] = 0;
    }

  printSolution(r, s, p, n);
  
  free(r);
  free(s);
  free(p);
  return 0;
}
