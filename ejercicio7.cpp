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

struct _cabezalPilaInt
{
	NodoLista *top;
	int cota = 0;
};

typedef _cabezalPilaInt *PilaInt;

struct _cabezalGrafo
{
	NodoLista **g;
	int cantidadV;
	int *largos; //(largos de cada bucket)
	int compConexas;
	bool *visitados;
};

typedef _cabezalGrafo *Grafo;

PilaInt crearPilaInt()
{
	PilaInt p = new _cabezalPilaInt();
	p->top = NULL;
	p->cota = 0;
	return p;
}

//Funciones Auxiliares

bool esVacia(PilaInt p)
{
	return (p->cota == 0);
}

void push(PilaInt &p, int e)
{
	NodoLista *nuevo = NULL;
	nuevo = new NodoLista(e);
	//nuevo->dato = e;
	nuevo->sig = p->top;
	p->top = nuevo;
	p->cota++;
}

int top(PilaInt p)
{
	return p->top->dato;
}

void pop(PilaInt &p)
{
	if (esVacia(p))
	{
		delete p->top;
		delete p;
		p->cota = 0;
	}
	else
	{
		NodoLista *aBorrar = p->top;
		p->top = p->top->sig;
		delete aBorrar;
		p->cota--;
	}
}

unsigned int cantidadElementos(PilaInt p)
{
	return p->cota;
}

void destruir(PilaInt &p)
{
	NodoLista *temp;
	while (p->top != NULL)
	{
		temp = p->top;
		p->top = p->top->sig;
		p->cota--;
		delete temp;
	}
	delete p;
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
}

Grafo crear(int v)
{
	Grafo nuevo = new _cabezalGrafo;
	nuevo->g = new NodoLista *[v];
	nuevo->cantidadV = v;
	nuevo->compConexas = 0;
	nuevo->largos = new int[v];
	nuevo->visitados = new bool[v];

	for (int i = 1; i < v; i++)
	{
		nuevo->g[i] = new NodoLista();
		nuevo->largos[i] = 0;
		nuevo->visitados[i] = false;
	}
	return nuevo;
}

void DFS(PilaInt &pilita, Grafo &grafito, int i)
{

	if (!grafito->visitados[i])
	{
		grafito->visitados[i] = true;

		NodoLista *verticeAdj = grafito->g[i];
		
		for (int j = 0; j < grafito->largos[i]; j++)
		{
			if (!grafito->visitados[verticeAdj->dato])
			{
				DFS(pilita, grafito, verticeAdj->dato);
			}

			verticeAdj = verticeAdj->sig;
		}
		push(pilita, i);
	}
}

void DFS2(Grafo &grafo, int i)
{

	grafo->visitados[i] = true;

	NodoLista *verticeAdj = grafo->g[i];

	for (int j = 0; j < grafo->largos[i]; j++)
	{
		if (!grafo->visitados[verticeAdj->dato])
		{
			DFS2(grafo, verticeAdj->dato);
		}

		verticeAdj = verticeAdj->sig;
	}
}

void cantCompConexas(Grafo &grafito, PilaInt &pilita)
{
	while (!esVacia(pilita))
	{
		int tope = top(pilita);
		if (!grafito->visitados[tope])
		{
			grafito->visitados[tope] = true;
			pop(pilita);
			DFS2(grafito, tope);
			grafito->compConexas++;
		}
		else
		{
			pop(pilita);
		}
		//cantCompConexas(grafito, pilita);
	}
}

void eliminarLista(NodoLista*& l) {
	while(l != NULL) {
		NodoLista* aBorrar = l;
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

	// IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
	/*ifstream myFile("50000.in.txt");
	cin.rdbuf(myFile.rdbuf());
	// Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
	ofstream myFile2("out.txt");
	cout.rdbuf(myFile2.rdbuf());*/

	int cantV, cantA, v1, v2;
	cin >> cantV;
	cin >> cantA;
	Grafo grafo = crear(cantV + 1);
	Grafo grafoT = crear(cantV + 1);

	for (int i = 0; i < cantA; i++)
	{
		cin >> v1;
		cin >> v2;
		agregarArista(grafo->g, grafo->largos, v1, v2);
		agregarArista(grafoT->g, grafoT->largos, v2, v1);
	}

	PilaInt nuevoPila = crearPilaInt();
	for (int i = 1; i < cantV + 1; i++)
	{
		if (!grafo->visitados[i])
		{
			DFS(nuevoPila, grafo, i);
		}
	}
	cantCompConexas(grafoT, nuevoPila);

	cout << grafoT->compConexas << endl;
	destruir(nuevoPila);
	delete [] grafo->visitados;
	delete [] grafo->largos;
	delete [] grafoT->visitados;
	delete [] grafoT->largos;
	borrar(grafo);
	borrar(grafoT);
	//puede ser que esto este de mas
	delete [] grafo->g;
	delete [] grafoT->g;
	delete grafo;
	delete grafoT;
	return 0;
}
