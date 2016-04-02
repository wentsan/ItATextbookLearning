#include <iostream>
#include <time.h>

using namespace std;


int * maxHeap(int *a, int index, int arrayLength)
{
  int left, right;
  int largest=0;
    left=2*index-1;
    right=left+1;
    if (left<=arrayLength-1 && *(a+left)>*(a+index-1))
      {
	largest=left;
	//cout<<"comparison 11: largest=\t"<<largest<<endl;
      }else{
      largest=index-1;
      //cout<<"comparison 12"<<endl;
    }
    if (right<=arrayLength-1 && *(a+right)>*(a+largest))
      {
	largest=right;
	//cout<<"comparison 13: largest=\t"<<largest<<endl;
      }
    if (largest != index-1)
      {
	int ex=0;
	ex=*(a+index-1);
	//cout<<"comparison 14: ex=\t"<<ex<<endl;
	*(a+index-1)=*(a+largest);
	//cout<<"comparison 14: *a=\t"<<*a<<endl;
	*(a+largest)=ex;
	//cout<<"comparison 14: *(a+largest)=\t"<<*(a+largest)<<endl;
	//cout<<"largest="<<largest+1<<endl;
	a=maxHeap(a, largest+1, arrayLength);
	  }
  return a;
}

void swap(int *a, int *b)
{
  int temp;
  temp=*a;
  *a=*b;
  *b=temp;
}

void printArray(int *a, int arrayLength)
{
  for (int i = 0; i < arrayLength; ++i)
    {
      cout<<"arh["<<i<<"]:\t"
	  <<*(a+i)
	  <<endl;
    }
}

int main(int argc, char *argv[])
{
  int *arh;
  const int Size=10;
  int tr[Size];
  int arrayLength = sizeof(tr)/sizeof(tr[0]);
  clock_t tstart=clock();
  clock_t tend;

  cout<<"Please input an array:"<<endl;
  for (int i = 0; i < arrayLength; ++i)
    {
      cout<<"arh["<<i<<"]:\t";
      cin>>tr[i];
    }
  arh=tr;

  for (int i = arrayLength/2; i > 0; --i)
  {
    arh=maxHeap(arh, i, arrayLength);
  }
  cout<<endl
      <<"MAXHEAP RESULT:"
      <<endl;
  printArray(arh,Size);
  
  for (int i = arrayLength-1; i >0; --i)
    {      
      swap(*arh, *(arh+i));
      arrayLength=arrayLength-1;
      arh=maxHeap(arh,1,arrayLength);
    }
  tend = clock() - tstart;
  cout<<endl
      <<"FINAL RESULT:"
      <<endl;
  printArray(arh, Size);
  cout<<"execution time:\t"<<tend<<endl;
  return 0;
}
