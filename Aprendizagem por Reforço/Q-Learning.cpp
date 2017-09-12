/*
	Algoritmo Q_Learning, implementado
	por Matheus Pessoa.
	Data de modificação: 14/08/2016

	Número de estados: 6
	Número de episódios: variável

*/


#include <iostream>
#include <stdlib.h>

using namespace std;

int r_matrix [6][6]= {
                	{-1,-1,-1,-1,0,-1}, {-1,-1,-1,0,-1,100},
			{-1,-1,-1,0,-1,-1}, {-1,0,0,-1,0,-1},
			{0,-1,-1,0,-1,100}, {-1,0,-1,-1,0,100}
		};


int q_matrix[6][6];
float gamma = 0.8;
int current_state=0, number_of_episodes = 1000, goal_state = 5, states = 6;
int best_path[6];


//ESSA FUNÇÃO ESTÁ CALCULANDO O MAIOR VALOR DE UMA LINHA NA TABELA Q
int return_max_value(int next_state){

int max = 0;

	for(int i=0;i<6;i++){
		if(q_matrix[next_state][i] != -1){
			if(q_matrix[next_state][i] > max){
				max = q_matrix[next_state][i];
			}
		}
	}

	return max;
}


//ESSA FUNÇÃO RETORNA UM VALOR ALEATÓRIO DE ESTADO PARA INICIAR O TREINAMENTO DO AGENTE
int select_state_randomly(int states){
	return rand()%states;
}

int select_action(int current_state){
    int action = 0;
    action = rand()%states;

    while(r_matrix[current_state][action] == -1){
        action = rand()%states;
    }
    return action;
}

//ESSA FUNÇÃO RETORNA O VALOR Q QUE É CALCULADO
int compute_q_value(int next_state, int action){
	return r_matrix[current_state][action] + gamma*return_max_value(next_state);
}

void print_q(){
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			cout << q_matrix[i][j] << " ";
		}
	cout << "" <<endl;
	}
}

void print_r(){
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			cout << r_matrix[i][j] << " ";
		}
	cout << "" <<endl;
	}
}

void start_episode(){
    int x, next_state = 0,action = 0;
    while(x < number_of_episodes){
        current_state = select_state_randomly(6);
        cout << "estado inicial "<<current_state<< " do episodio "<< x << endl;
        do{
            action = select_action(current_state);
            cout << "acao selecionada "<<action << endl;
            next_state = action;
            q_matrix[current_state][action] = compute_q_value(next_state, action);
            current_state = next_state;
            cout << "novo estado " << current_state << " episodio " << x << endl;
        }while(current_state!=goal_state);
    x++;
    }
}

void find_best_path(int initial_state){
    int next = 0, value=0, x=0;
    if(initial_state == goal_state){
        cout << "Esse já é o objetivo "<<endl;
    }else{
        cout << "O melhor caminho partindo de "<< initial_state << " eh "<<endl;
        while(initial_state != goal_state && x < states){
            value = return_max_value(initial_state);

            for(int i=0;i<states;i++){
                if(q_matrix[initial_state][i] == value){
                    next = i;
                    break;
                }
            }
            best_path[x] = next;

            initial_state = next;
            x++;
        }

        cout << "[";
        for(int i=0;i<states;i++){
            cout << best_path[i] << " ";
        }
        cout << "]";
	}
}

int main(){

for(int i=0;i<6;i++){
	for(int j=0;j<6;j++){
		q_matrix[i][j] = 0;
	}
}
srand(time(NULL));
/*
current_state = 1;
int estado_temporario = 5, valor_recompensa=0;

//compute_q_valeu(estado_temporario,action);
valor_recompensa = compute_q_value(5,5); // O 5 FOI "SELECIONADO RANDOMICAMENTE". AQUI, PARA FIM DE TESTE, FOI COLOCADO NA MÃO
q_matrix[current_state][5] = valor_recompensa; // O 5 AQUI SERIA A AÇÃO QUE FOI SELECIONADA PARA SER FEITA
print_q();

current_state = 3;
q_matrix[current_state][1] = compute_q_value(1,1); //1 PASSA A SER AGORA, ALÉM DA MINHA AÇÃO, MEU PRÓXIMO ESTADO POSSÍVEL
cout << endl;
print_q();
*/

start_episode();
print_q();
current_state = rand()%states;
cout << "Estado inicial"<< endl;
int u;
cin >> u;
find_best_path(u);
cout <<"estado inicial " <<current_state << endl;

return 1;
}



