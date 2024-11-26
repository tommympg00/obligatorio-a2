#include "iostream"
#define INF 99999

//Amar Premchand (247766), Pablo Tomás Martínez (241532).
using namespace std;

int max(int a, int b)
{
    return a >= b ? a : b;
}

struct Archivo
{
    int megas;
    int lineas;
    int puntos;

    Archivo(int megas, int lineas, int puntos) : megas(megas), lineas(lineas), puntos(puntos) {}
};

void me_lime(int cantElementos, Archivo **arch, int limiteMegas, int limiteLineas)
{
    //inicializamos la matriz vacia
    int ***matDP = new int **[cantElementos];
    for (int i = 0; i < cantElementos; i++)
    {
        matDP[i] = new int *[limiteLineas + 1];
        for (int j = 0; j < limiteLineas + 1; j++)
        {
            matDP[i][j] = new int[limiteMegas + 1];
        }
    }
    
    for (int i = 0; i < cantElementos; i++)
    {
        for (int l = 0; l < limiteMegas + 1; l++)
        {
            matDP[i][0][l] = 0;
        }
    }

    for (int i = 0; i < cantElementos; i++)
    {
        for (int j = 0; j < limiteLineas + 1; j++)
        {
            matDP[i][j][0] = 0;
        }
    }
    

    for (int j = 0; j < limiteLineas + 1; j++)
    {
        for (int k = 0; k < limiteMegas + 1; k++)
        {
            if (arch[0]->lineas <= j && arch[0]->megas <= k)
            {
                matDP[0][j][k] = arch[0]->puntos;
            }
            else
            {
                matDP[0][j][k] = 0;
            }
        }
    }

    for (int t = 1; t < cantElementos; t++)
    {
        for (int l = 1; l < limiteLineas + 1; l++)
        {

            for (int p = 1; p < limiteMegas + 1; p++)
            {
                if (arch[t]->lineas <= l && arch[t]->megas <= p)
                {
                    matDP[t][l][p] = max(matDP[t - 1][l][p], arch[t]->puntos + matDP[t-1][l - arch[t]->lineas][p - arch[t]->megas]);
                }
                else
                {
                    matDP[t][l][p] = matDP[t - 1][l][p];
                }
            }
        }
    }
    int j = limiteLineas;
    int k = limiteMegas;
    int i = cantElementos - 1;
    cout << matDP[i][j][k];

    //Delete de la matriz
     for (int i = 0; i < cantElementos; i++)
    {
        for (int j = 0; j < limiteLineas + 1; j++)
        {
            delete [] matDP[i][j];
        }
        delete [] matDP[i];  
    }
    delete [] matDP;
    delete matDP;
}

int main()
{

    int N, S, L, t, l, p;
    cin >> N;
    Archivo **arch = new Archivo *[N];
    cin >> S;
    cin >> L;

    for (int i = 0; i < N; i++)
    {
        cin >> t;
        cin >> l;
        cin >> p;

        arch[i] = new Archivo(t, l, p);
    }
    me_lime(N, arch, S, L);
    for (int i = 0; i<N; i++){
        delete arch[i];
    }
    delete [] arch;
    return 0;
}