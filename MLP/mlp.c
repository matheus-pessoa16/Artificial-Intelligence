#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

float sigmoide(float x);
float df_sigmoide(float x);
void print(float val[], int len);
float mean(float x, int tam);


float error_mean = 0;
int tam_amostra;


int main(){

	srand(time(NULL));

	float w_h [2][3] = {{0.1, 0.2, 0.8} , {0.2, 0.1, 0.5}};

	float w_o[3] = {0.2, 0.1, 0.5};

	float entrada[4][3] = {	{-1, 0, 0}, {-1, 0, 1},
							{-1, 1, 0},{-1, 1, 1}	};

	tam_amostra = 4;

	float saidas_desejadas[] = {0, 1, 1, 0};

	float saida_camada_oculta[2];
	memset(saida_camada_oculta,0, sizeof(saida_camada_oculta));

	float input_camada_saida[3];
	memset(input_camada_saida,0, sizeof(input_camada_saida));


	float saida_ativada[2];
	memset(saida_ativada,0, sizeof(saida_ativada));

	float erro;
	float delta_camada_saida = 0;
	float learning_rate = 0.8;

	float saida_oculta_bias[] = {-1,0,0};

	float delta_camada_oculta[2];

	float resposta_rede = 0;

	float mse = 1, erro_ant, erro_m_atual;

	int cont=0, indice_aleatorio;

	float aux = 0;

	do{
		for(int i=0; i<4; i++){
				indice_aleatorio = valor_aleatorio();

				printf("Amostra da vez %d\n", indice_aleatorio);

				erro_ant = mse;
				//******************************************************//
				//				INÍCIO DA FASE DE FORWARD				//
				//******************************************************//

				for(int i=0; i<2; i++){
					for(int j=0; j<3;j++){
						aux = aux + w_h[i][j] * entrada[indice_aleatorio][j];
					}
					saida_camada_oculta[i] = aux;
					aux = 0;
					//printf("%f\n", saida_camada_oculta);
				}

				printf("\n");
				printf("Saída da camada oculta sem bias\n");
				print(saida_camada_oculta, 2);

				for(int i=0; i < 2; i++){
					saida_ativada[i] = sigmoide(saida_camada_oculta[i]);
				}

				printf("\n");
				printf("Saída ativada da camada oculta\n");
				print(saida_ativada, 2);

				for(int i=0; i<2; i++){
					saida_oculta_bias[i+1] = saida_ativada[i];
				}

				printf("\n");
				printf("Saída ativada da camada oculta com bias\n");
				print(saida_oculta_bias, 3);

				for(int i=0;i<3;i++){
					input_camada_saida[i] = saida_oculta_bias[i];
				}

				printf("\n");
				printf("Entradas da camada de saída\n");
				print(input_camada_saida, 3);

				for(int i=0; i<3; i++){
					resposta_rede = resposta_rede + w_o[i]*input_camada_saida[i];
				}

				resposta_rede = sigmoide(resposta_rede);


				printf("\n");
				printf("Saída da rede %f\n", resposta_rede);

				//******************************************************//
				//				FIM DA FASE DE FORWARD					//
				//******************************************************//


				//******************************************************//
				//				INÍCIO DA FASE DE BACKWARD				//
				//******************************************************//



				erro = saidas_desejadas[indice_aleatorio] - resposta_rede;

				mse = mean(erro*erro, 4);
				//mse[cont] = erro*erro;
				delta_camada_saida = erro * df_sigmoide(resposta_rede);

				printf("\n");
				printf("%f\n", delta_camada_saida);

				for(int i=0; i<3; i++){
					w_o[i] = w_o[i] + learning_rate * delta_camada_saida * input_camada_saida[i];
				}

				printf("\n");
				printf("Pesos de saída atualizados\n");
				print(w_o, 3);

				aux=0;
				//memset(aux_vec, 0, sizeof(aux_vec));
				for(int i = 1; i<3 ; i++){
					aux = aux + delta_camada_saida*w_o[i];
				}


				memset(delta_camada_oculta,0,sizeof(delta_camada_oculta));
				for(int i=0; i<2;i++){
					delta_camada_oculta[i] = aux*df_sigmoide(saida_ativada[i]);
				}

				printf("\n");
				printf("Delta camada oculta\n");
				print(delta_camada_oculta, 2);


				for(int i=0; i<2; i++){
					for(int j=0; j<3; j++){
						w_h[i][j] = w_h[i][j] + learning_rate*delta_camada_oculta[i]*entrada[indice_aleatorio][j];
					}
				}
				printf("\n");
				printf("Pesos da camada oculta atualizados\n");
				for(int i=0; i<2; i++){
					printf("|");
					for(int j=0; j<3; j++){
						printf("%f ", w_h[i][j]);
					}

					printf("|");
					printf("\n");
				}

				// printf("\n");
				cont = cont + 1;
				erro_m_atual = mse;

				printf("\n");
				printf("Diferença entre os erros %f", fabs(erro_m_atual - erro_ant));
				printf("\n");


				//******************************************************//
				//				FIM DA FASE DE BACKWARD				//
				//******************************************************//
				//fabs(erro_m_atual - erro_ant) < 10e-5
		}
	}while ( cont < 10000 || fabs(erro_m_atual - erro_ant) > 10e-7);


	// TESTE DA REDE

		// int input[3] = {-1, 0, 1};
		// 	aux = 0;
		// 	for(int i=0; i<2; i++){
		// 		for(int j=0; j<3;j++){
		// 			aux  = aux + w_h[i][j] * input[j];
		// 		}
		// 		saida_camada_oculta[i] = aux;
		// 		aux = 0;
		// 		//printf("%f\n", saida_camada_oculta);
		// 	}
		//
		// 	printf("\n");
		// 	printf("Saída da camada oculta sem bias\n");
		// 	print(saida_camada_oculta, 2);
		//
		// 	for(int i=0; i < 2; i++){
		// 		saida_ativada[i] = sigmoide(saida_camada_oculta[i]);
		// 	}
		//
		// 	printf("\n");
		// 	printf("Saída ativada da camada oculta\n");
		// 	print(saida_ativada, 2);
		//
		// 	for(int i=0; i<2; i++){
		// 		saida_oculta_bias[i+1] = saida_ativada[i];
		// 	}
		//
		// 	printf("\n");
		// 	printf("Saída ativada da camada oculta com bias\n");
		// 	print(saida_oculta_bias, 3);
		//
		// 	for(int i=0;i<3;i++){
		// 		input_camada_saida[i] = saida_oculta_bias[i];
		// 	}
		//
		// 	printf("\n");
		// 	printf("Entradas da camada de saída\n");
		// 	print(input_camada_saida, 3);
		//
		// 	for(int i=0; i<3; i++){
		// 		resposta_rede = resposta_rede + w_o[i]*input_camada_saida[i];
		// 	}
		//
		// 	resposta_rede = sigmoide(resposta_rede);
		//
		//
		// 	printf("\n");
		// 	printf("Saída da rede %f\n", resposta_rede);
		int i=0;
		while(i < 4){
		for(int i=0; i<4; i++){
				indice_aleatorio = valor_aleatorio();

				printf("Amostra da vez %d\n", indice_aleatorio);

				//erro_ant = mse;
				//******************************************************//
				//				INÍCIO DA FASE DE FORWARD				//
				//******************************************************//

				for(int i=0; i<2; i++){
					for(int j=0; j<3;j++){
						aux = aux + w_h[i][j] * entrada[indice_aleatorio][j];
					}
					saida_camada_oculta[i] = aux;
					aux = 0;
					//printf("%f\n", saida_camada_oculta);
				}

				printf("\n");
				printf("Saída da camada oculta sem bias\n");
				print(saida_camada_oculta, 2);

				for(int i=0; i < 2; i++){
					saida_ativada[i] = sigmoide(saida_camada_oculta[i]);
				}

				printf("\n");
				printf("Saída ativada da camada oculta\n");
				print(saida_ativada, 2);

				for(int i=0; i<2; i++){
					saida_oculta_bias[i+1] = saida_ativada[i];
				}

				printf("\n");
				printf("Saída ativada da camada oculta com bias\n");
				print(saida_oculta_bias, 3);

				for(int i=0;i<3;i++){
					input_camada_saida[i] = saida_oculta_bias[i];
				}

				printf("\n");
				printf("Entradas da camada de saída\n");
				print(input_camada_saida, 3);

				for(int i=0; i<3; i++){
					resposta_rede = resposta_rede + w_o[i]*input_camada_saida[i];
				}

				resposta_rede = sigmoide(resposta_rede);


				printf("\n");
				printf("Saída da rede %f\n", resposta_rede);

				//******************************************************//
				//				FIM DA FASE DE FORWARD					//
				//******************************************************//
		}
		i++;
	}
	// FIM DO TESTE

	return 0;
}


void forward(int n_amostras, int n_entradas,float pesos[][n_entradas],int entradas[], int resultado_I[]){
	int aux = 0;
	for(int i=0; i<n_amostras; i++){
		for(int j=0; j<n_entradas; j++){
			aux = aux + pesos[i][j]*entradas[j];
		}
		resultado_I[i] = aux;
		aux = 0;
	}




}

/*
void atualiza_peso_camada_saida(int n_output, int n_entradas, float pesos_saida[][n_entradas], float entrada_I[]){
	//LEMBRAR QUE ENTRADA_I DEVE SER O RESULTADO DA SIGMOIDE
	float delta_saida = (saida_esperada - saida_rede) * df_sigmoide(entrada_I);

	for(int i = 0; i < n_output; i++){
		for(int j=0; j<n_entradas; j++){
			pesos_saida[j][i] =
		}
	}

}
*/
int valor_aleatorio(){
	return rand()%tam_amostra;
}

void print(float val[], int len){
	for(int i=0; i<len; i++){
		printf("%f\n", val[i]);
	}
}

float sigmoide(float x){
	return 1.0/(1 + exp(-x));
}

//LEMBRE QUE A DERIVADA DA SIGMOIDE É ELA VEZES (1 - SIGMOIDE)
// DF(X) = F(X) * (1 - F(X))
//PORTANTO, A ENTRADA DESSA FUNÇÃO É O SINAL ATIVADO DE CADA CAMADA
float df_sigmoide(float x){
	return x*(1-x);
}

float mean(float erro, int tam){
	error_mean = error_mean + 0.5*error_mean;
	return error_mean/tam;
}
