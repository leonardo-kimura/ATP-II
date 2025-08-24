#include <stdio.h>
#include <string.h>
#include <conio2.h>
#include <stdlib.h>
#include <ctype.h>

#define TF 5
struct TpPessoa {
	char Nome[25], End[50], Tel[20];
};

int main(void){
	TpPessoa TabPessoa[TF];
	int TLP=0,i;
	char AuxNome[25],Endereco[50],Tel[20];
	
	
		printf("Digite o nome: \n");
		fflush(stdin);
		gets(AuxNome);
	while(TLP < TF && strcmp(AuxNome,"\0") != 0){
		strcpy(TabPessoa[TLP].Nome,AuxNome);
		printf("Digite o endereco\n");
		fflush(stdin);
		gets(Endereco);
		strcpy(TabPessoa[TLP].End,Endereco);
		printf("Digite o Telefone:\n");
		fflush(stdin);
		gets(Tel);
		strcpy(TabPessoa[TLP].Tel,Tel);
		TLP++;
		printf("Digite o nome: \n");
		fflush(stdin);
		gets(AuxNome);
	}	
	for(i = 0; i < TLP;i++){
		printf("Nome: %s\nEndereco: %s\nTelefone: %s\n\n",TabPessoa[i].Nome,
													  TabPessoa[i].End,
													  TabPessoa[i].Tel);
	}
return 0;	
}
