#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ativa(float val){
    if(val > 0){
        return 1;
    }
    return 0;
}

float atualiza_peso(float peso, float tx, float dif ,int val){
    float aux;
        aux = peso + tx*(dif)*val;
        //printf("Peso atualizado %f\n", aux);
        return aux;
}


void perceptron(int col, int lin,float amostras[][col], int epoc, float tx, float saidas[], float peso[]){

    float somador = 0 , res, dif;
    int cont = 0;
    while(cont <  epoc){
        for(int i=0; i<lin; i++){
            for(int j=0; j<col; j++){
                somador = somador + (peso[j]*amostras[i][j]);
            }

            //printf("Não ativada %f\n", somador);
            res = ativa(somador);
            //printf("Ativada %f\n", res);
            //printf("Saída [%f]\n", saidas[i]);
            if(res != saidas[i]){
                dif = saidas[i] - res;
                for(int j=0; j<col; j++){
                    peso[j] = atualiza_peso(peso[j],tx, dif, amostras[i][j]);
                }
            }
            somador=0;
        }
        cont++;
    }
}

int main(int argc, char const *argv[]) {


    float u=0;
    int y;
    float amostras[][3] = {
                            {1, 0, 0}, {1, 0, 1},

                            {1, 1, 0}, {1, 1, 1}
                        };
    float saidas[] = {0,0,0,1};


    // float amostras[][3] = {
    //                         {1, 0.0, 0.45}, {1, 0.3, 0.5},
    //                         {1, 0.0, 0.6}, {1, 0.2, 0.7}
    //                     };
    // float saidas[] = {1.0, 1.0, 0.0, 0.0};

    // float amostras[][3] = {{0.1, 0.4, 0.7}, {0.3, 0.7, 0.2},
    //                 {0.6, 0.9, 0.8}, {0.5, 0.7, 0.1}};
    //
    // float saidas[] ={1, -1, -1, 1};
    float peso_treino[3];

    memset(peso_treino, 0, sizeof(peso_treino));

    for(int i=0; i<3;i++){
        printf("%f\n", peso_treino[i]);
    }

    perceptron(3, 6,amostras, 10, 0.25, saidas, peso_treino);


    for(int i=0; i< 3;i++){
        printf("%f\n", peso_treino[i]);
    }


    float entrada[3];
    //memset(entrada, 0, sizeof(entrada));
    printf("Digite o valor\n");
    for(int i=0; i < 3; i++){
        scanf("%f", &entrada[i]);
    }

    u = 0;
    for(int cont = 0; cont < 3; cont++){
        u = u + peso_treino[cont]*entrada[cont];
        printf("valor de u+w{%d}*x{%d} {%f}\n",cont,cont ,u);
    }
    printf("valor de u %f\n", u);
    y = ativa(u);
    printf("saída da função {%d}\n", y);
    y == 1 ? printf("Classe A\n") : printf("Classe B\n");
    u=0;

    //
    // for(int i=0; i<=6; i++){
    //     for(int j=0; j<3; j++){
    //         u = u + peso_treino[j]*amostras[i][j];
    //         printf("valor de u+w{%d}*x{%d} {%f}\n",j,j ,u);
    //     }
    //     printf("valor de u %f\n", u);
    //     y = ativa(u);
    //     printf("saída da função {%d}\n", y);
    //
    //     y == 1 ? printf("Classe A\n") : printf("Classe B\n");
    //     u=0;
    // }
    //


    return 0;
}
