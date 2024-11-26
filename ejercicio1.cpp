#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Pablo Tomás Martínez 241532, Amar Premchand 247766
struct NodoListaInt
{
    int dato;
    NodoListaInt *sig;
    NodoListaInt() : dato(0), sig(NULL) {}
    NodoListaInt(int d) : dato(d), sig(NULL) {}
};

struct _cabezalHeap
{
    NodoListaInt **heap;
    int tope;
};

typedef _cabezalHeap *Heap;

void flotar(NodoListaInt **&vector, int pos)
{
    if (pos <= 1)
    {
        return;
    }

    else
    {
        NodoListaInt *flota = vector[pos];
        NodoListaInt *padre = vector[pos / 2];
        NodoListaInt *aux;
        if (flota->dato < padre->dato)
        {
            aux = flota;
            vector[pos] = padre;
            vector[pos / 2] = aux;
            flotar(vector, pos / 2);
        }
    }
}

void hundir(NodoListaInt **&vector, int pos, int tope)
{
    NodoListaInt *aux;

    int padre = pos;
    int hijoI = 2 * pos;
    int hijoD = 2 * pos + 1;
    if (hijoI <= tope && vector[padre]->dato > vector[hijoI]->dato)
    {
        padre = hijoI;
    }
    if (hijoD <= tope && vector[padre]->dato > vector[hijoD]->dato)
    {
        padre = hijoD;
    }
    if (padre != pos)
    {
        aux = vector[pos];
        vector[pos] = vector[padre];
        vector[padre] = aux;

        hundir(vector, padre, tope);
    }
}

void borrarMin(Heap &h)
{
    if (h->heap[1] != NULL)
    {
        NodoListaInt *borro = h->heap[1];
        h->heap[1] = h->heap[1]->sig;
        delete borro;
        if (h->heap[1] == NULL) //va a ser NULL, hago esto para meter el ultimo en su lugar
        {

            h->heap[1] = h->heap[h->tope];
            h->heap[h->tope] = NULL;
            h->tope = h->tope - 1;
            hundir(h->heap, 1, h->tope);
        }
    }
}

/*void borrar(Heap &h, int pos)
{
    if (h->heap[pos] != NULL)
    {

        h->heap[pos]->dato = h->heap[h->tope]->dato;
        h->heap[h->tope] = NULL;
        h->tope = h->tope - 1;

        hundir(h->heap, pos, h->tope);
        flotar(h->heap, pos);
    }
}*/

void insertar(Heap &h, NodoListaInt *lista)
{
    if (lista == NULL)
    {
        return;
    }

    else if (lista != NULL)
    {

        h->heap[h->tope + 1] = lista; // el siguiente lugar va a ser igual a la cantidad que tengo +1
        h->tope++;
        flotar(h->heap, h->tope);
    }
}

Heap crear(int length)
{
    Heap nuevo = new _cabezalHeap;
    nuevo->heap = new NodoListaInt *[length + 1]; //ignoramos la posicion 0
    nuevo->tope = 0;

    for (int i = 0; i < length + 1; i++)
    {
        nuevo->heap[i] = NULL;
    }
    return nuevo;

} // retorna heap vacío

int minimo(Heap h)
{
    if (h->tope > 0)
    {
        return h->heap[1]->dato;
    }

    else
    {
        return 0;
    }
}

int main()
{
    
    int largo;
    cin >> largo;

    Heap nuevo = crear(largo + 1);

    //agrega los elementos al heap
    for (int i = 1; i < largo + 1; i++)
    {
        NodoListaInt *AInsertar = new NodoListaInt();
        cin >> AInsertar->dato;
        insertar(nuevo, AInsertar);
    }

    for (int i = 1; i < largo + 1; i++)
    {

        cout << minimo(nuevo) << endl;
        borrarMin(nuevo);
    }
    delete [] nuevo->heap;
    delete nuevo;
    return 0;
}
