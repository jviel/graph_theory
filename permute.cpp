#include <iostream>

using namespace std;

void permute( int* arr, int &sz, int &num);

int main()
{
    int sz = 5;
    int num = 5;
    int arr[5] = {1,2,3,4,5};
    permute( arr, sz, num );
}

void permute( int* arr, int &sz, int &num )
{
    if( num == 1 ){
        for( int i=0; i<sz; i++ )
            cout << arr[i] << " ";
        cout << endl;
    }   
    if( num == 2 ){
        // print full string
        for( int i=0; i<sz; i++ )
            cout << arr[i] << " ";
        cout << endl;
        // swap, print
        int temp = arr[sz-num];
        arr[sz-num] = arr[sz-num+1];
        arr[sz-num+1] = temp;
        for( int i=0; i<sz; i++ )
            cout << arr[i] << " ";
        cout << endl;
        // swap again
        temp = arr[sz-num];
        arr[sz-num] = arr[sz-num+1];
        arr[sz-num+1] = temp;
    }
    else
        permute( arr, sz, --num );

    return;
}
