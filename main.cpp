#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#define N 20000
#define M 5

using namespace std;

typedef struct {
    int id;
    int horas;
    bool reparacion;
} Componentes;

void simular1(float **);
void simular2(float **);

int main() {

    ifstream archivo("Tabla1.txt");

    float **tabla = (float **) malloc(N * sizeof(float *));

    for (int i = 0; i < N; ++i) {
        tabla[i] = (float *) malloc(M * sizeof(float));
    }

    int i = 0;
    int k;
    string linea, temp;

    if (archivo.is_open()) {
        while ( getline(archivo, linea) ) {
            temp = "";
            k = 0;
            for (int j = 0; j < linea.length(); ++j) {
                if (linea.at(j) != '\t'){
                    temp += linea.at(j);
                } else if(temp != ""){
                    tabla[i][k] = atof(temp.c_str());
                    k++;
                    temp = "";
                }
            }

            tabla[i][k] = atof(temp.c_str());

            i++;
        }

        archivo.close();
        simular1(tabla);
        simular2(tabla);
    }
    archivo.close();
    free(tabla);
    return 0;
}

void simular1(float **tabla) {

    Componentes comp[M - 1];

    for (int i = 0; i < M - 1; ++i) {
        comp[i].id = i + 1;
        comp[i].horas = 0;
        comp[i].reparacion = false;
    }

    float **t = tabla;
    int gasto = 0;

    for (int i = 0; i < N; ++i) {

        bool falla = false;

        for (int j = 0; j < M - 1; ++j) {
            if ((*t)[j + 1] <= comp[j].horas) {
                falla = true;
         /*       cout <<  "El componenete " << comp[j].id << " presenta falla en la hora " << i <<
                        ", se restablecera las horas de todos los componentes dado que se van a remplazar\n";
         */      break;
            }
        }

        if (!falla) {
            for (int j = 0; j < M - 1; ++j) {
                comp[j].horas++;
            }

         //   cout << "No se presento ninguna falla en la hora " << i << endl;
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

void simular2(float **tabla){

    Componentes comp[M - 1];

    for (int i = 0; i < M - 1; ++i) {
        comp[i].id = i + 1;
        comp[i].horas = 0;
        comp[i].reparacion = false;
    }

    float **t = tabla;
    int gasto = 0;
    int fallas[M - 1] = {0, 0, 0, 0};

    for (int i = 0; i < N; ++i) {

        bool falla = false;

        for (int j = 0; j < M - 1; ++j) {
            if (t[fallas[j]][j + 1] <= comp[j].horas) {
                falla = true;
  /*              cout <<  "El componenete " << comp[j].id << " presenta falla en la hora " << i <<
                ", se restablecera las horas de todos los componentes dado que se van a remplazar\n";
    */            comp[j].reparacion = true;
            }
        }

        if (!falla) {
            for (int j = 0; j < M - 1; ++j) {
                comp[j].horas++;
            }

      //      cout << "No se presento ninguna falla en la hora " << i << endl;
        } else {
            gasto += 300;
            for (int j = 0; j < M - 1; ++j) {
                if(comp[j].reparacion) {
                    comp[j].horas = 0;
                    fallas[j]++;
                    comp[j].reparacion = false;
                }
            }
            i++;
        }
    }

    cout << "\nEl costo total por la politica de rempalazar solo un "
            "componente fallido, generaria un costo de:" << gasto << endl << endl;
}