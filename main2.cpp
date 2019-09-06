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


double calcCustoMin(int i, int y, int T_lim, int *d, double *P, double **C){

    double *possiveisCustos = new double[T_lim];
    int j = i-1;
    int d_plano = d[j] + y;
    int a, x;
    for (x=0; x < T_lim; x++) {

        if (d_plano < x)
            possiveisCustos[x] = inf;
        else {
            if (d_plano == x)
                possiveisCustos[x] = C[j][x];
            else {
                a = d_plano - x;
                possiveisCustos[x] = C[j][x] + a * P[j - 1]; 
            }
        }
    }


    double min = minimo(possiveisCustos, T_lim);
    delete[] possiveisCustos;
    return min;
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
    string arq = "./instancias/exemplo_lobosco02.txt";

    leitura(&D, &qtd_posto, d, P, arq);

    int T_max = 200;
    int T_init = 100;
    int T_final = 100;

    double **C = new double*[qtd_posto+1];
    int *tams = new int[qtd_posto+1];

    tams[0] = T_init + 1;
    tams[1] = T_init - d[0] + 1;
    for(int i = 0; i < 2; i++){
        C[i] = new double[T_max+1];
        for (int j = 0; j < tams[i]; j++) {
            C[i][j] = inicializacao(i, j, T_init, d[0]);
        }
    }

    int k = 0;
    for(int i = 2; i < qtd_posto + 1; i++){

        tams[i] = T_max - d[i-1] + 1;
        C[i] = new double[tams[i]];

        for(int j = 0; j < tams[i]; j++){
            C[i][j] = calcCustoMin(i, j, tams[i-1], d, P, C);
        }
    }

    bool error = false;
    for (int j = 0; j < T_max; j++){
        printf("%3d: ", j);
        for(int i = 0; i < qtd_posto+1; i++)

            if (j <= tams[i]){
                printf("%.3f \t", C[i][j]);
            } else cout << "\t\t";

        cout << endl;
    }

    cout << endl << endl << endl;

    cout << "Resposta: " << C[qtd_posto][T_final] << endl;
    
    delete[] tams;
    for (int i = 0; i < qtd_posto+1; i++) delete[] C[i];
    delete[] C;

    return 0;
}
