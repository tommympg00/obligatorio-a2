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

struct _cabezalGrafo
{
	NodoListaInt **g;
	int cantidadV;
	int *largos; //(largos de cada bucket)
};

typedef _cabezalGrafo *Grafo;

Grafo Crear(int v)
{
	Grafo nuevo = new _cabezalGrafo;
	nuevo->g = new NodoListaInt *[v];
	nuevo->cantidadV = v;
	nuevo->largos = new int[v];

	for (int i = 1; i < v; i++)
	{
		nuevo->g[i] = new NodoListaInt();
		nuevo->largos[i] = 0;
	}
	return nuevo;
}

void agregarArista(NodoListaInt **&aux, int *&largos, int v, int a)
{
	//insertarPpio
	NodoListaInt *nuevo = new NodoListaInt();
	nuevo->dato = a;
	nuevo->sig = aux[v];
	aux[v] = nuevo;
	largos[v]++;
}

bool esCiclo(Grafo &graph, int v, bool *&visitados, bool *&enPila, int cantidadV)
{
	if (!visitados[v])
	{
		visitados[v] = true;
		enPila[v] = true;

		if (graph->largos[v] != 0)
		{
			for (int i = 0; i < graph->largos[v]; i++)
			{
				if (!visitados[graph->g[v]->dato] && esCiclo(graph, graph->g[v]->dato, visitados, enPila, cantidadV))
				{
					return true;
				}
				else if (enPila[graph->g[v]->dato])
				{
					return true;
				}
				graph->g[v] = graph->g[v]->sig;
			}
		}
	}

	enPila[v] = false;
	return false;
}

void eliminarLista(NodoListaInt*& l) {
	while(l != NULL) {
		NodoListaInt* aBorrar = l;
		l = l->sig;
		delete aBorrar;
	}
}

void borrar(Grafo &aBorrar){
    int i = 1;
	while (i < aBorrar->cantidadV) {
		eliminarLista (aBorrar->g[i]);
		i++;
	}
}

int main()
{
	
	int cantV;
	int cantA;
	bool retorno = false;
	cin >> cantV;
	cin >> cantA;
	int v, a;
	Grafo grafo = Crear(cantV + 1);
	for (int i = 0; i < cantA; i++)
	{
		cin >> v;
		cin >> a;
		agregarArista(grafo->g, grafo->largos, v, a);
	}
	bool ciclo = false;
	bool *visitado = new bool[cantV + 1];
	bool *enPila = new bool[cantV + 1];
	for (int i = 1; i < cantV + 1; i++)
	{
		visitado[i] = false;
		enPila[i] = false;
	}
	for (int v = 1; v < cantV + 1 && !ciclo; v++)
	{
		if (esCiclo(grafo, v, visitado, enPila, grafo->cantidadV))
		{
			ciclo = true;
		}
	}
	if (ciclo)
	{
		cout << 1;
	}
	else
	{
		cout << 0;
	}
	delete [] grafo->largos;
	borrar(grafo);
	delete [] grafo->g;
	delete grafo;
	delete [] visitado; 
	delete [] enPila;
	
	
	return 0;
}