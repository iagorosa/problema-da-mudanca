#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>
#include <fstream>

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
    int a, x;
    for (x=0; x < T_max+1; x++) {

        if (d_plano > T_max ) {
            possiveisCustos[x] = inf;
        }
        else {
            if (d_plano < x)
                possiveisCustos[x] = inf;
            else {
                if (d_plano + y == x)
                    possiveisCustos[x] = C[x][j];
                else {
                    a = d_plano - x;
                    possiveisCustos[x] = C[x][j] + a * P[j - 1]; //Ficar atento parametro P
                }
            }
        }
    }


    return minimo(possiveisCustos, x-1);
}



void leitura(int *D, int *qtd_posto, int *(&d), double *(&P), const string arq_name){
    ifstream entrada;
    entrada.open(arq_name, ios::in);

    if(!entrada) cout << "Arquivo nao encontrado!" << endl;

    entrada >> *D;
    entrada >> *qtd_posto;

    P = new double[*qtd_posto];
    d = new int[*qtd_posto];

    double preco;
    int dist;
    int dist_acum=0;

    for (int i = 0; i < *qtd_posto; i++) {
        entrada >> dist >> preco;
        d[i] = dist - dist_acum;
        P[i] = preco;
        dist_acum += d[i];
    }
}



int main() {

    int D, qtd_posto;
    int *d;
    double *P;
    string arq = "./instancias/exemplo_medina01.txt";

    leitura(&D, &qtd_posto, d, P, arq);

    int T_max = 200;
    int T_init = 100;
    int T_final = 100;

    double **C = new double*[T_max+1];
    for (int i = 0; i < T_max+1; ++i) {
        C[i] = new double[qtd_posto+1];
    }

    for(int i = 0; i < 2; i++){
        for (int j = 0; j < T_max+1; j++) {
            C[j][i] = inicializacao(i, j, T_init, d[0]);
        }
    }

    bool pause;
    int k = 0;
    for(int i = 2; i < qtd_posto + 1; i++){
        pause = false;

        for(int j = 0; j < T_max+1; j++){
            C[j][i] = calcCustoMin(i, j, T_max, d, P, C);
        }
    }

    for (int j = 0; j < T_max; j++){
        printf("%3d: ", j);
        for(int i = 0; i < qtd_posto+1; i++){
            printf("%.3f \t", C[j][i]);
        }
        cout << endl;
    }

    cout << endl << endl;

    cout << "Resposta: " << C[T_final][qtd_posto] << endl;

    return 0;
}
