#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// 0  1  2  3  4  5  6   7  8  9  10  11  12  13
//[2, 2, 5, 5, 7, 7, 10, 10, 11, 14, 14, 16, 16]

int encontrarSoltero(int *arr, int pos, int largo)
{
    if (arr[pos - 1] < arr[pos] && arr[pos + 1] > arr[pos])
    {
        return arr[pos];
    }
    else if(arr[0] != arr[1]){
        return arr[0];
    }
    else if(arr[largo-1] != arr[largo-2]){
        return arr[largo-1];
    }
    else if(arr[pos] == arr[pos+1]){
        pos = (pos+1+largo)/2;
        encontrarSoltero(arr,pos,largo);
    }
    else if(arr[pos] == arr[pos-1]){
        pos = (pos-1)/2;
        encontrarSoltero(arr,pos,largo);
    }
}

int main()
{
    
    int largo;
    int entrada;
    cin >> largo;
    int *arr = new int[largo];
    for (int i = 0; i < largo; i++)
    {
        cin >> entrada;
        arr[i] = entrada;
    }

    int pos = (largo - 1) / 2;
    
    int numSolo = encontrarSoltero(arr, pos,largo);
    cout << numSolo;
    delete [] arr;
    return 0;
}