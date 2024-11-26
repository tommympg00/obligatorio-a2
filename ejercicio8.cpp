#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Pablo Tomás Martínez 241532, Amar Premchand 247766
struct NodoLista
{
    int dato;
    NodoLista *sig;
    NodoLista() : dato(0), sig(NULL) {}
    NodoLista(int d) : dato(d), sig(NULL) {}
};

struct _cabezalGrafo
{
    NodoLista **listaAdy;
    int cantidadV;
    int *largosAdy; //(largos de cada bucket)
    NodoLista *listaPuntoQuiebre;
    //int compConexas;
    bool *visitados;
};

typedef _cabezalGrafo *Grafo;

void insertarPpio(NodoLista *&l, int dato)
{
    if (l == NULL)
    {
        l = new NodoLista(dato);
    }
    else
    {
        NodoLista *aux = l;
        l = new NodoLista(dato);
        l->sig = aux;
    }
}

void insOrd(int a, NodoLista *&l)
{

    if (l == NULL)
    {
        insertarPpio(l, a);
    }
    else
    {
        if (a <= l->dato)
        {
            insertarPpio(l, a);
        }
        else
        {
            insOrd(a, l->sig);
        }
    }
}

//struct de grafos
void agregarArista(NodoLista **&aux, int *&largos, int v, int a)
{
    //insertarPpio
    NodoLista *nuevo1 = new NodoLista();
    nuevo1->dato = a;
    nuevo1->sig = aux[v];
    aux[v] = nuevo1;
    largos[v]++;

    //hacemos para el otro lado tambien
    NodoLista *nuevo2 = new NodoLista();
    nuevo2->dato = v;
    nuevo2->sig = aux[a];
    aux[a] = nuevo2;
    largos[a]++;
}

Grafo crear(int v)
{
    Grafo nuevo = new _cabezalGrafo;
    nuevo->listaAdy = new NodoLista *[v];
    nuevo->cantidadV = v;
    nuevo->listaPuntoQuiebre = NULL;
    //nuevo->compConexas = 0;
    nuevo->largosAdy = new int[v];
    nuevo->visitados = new bool[v];

    for (int i = 1; i < v; i++)
    {
        nuevo->listaAdy[i] = NULL;
        nuevo->largosAdy[i] = 0;
        nuevo->visitados[i] = false;
    }
    return nuevo;
}

int DFS(Grafo &grafo, int i, int &cantVisitados)
{
    grafo->visitados[i] = true;
    cantVisitados++;
    
    NodoLista *verticeAdj = grafo->listaAdy[i];
    

        while(verticeAdj != NULL)
        {
            if (!grafo->visitados[verticeAdj->dato])
            {
                DFS(grafo, verticeAdj->dato, cantVisitados);
            }
            verticeAdj = verticeAdj->sig;
        }
        //grafo->visitados[i] = false;
        
    return cantVisitados;
}

void normalizarVistados(bool *visitados, int cantV)
{
    for (int j = 0; j < cantV; j++)
    {
        visitados[j] = false;
    }
}



void eliminarVertice(bool* visitados, int aBorrar)
{
    visitados[aBorrar] = true;
}

void esPuntoQuiebre(Grafo &g, int unVertice, int verticeParaDFS, NodoLista *&listaPuntoQuiebre)
{

    //"borro" el vertice poniendolo en visitado.
    eliminarVertice(g->visitados, unVertice);


    //llamar al DFS
    int cantVisitados = 1;
    bool encontre = false;
    
    cantVisitados = DFS(g, verticeParaDFS, cantVisitados);

    //comparar el contador del DFS con cantidadDeVertices - 1
    if (cantVisitados < g->cantidadV - 1) //xq al crear le pasamos CantV +1
    {
        insOrd(unVertice, listaPuntoQuiebre);
    }

    

    //resetear los visitados

}

void eliminarLista(NodoLista*& l) {
	while(l != NULL) {
		NodoLista* aBorrar = l;
		l = l->sig;
		delete aBorrar;
	}
}

int main()
{

    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    /*oifstream myFile("in.3.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());*/

    int cantV, cantA, vertice, arista;
    cin >> cantV;
    cin >> cantA;

    Grafo nuevo = crear(cantV + 1);
    for (int i = 0; i < cantA; i++)
    {
        cin >> vertice;
        cin >> arista;
        agregarArista(nuevo->listaAdy, nuevo->largosAdy, vertice, arista);
    }

    int verticeParaDFS;
    for (int i = 1; i < cantV + 1; i++)
    {
        if(i == 1){
            verticeParaDFS = i + 1;
        }
        else if( i == cantV){
            verticeParaDFS = i - 1;
        }
        else{
            verticeParaDFS = i - 1;
        }
        
        esPuntoQuiebre(nuevo, i, verticeParaDFS, nuevo->listaPuntoQuiebre);
        
        normalizarVistados(nuevo->visitados,nuevo->cantidadV);
    }

    NodoLista *rec = nuevo->listaPuntoQuiebre;
    while (rec != NULL)
    {
        cout << rec->dato << endl;
        rec = rec->sig;
    }

    //eliminamos memoria
    for(int i = 1; i < cantV + 1 ; i++){
        eliminarLista(nuevo->listaAdy[i]);
    }
    eliminarLista(nuevo->listaPuntoQuiebre);
    delete [] nuevo->visitados;
    delete [] nuevo->listaAdy;   
    delete nuevo;

    return 0;
}