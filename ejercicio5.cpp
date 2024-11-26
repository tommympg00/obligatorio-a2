#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

// Pablo Tomás Martínez 241532, Amar Premchand 247766

using namespace std;

const int INF = 99999;

struct _cabezalGrafo
{
    int **matAdj;
    int cantidad;
    //int tope;
};
typedef _cabezalGrafo *Grafo;

Grafo crear(int v)
{
    const int largo = v;
    Grafo nuevo = new _cabezalGrafo;
    nuevo->cantidad = v;
    nuevo->matAdj = new int *[v];
    //seteamos la matriz vacia;
    for (int i = 0; i < nuevo->cantidad; i++)
    {
        nuevo->matAdj[i] = new int[v];
        for (int j = 0; j < v; j++)
        {
            if (i == j)
            {
                nuevo->matAdj[i][j] = 0;
            }
            else
            {
                nuevo->matAdj[i][j] = INF;
            }
        }
    }

    return nuevo;
}

void agregarArista(Grafo &g, int vOrigen, int vDestino, int ponderacion)
{
    g->matAdj[vOrigen][vDestino] = ponderacion;
}

void Floyd(Grafo &g)
{

    for (int k = 1; k < g->cantidad; k++)
    {
        for (int i = 1; i < g->cantidad; i++)
        {
            for (int j = 1; j < g->cantidad; j++)
            {
                if (g->matAdj[i][j] > g->matAdj[i][k] + g->matAdj[k][j])
                {
                    g->matAdj[i][j] = g->matAdj[i][k] + g->matAdj[k][j];
                }
                
            }

        }
    }
}

int main()
{

    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    /*ifstream myFile("1.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());*/

    int cantV;
    int cantA;
    bool retorno = false;
    cin >> cantV;
    cin >> cantA;
    int vOrigen, vDestino, ponderacion;
    Grafo grafo = crear(cantV + 1);
    for (int i = 0; i < cantA; i++)
    {
        cin >> vOrigen;
        cin >> vDestino;
        cin >> ponderacion;
        agregarArista(grafo, vOrigen, vDestino, ponderacion);
    }
 
    Floyd(grafo);
    for (int i = 1; i < grafo->cantidad; i++)
    { //muestra matriz por pantalla

        for (int j = 1; j < grafo->cantidad; j++)
        {
            if (i == j)
            {
                cout << -1 << endl;
            }
            else
            {
                cout << grafo->matAdj[i][j] << endl;
            }
        }
    }
     for (int i = 0; i < grafo->cantidad; i++)
    {
        delete grafo->matAdj[i];
    }
    delete [] grafo->matAdj;
    delete grafo;
    return 0;
}



    /*   

    //hicimos el dijstra tambien pero demoraba mucho, dejamos la implementacion aca

    
    for (int i = 1; i < grafo->cantidad; i++)
    {

        for (int j = 1; j < grafo->cantidad; j++)
        {
            if (i == j)
            {
                cout << -1 << endl;
            }
            else
            {
                cout << dijstra(grafo, i, j) << endl;
            }
            /
        }
    }
*/




//hicimos el dijstra tambien pero demoraba mucho, dejamos la implementacion aca

/*
int posDistMinNoVisitada(Grafo g, int *dist, bool *vis)
{
    int posMin = -1, minDist = INF;
    for (int i = 1; i < g->cantidad; i++)
    {
        if (!vis[i] && dist[i] < minDist)
        {
            minDist = dist[i];
            posMin = i;
        }
    }
    return posMin;
}

int dijstra(Grafo &g, int origen, int destino)
{
    int *dist = new int[g->cantidad];
    int *ant = new int[g->cantidad];
    bool *vis = new bool[g->cantidad];

    for (int i = 0; i < g->cantidad; i++)
    {
        dist[i] = INF;
        ant[i] = -1;
        vis[i] = false;
    }
    dist[origen] = 0;

    for (int i = 1; i < g->cantidad; i++)
    {
        int posMin = posDistMinNoVisitada(g, dist, vis);

        if (posMin == -1)
        {
            return -1;
        }
        else
        {
            vis[posMin] = true;
            g->tope++;
            for (int j = 1; j < g->cantidad; j++)
            {
                if (g->matAdj[posMin][j] != -1)
                {
                    int nuevaDist = dist[posMin] + g->matAdj[posMin][j];
                    if (nuevaDist < dist[j])
                    {
                        dist[j] = nuevaDist;
                        ant[j] = posMin;
                    }
                }
            }
        }
    }
    return dist[destino];
}*/
