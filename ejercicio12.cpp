#include "iostream"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#define INF 99999

//Amar Premchand (247766), Pablo Tomás Martínez (241532).
using namespace std;

struct Archivo
{
  int megas;
  int lineas;
  int puntos;

  Archivo(int megas, int lineas, int puntos) : megas(megas), lineas(lineas), puntos(puntos) {}
};

void me_lime(int megasMax, int lineasMax, Archivo **archivos, int posActual, int cantElem, int *solActual, int *&solOptima, int puntosActual, int &puntosOptimo)
{

  if (cantElem == posActual)
  {
    if (puntosActual > puntosOptimo)
    {
      puntosOptimo = puntosActual;
      for (int i = 0; i < cantElem; i++)
      {
        solOptima[i] = solActual[i];
      }
    }
  }
  else
  {
    //No coloco a mi elemento
    me_lime(megasMax, lineasMax, archivos, posActual + 1, cantElem, solActual, solOptima, puntosActual, puntosOptimo);
    //coloco una vez a mi elemento
    if (megasMax >= archivos[posActual]->megas && lineasMax >= archivos[posActual]->lineas)
    {
      solActual[posActual]++;
      megasMax -= archivos[posActual]->megas;
      lineasMax -= archivos[posActual]->lineas;
      puntosActual += archivos[posActual]->puntos; //Esta linea era la que faltaba, Fran la tiene en la linea 38
      me_lime(megasMax, lineasMax, archivos, posActual + 1, cantElem, solActual, solOptima, puntosActual, puntosOptimo);
      solActual[posActual]--;
    }
  }
}

int main()
{
  // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
  /*ifstream myFile("10.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());*/

  int cantElementos, lineasMax, megasMax, puntosOptimo, megas, lineas, puntos;
  int *solActual, *solOptima;
  Archivo **archivos;
  cin >> cantElementos;
  cin >> megasMax;
  cin >> lineasMax;
  archivos = new Archivo *[cantElementos];
  for (int i = 0; i < cantElementos; i++)
  {
    cin >> megas;
    cin >> lineas;
    cin >> puntos;
    archivos[i] = new Archivo(megas, lineas, puntos);
  }

  solActual = new int[cantElementos];
  solOptima = new int[cantElementos];
  puntosOptimo = -INF;

  for (int i = 0; i < cantElementos; i++)
  {
    solActual[i] = 0;
    solOptima[i] = 0;
  }

  int posActual = 0;
  int puntosActual = 0;

  me_lime(megasMax, lineasMax, archivos, posActual, cantElementos, solActual, solOptima, puntosActual, puntosOptimo);

  cout << puntosOptimo << endl;

  for (int i = 0; i < cantElementos; delete archivos[i++])
    ;
  delete[] archivos;

  delete[] solActual;
  delete[] solOptima;
  return 0;
}