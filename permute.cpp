/* THIS PROGRAM IS AN EXPERIMENT FOR RECURSIVELY PERMUTING A SEQUENCE OF NUMBERS
 * OF ANY LENGTH. # OF PERMUTATIONS IS N! WHERE N IS THE NUMBER OF ELEMENTS
 * written by Johnny Viel 3.20.16
 *******************************************************************************/
 
#include <iostream>

using namespace std;

void permute( int* arr, const int &sz, int num);
void printarr( int*& arr, const int &sz );
void swapCols( int*& arr, const int &sz, int num );

int main()
{
    const int sz     = 5;
    int       num    = 5;
    int       arr[5] = {1,2,3,4,5};

    permute( arr, sz, num );
    
    return 0;
}

void permute( int * arr, const int &sz, int num )
{
    if( num == 1 )
        printarr( arr, sz );

    for( int i=0; i<num; i++ )
    {
        permute( arr, sz, (num-1) );
        swapCols( arr, sz, num );
    }

    return;
}

void printarr( int*& arr, const int &sz )
{
    for( int i=0; i<sz; i++ )
        cout << arr[i] << " ";
    cout << endl;
}

void swapCols( int *& arr, const int &sz, int num )
{
        int pivot = sz-num;
        int temp  = arr[pivot];
     // shift one-by-one to the left
        for( int j=pivot; j<sz-1; j++ )
            arr[j] = arr[j+1]; 
        arr[sz-1] = temp;         // set last as first
}
