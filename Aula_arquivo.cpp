#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

struct TpProduto{
	int Codigo, Estoque;
	char Descr[30];
	float Preco;
};

void CADProduto(char NArq[80]){
	TpProduto Prod;
	FILE *PtrProduto = fopen(NArq,"ab");
	printf("\n ### Cadastro de Produtos ###\n");
	printf("Codigo: ");
	scanf("%d",&Prod.Codigo);
	while(Prod.Codigo>0){
		printf("Descricao: ");
		fflush(stdin);
		gets(Prod.Descr);
		printf("Qtd em Estoque: ");
		scanf("%d",&Prod.Estoque);
		printf("Preco: R$ ");
		scanf("%f",&Prod.Preco);
		fwrite(&Prod,sizeof(TpProduto),1,PtrProduto);
		
		printf("\nCodigo: ");
		scanf("%d",&Prod.Codigo);
	}
}


void VerifArquivo(char NArq[80]){
	FILE *PtrArq;
	
	PtrArq = fopen(NArq,"rb");
	if (PtrArq == NULL){
		printf("\nErro de abertura!");
		printf("Deseja cria-lo (S/N)? ");
		if(toupper(getche())== 'S'){
			PtrArq = fopen(NArq, "wb");
			printf("\nArquivo Criado!");
			fclose(PtrArq);
			getch();
		}
	}
	else{
		printf("\nArquivo pronto para uso!\n");
		fclose(PtrArq);
	}
	getch();
}

void NomeArquivo(char Caminho[80]){
	printf("Caminho/Nome do Arquivo: ");
	fflush(stdin);
	gets(Caminho);
}


int main(void){
	char NomeArq[80];
	NomeArquivo(NomeArq);
	VerifArquivo(NomeArq);
	CADProduto(NomeArq);
	return 0;
}
