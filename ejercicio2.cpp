#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// Pablo Tomás Martínez 241532, Amar Premchand 247766

int main()
{
    int largo;
    cin >> largo;
    int *vec = new int[largo + 1];
    int ingresan;
    for (int i = 1; i < largo + 1; i++)
    {
        cin >> ingresan;
        vec[i] = ingresan;
    }
    bool cumple = true;
    int cont = 1;
    for (int i = 1; 2 * i + 1 < largo && cumple; i++)
    {
        if (vec[i] > vec[2*i] || vec[i] > vec[2*i + 1])
        {
            cumple = false;
            cont = 0;
        }
    }
    delete[] vec;
    cout << cont ;
    return 0;
}