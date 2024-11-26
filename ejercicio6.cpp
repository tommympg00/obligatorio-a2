#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Pablo Tomás Martínez 241532, Amar Premchand 247766

//struct de cola

struct NodoLista
{
    int dato;
    NodoLista *sig;
    NodoLista() : dato(0), sig(NULL) {}
    NodoLista(int d) : dato(d), sig(NULL) {}
};

struct _cabezalColaInt
{
    NodoLista *primero, *ultimo;
};

struct _cabezalGrafo
{
    NodoLista **g;
    int cantidadV;
    int *largos;  //(largos de cada bucket)
    int *estados; //(-1 si no tiene, 0 y 1)
    bool *visitados;
};


typedef _cabezalColaInt *ColaInt;

ColaInt crearColaInt()
{
    _cabezalColaInt *c = new _cabezalColaInt;
    c->primero = NULL;
    c->ultimo = NULL;
    return c;
}

void encolar(ColaInt &c, int e)
{
    NodoLista *nuevo = new NodoLista;
    nuevo->dato = e;
    nuevo->sig = NULL;
    if (c->primero == NULL)
    {
        c->primero = nuevo;
        c->ultimo = nuevo;
    }
    else
    {
        c->ultimo->sig = nuevo;
        c->ultimo = nuevo;
    }
}

bool esVacia(ColaInt c)
{
    return c->primero == NULL;
}

int principio(ColaInt c)
{
    if (!esVacia(c))
    {
        return c->primero->dato;
    }
    else
    {
        return -1;
    }
}

void desencolar(ColaInt &c)
{
    if (c->primero != NULL)
    {
        NodoLista *temp = c->primero;
        c->primero = c->primero->sig;
        if (c->primero == NULL)
        {
            c->ultimo = NULL;
        }
        delete temp;
    }
}

unsigned int cantidadElementos(ColaInt c)
{
    int cont = 0;
    NodoLista *recorredor = c->primero;
    while (recorredor != NULL)
    {
        cont++;
        recorredor = recorredor->sig;
    }
    return cont;
}

ColaInt clon(ColaInt c)
{
    ColaInt copia = crearColaInt();
    NodoLista *recorredor = c->primero;
    while (recorredor != NULL)
    {
        encolar(copia, recorredor->dato);
        recorredor = recorredor->sig;
    }
    delete recorredor;
    return copia;
}

void destruir(ColaInt &c)
{
    NodoLista *temp;
    while (c->primero != NULL)
    {
        temp = c->primero;
        c->primero = c->primero->sig;
        delete temp;
    }
    delete c;
}

//struct de grafos

typedef _cabezalGrafo *Grafo;

Grafo Crear(int v)
{
    Grafo nuevo = new _cabezalGrafo;
    nuevo->g = new NodoLista *[v];
    nuevo->cantidadV = v;
    nuevo->largos = new int[v];
    nuevo->estados = new int[v];
    nuevo->visitados = new bool[v];

    for (int i = 1; i < v; i++)
    {
        nuevo->g[i] = new NodoLista();
        nuevo->largos[i] = 0;
        nuevo->estados[i] = -1;
        nuevo->visitados[i] = false;
    }
    return nuevo;
}

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

bool esBipartito(Grafo &grafo, int pos, ColaInt &colita)
{
   
    bool cumple = true;

    
        if (grafo->estados[pos] == -1)
        {
            grafo->estados[pos] = 0; // el .1 es white, el 0 es red, el 1 es green
            encolar(colita, pos);

            while (!esVacia(colita) && cumple)
            {
                int primero = principio(colita);
                desencolar(colita);
				grafo->visitados[primero] = true;
				NodoLista* aux = grafo->g[primero];

                for (int j = 0; j < grafo->largos[primero] && cumple; j++)
                {
                    //nos fijamos todos los vertices adyacentes a primero
                    int vecino = aux->dato;
                    if (grafo->estados[vecino] == -1)
                    {
                        grafo->estados[vecino] = 1 - grafo->estados[primero];
						encolar(colita, vecino);
                    }
                    if (grafo->estados[vecino] == grafo->estados[primero])
                    {
                        cumple = false;
                    }
					aux = aux->sig;
					

                    
                }
            }
            //aca probamos que el grafo sea conexo

        }
    
    return cumple;
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
   /*
	// IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
  ifstream myFile("3.in.txt");
  cin.rdbuf(myFile.rdbuf());
  // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
  ofstream myFile2("out.txt");
  cout.rdbuf(myFile2.rdbuf());
  */

    int cantV, cantA, v1, v2;
    cin >> cantV;
    cin >> cantA;
    Grafo grafo = Crear(cantV + 1);
    for (int i = 0; i < cantA; i++)
    {
        cin >> v1;
        cin >> v2;
        agregarArista(grafo->g, grafo->largos, v1, v2);
    }
    ColaInt c = crearColaInt();
    bool cumple = true;
    for(int i = 1; i < cantV + 1 && cumple; i++){
        if(grafo->visitados[i] == false){
            cumple = esBipartito(grafo,i, c);
        }
    }
    
    if (cumple)
    {
        cout << 1;
    }
    else
    {
        cout << 0;
    }
    
    destruir(c);
    borrar(grafo);
    delete [] grafo->g;
    delete [] grafo->estados;
    delete [] grafo->largos;
    delete [] grafo->visitados;
    delete grafo;
    
    return 0;
}