#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

double inf = std::numeric_limits<double>::infinity();

double minimo(double *pC, int T_max){
    double menor = inf;
    for (int i = 0; i < T_max; i++){
        if (pC[i] < menor)
            menor = pC[i];
    }
    return menor;
}

float inicializacao(int i, int j, int T_init, int d_init){

    if (i == 0) {
        if (j == T_init)
            return 0.0;
        else
            return (float)inf;
    }
    else{
        if (d_init > T_init) {
            printf(("Impossivel!!!!"));
            exit(1);
        }
        else {
            if (j == T_init-d_init)
                return 0;
            else
                return (float)inf;
        }
    }
}

double calcCustoMin(int i, int y, int T_max, int *d, double *P, double **C){

    double *possiveisCustos = new double[T_max+1];
    int j = i-1;
    int d_plano = d[j] + y;
    int a;
    if (y == 0)
        cout << "P[" << j-1 <<"]: " << P[j-1] << endl;
    for (int x = 0; x < T_max+1; x++) {

        if (d_plano < x || d_plano > T_max)
            possiveisCustos[x] = inf;
        else {
            if (d_plano + y == x)
                possiveisCustos[x] = C[x][j];
            else {
                a = d_plano - x;
                possiveisCustos[x] = C[x][j] + a * P[j-1]; //Ficar atento parametro P
            }
        }
    }

    return minimo(possiveisCustos, T_max);
}

int main() {

/////////////// EXEMPLO MEDINA ////////////////////
//    const int D = 280;
//    const int qtd_posto = 5;
//    int d[qtd_posto+1]    = {10,   60,   100,  30,    50,    100};
//    double P[qtd_posto+1] = {10.0, 50.0, 10.0, 50.0, 100.0, inf};
//////////////////////////////////////////////////

/////////////// EXEMPLO LOBOSCO /////////////////
//    const int D = 500;
//    const int qtd_posto = 7;
//    int d[qtd_posto+1] =    {100,    50,    50,   100,   100,    50,     50,  100};
//    double P[qtd_posto+1] = {3.99, 3.888, 3.777, 3.999, 4.199, 4.119, 4.1399, inf};
////////////////////////////////////////////////

/////////////// EXEMPLO LOBOSCO 2 /////////////////
    const int D = 500;
    const int qtd_posto = 7;
    int d[qtd_posto+1] =    {  100,    50,    50,   100,   100,    50,     50,  100};
    double P[qtd_posto+1] = {0.999, 0.888, 0.777, 0.999, 1.009, 1.019,  1.399, inf};
//////////////////////////////////////////////////

    int T_max = 200;
    int T_init = 100;

//    double C[D][qtd_posto + 2];
    double **C = new double*[T_max+1];
    for (int i = 0; i < T_max+1; ++i) {
        C[i] = new double[qtd_posto+2];
    }

    for(int i = 0; i < 2; i++){
        for (int j = 0; j < T_max+1; j++) {
            C[j][i] = inicializacao(i, j, T_init, d[0]);
        }
    }

    for(int i = 2; i < qtd_posto + 2; i++){
        for(int j = 0; j < T_max+1; j++){
            C[j][i] = calcCustoMin(i, j, T_max, d, P, C);
        }
    }

    for (int j = 0; j < T_max; j++){
        printf("%3d: ", j);
        for(int i = 0; i < qtd_posto+2; i++){
//            printf("%10.5lf \t", C[j][i]);
            printf("%.3f \t", C[j][i]);
        }    float* x = new float[5];
    float* x_next = new float[5];
        cout << endl;
    }



    return 0;
}