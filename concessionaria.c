/*
"r": abre para leitura (o arquivo deve existir).
"w": abre para escrita (cria um novo arquivo ou apaga o conteúdo se já existir).
"a": abre para adicionar (escreve no final sem apagar o conteúdo existente).
"r+": abre para leitura e escrita (o arquivo deve existir).
"w+": abre para leitura e escrita (cria um novo arquivo ou apaga o conteúdo se já existir).
"a+": abre para leitura e escrita (adiciona no final).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tam 5

typedef struct{
	char modelo[50];
	char marca[50];
	int ano;
	int potencia;
	float preco;
	int disponivel;
	int codigo;
}carro;

carro car[tam];
int indice = 0, i_relatorio = 0;

void menu(){
	system("cls");
	printf("===========================/ Unifenas Garage /===========================\n\n");
	
	printf("                       ___________________\n");                              
    printf("                    //|           |         \\ \n");                            
    printf("                  //  |           |           \\ \n");                          
    printf("    ____________//____|___________|___________()\\__________________ \n");      
    printf("   /__________________|_=_________|_=___________|_________________{} \n");    
    printf("   [            _____ |           | .           | == ______      {  } \n");   
	printf("  _[___       /##  ##\\|           |             |   /##  ##\\    _{ *}_ \n"); 
	printf(" {_____)_____|##    ##|___________|_____________|__|##    ##|__(______} \n");
    printf("             / ##__##                              / ##__##        \ \n"); 
	
	printf("\n\n\t1 - Cadastrar veiculo    \t2 - Consultar veiculos\n");
	printf("\t3 - Gerar arquivo relatorio  \t4 - Excluir veiculo\n");
	printf("\n\t5 - Sair da Garagem\n\n");  
	printf("Digite a opcao desejada: ");
}

void cadastrar(FILE *arqb){
	
	if(indice == tam - 1){
		return;
	}
	fflush(stdin);
	system("cls");
	printf("Digite o nome do veiculo: ");
	fgets(car[indice].modelo, sizeof(car[indice].modelo), stdin);
	printf("\nDigite o nome do fabricante: ");
	fgets(car[indice].marca, sizeof(car[indice].marca), stdin);
	printf("\nDigite o ano de fabricacao: ");
	scanf("%d", &car[indice].ano);
	printf("\nDigite a potencia do veiculo (em numero de cavalos): ");
	scanf("%d", &car[indice].potencia);
	printf("\nDigite o preco do veiculo: ");
	scanf("%f", &car[indice].preco);
	printf("\nInforme o codigo do veiculo no programa: ");
	scanf("%d", &car[indice].codigo);
	
	car[indice].disponivel = 1;	
	
	size_t len = strlen(car[indice].marca);   
    size_t len2 = strlen(car[indice].modelo);
    
    if (len > 0 && car[indice].marca[len - 1] == '\n') {
        car[indice].marca[len - 1] = '\0';
    }
    
    if (len2 > 0 && car[indice].modelo[len2 - 1] == '\n') {
        car[indice].modelo[len2 - 1] = '\0';
    }
    
    //-------------------------------------------
    size_t escrita = fwrite(&car[indice], sizeof(carro), 1, arqb);
	if (escrita != 1) {
    	printf("Erro ao escrever os dados no arquivo.\n");
    	fclose(arqb);
    	return;
	}

    indice++;
}

void consultar(){
	
	int cod, achou = 0;
	
	system("cls");
	
	if(indice == 0){
		printf("Nenhum veiculo cadastrado!\n");
		system("pause");
		return;
	}
	
	printf("Digite o codigo do veiculo: ");
	scanf("%d", &cod);
	
	for(int i = 0; i < indice; i++){
		if(car[i].codigo == cod){
			achou = 1;
			printf("Veiculo localizado com sucesso! \n\n");
			printf("Marca: %s\t Veiculo: %s\t Ano: %d\t Potencia: %dHP\t  Valor: R$ %.2f\t\n\n\n", car[i].marca, car[i].modelo, car[i].ano, car[i].potencia, car[i].preco);
			system("pause");
		}
	}
	
	if(achou == 0){
		printf("Veiculo nao localizado!\n");
		system("pause");
		return;	
	}
	
}

void excluir(){

	int op, encontrado = 0;
	
	system("cls");
	
	if(indice == 0){
		printf("Nenhum veiculo cadastrado!\n");
		system("pause");
		return;
	}
	
	printf("========================== Carros disponiveis ==========================\n\n");
	
	for(int i = 0; i < indice; i++){
		if(car[i].disponivel == 1){
			printf("Codigo %d Marca: %s Veiculo: %s Ano: %d Potencia: %d Valor: %.2f\n", car[i].codigo, car[i].marca, car[i].modelo, car[i].ano, car[i].potencia, car[i].preco);
		}
	}
	
	printf("\nDigite o codigo do veiculo que deseja excluir: ");
	scanf("%d", &op);
	
	for(int i = 0; i < indice; i++){
		if(car[i].codigo == op){
			car[i].disponivel = 0;
			printf("Veiculo excluido com sucesso!\n");
			encontrado = 1;
			system("pause");
		}
	}
	
	if (!encontrado) {
        printf("Veiculo com o codigo %d nao encontrado.\n", op);
        system("pause");
    }
		
}

void relatorio(FILE *arq){
	
	if(indice == 0){
		system("cls");
		printf("Nenhum veiculo cadastrado!\n");
		system("pause");
		return;
	}
	
	long tam_arq = ftell(arq);
	
	if(tam_arq == 0){
		fprintf(arq, "Codigo \t\t Fabricante \t\t Modelo \t\t Ano \t\t Potencia(HP) \t\t  Valor\n");
		fprintf(arq, "------------------------------------------------------------------------------------------------------------------\n");
		i_relatorio = 1;
	}
	
	for(int i = 0; i < indice; i++){	
		fprintf(arq, "%-17d%-24s%-15s%13d%15d%30.2f",car[i].codigo, car[i].marca, car[i].modelo, car[i].ano, car[i].potencia, car[i].preco);
		fprintf(arq, "\n");
	}
	
	printf("Relatorio gerado com sucesso!\n");
	system("pause");
}

int main(){
	
	int op = 0;
	FILE *arq;
	arq = fopen("dados", "a+");
	
	FILE *arqb;
	arqb = fopen("dados_b", "wb");
	
	if(arqb == NULL){
		printf("Erro ao abrir o arquivo binario!\n");
		system("pause");
	}else{
		printf("Arquivo binario criado e aberto com sucesso!\n");
		system("pause");
	}
	
	if(arq == NULL){
		arq = fopen("dados", "w+");
		if(arq == NULL){
			printf("Error ao abrir o arquivo!\n");
			system("pause");
		}else{
			printf("Arquivo txt criado e aberto com sucesso!\n");
			system("pause");
		}
	}else{
		printf("Arquivo txt existente aberto com sucesso!\n");
		system("pause");
		fseek(arq, 0, SEEK_END);
	}
	
	
	if(arqb == NULL){
		printf("Erro ao criar o arquivo binario!\n");
	}
	
	
	do{
		menu();
		scanf("%d", &op);
		
		switch(op){
			case 1:
				cadastrar(arqb);
				break;
			case 2:
				consultar();
				break;
			case 3:
				relatorio(arq);
				break;
			case 4:
				excluir();
				break;
		}
	}while(op != 5);
	
	fclose(arq);
	fclose(arqb);
	
	return 0;
}