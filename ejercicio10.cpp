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
        // borro = NULL;
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

int Aeropuerto(Heap &entrada, Heap &salida, int max, int cant)
{
    while (minimo(entrada) != 0 && minimo(salida) != 0)
    {

        if (minimo(entrada) == 0)
        {
            if (cant > 0)
            {
                cant = cant - 1;
            }
            borrarMin(salida);
        }
        else if (minimo(salida) == 0)
        {
            cant = cant + 1;
            if (cant > max)
            {
                max = cant;
            }
            borrarMin(entrada);
        }
        else if (minimo(entrada) < minimo(salida))
        {
            cant = cant + 1;
            if (cant > max)
            {
                max = cant;
            }
            borrarMin(entrada);
        }
        else if (minimo(entrada) > minimo(salida))
        {
            if (cant > 0)
            {
                cant = cant - 1;
            }
            borrarMin(salida);
        }
        else if (minimo(entrada) == minimo(salida))
        {
            borrarMin(entrada);
            borrarMin(salida);
        }
    }
    while (minimo(salida) != 0) {
     borrarMin(salida);
    }
    return max;
}

int main()
{
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    /*ifstream myFile("100000.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());*/

    int largo;
    cin >> largo;
    int cant = 0;
    int max = 0;
    Heap entrada = crear(largo + 1);
    Heap salida = crear(largo + 1);
    int e, s;
    for (int i = 1; i < largo + 1; i++)
    {
        cin >> e;
        cin >> s;
        NodoListaInt *en = new NodoListaInt(e);
        NodoListaInt *sa = new NodoListaInt(s);
        insertar(entrada, en);
        insertar(salida, sa);
    }

    int retorno = Aeropuerto(entrada, salida, cant, max);
    cout << retorno;

    delete[] entrada->heap;
    delete entrada;
    delete[] salida->heap;
    delete salida;
    return 0;
}