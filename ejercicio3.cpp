#include <iostream>

using namespace std;

// Pablo Tomás Martínez 241532, Amar Premchand 247766

struct NodoListaString
{
    string palabra;
    
    int cantidadOcurrencias;
    NodoListaString *sig;
    NodoListaString() : palabra(""), cantidadOcurrencias(0), sig(NULL) {}
    NodoListaString(string p, int cant) : palabra(p), cantidadOcurrencias(cant), sig(NULL) {}
};

struct _cabezalPalabra
{
    NodoListaString **p;
    int cantidadDoble;
    int largo;
};

typedef _cabezalPalabra *Palabras;

int siguienteNumPrimo(int num)
{

    bool a = true;
    for (int i = 2; i < 10 && a; i++)
    {
        if (num != i && num % i == 0)
        {
            a = false;
        }
    }
    if (!a)
    {
        return siguienteNumPrimo(num + 1);
    }
    else
    {
        return num;
    }
}



int funcionHash(string palabra, int largoArray)
{
    int hash = 0;
    for (int i = 0; i < palabra.length(); i++)
    {
        hash = (31 * hash) + int(palabra[i]);
    }
    return hash % largoArray;
}

Palabras Crear(int largoArray)
{
    Palabras nuevo = new _cabezalPalabra;
    nuevo->p = new NodoListaString *[largoArray];
    nuevo->cantidadDoble = 0;
    nuevo->largo = largoArray;
    for (int i = 0; i < largoArray; i++)
    {
        nuevo->p[i] = NULL;
    }
    return nuevo;
}

//PRE: Recibe NodoListaString*& l, String i, int ocurrencias, int& cantidad
//POS: Agrega a "i" en "l" "ocurrencias" veces, haciendo que "cantidad" aumente "ocurrencias" veces.
void agregar(NodoListaString*& l, string i, int ocurrencias, int& cantidad) {
	
	if (l == NULL) {
		l = new NodoListaString(i, ocurrencias);
	}

	else if (l->palabra == i) {
		l->cantidadOcurrencias = l->cantidadOcurrencias + ocurrencias;
		
        if(l->cantidadOcurrencias == 2) {
        cantidad ++;
        }
        if(l->cantidadOcurrencias == 3){
            cantidad --;
        }

	}
	
	if (l->palabra != i) {
		agregar(l->sig, i, ocurrencias, cantidad);
	}
	
}
void eliminarLista(NodoListaString*& l) {
	while(l != NULL) {
		NodoListaString* aBorrar = l;
		l = l->sig;
		delete aBorrar;
	}
}

void borrar(Palabras &aBorrar){
    int i = 0;
	while (i < aBorrar->largo) {
		eliminarLista (aBorrar->p[i]);
		i++;
	}

}

int main()
{
    int l;
    cin >> l;
    int largo = siguienteNumPrimo(l);
    Palabras nuevo = Crear(largo);

    for(int i = 0; i<largo; i++){
        string aInsertar;
        cin >> aInsertar;
        int pos = funcionHash(aInsertar,largo);
        agregar(nuevo->p[pos], aInsertar,1,nuevo->cantidadDoble);
    }
     cout << nuevo->cantidadDoble;
    borrar(nuevo);
    delete [] nuevo->p;
    delete nuevo;
    return 0;
}
                                                                                                                                                                         