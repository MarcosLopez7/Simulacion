#include <iostream>
#include <fstream>
#include <cstdlib>

#define N 20000
#define M 5

using namespace std;

typedef struct {
    int id;
    int horas;
    bool reparacion;
} Componentes;

void simular(int **);

int main() {

    ifstream archivo("Tabla1.txt");
    int **tabla = (int **) malloc(N * sizeof(int *));

    for (int i = 0; i < N; ++i) {
        tabla[i] = (int *) malloc(M * sizeof(int));
    }

    int i = 0;

    while (archivo >> tabla[i][0] >> tabla[i][1] >> tabla[i][2] >> tabla[i][3] >> tabla[i][4]) {
        i++;
    }

    simular(tabla);

    free(tabla);
    return 0;
}

void simular(int **tabla) {

    Componentes comp[M - 1];

    for (int i = 0; i < M - 1; ++i) {
        comp[i].id = i + 1;
        comp[i].horas = 0;
        comp[i].reparacion = false;
    }

    int **t = tabla;
    int gasto = 0;

    for (int i = 0; i < N; ++i) {

        bool falla = false;

        for (int j = 0; j < M - 1; ++j) {
            if ((*t)[j + 1] >= comp[j].horas) {
                falla = true;
                cout <<  "El componenete " << comp[j].id << " presenta falla en la hora " << i <<
                        ", se restablecera las horas de todos los componentes dado que se van a remplazar\n";
                break;
            }
        }

        if (!falla) {
            for (int j = 0; j < M - 1; ++j) {
                comp[j].horas++;
            }

            cout << "No se presento ninguna falla en la hora " << i << endl;
        } else {
            gasto += 1000;
            for (int j = 0; j < M - 1; ++j) {
                comp[j].horas = 0;
            }
            i += 2;
            t++;
        }

    }

    cout << "\nEl costo total por la politica de rempalazar todos los "
                    "componentes por uno fallido, generaria un costo de:" << gasto << endl << endl;

}