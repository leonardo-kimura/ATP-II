#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>

struct TpProduto
{
	int Codigo, Estoque;
	char Descr[30];
	float Preco;
};


int BuscaExaustiva(FILE *PtrArq, int Cod){
	int i=0;
	while (i < TL && Cod!=Tab[i].Codigo)
	i++;
	if(i<TL)
		return i;
	else
		return -1;
}

void CADProduto(char NArq[80])
{
	TpProduto Prod;
	FILE *PtrProd = fopen(NArq,"ab");
	printf("\n## Cadastro de Produtos ##\n");
	printf("Codigo: ");
	scanf("%d",&Prod.Codigo);
	while (Prod.Codigo>0)
	{
		printf("Descricao: ");
		fflush(stdin);
		gets(Prod.Descr);
		printf("Qtde em Estoque: ");
		scanf("%d",&Prod.Estoque);
		printf("Preco: R$ ");
		scanf("%f",&Prod.Preco);
		fwrite(&Prod,sizeof(TpProduto),1,PtrProd);
		
		printf("\nCodigo: ");
		scanf("%d",&Prod.Codigo);
	}
	fclose(PtrProd);
}

void VerifArquivo(char NArq[80])
{
	FILE *PtrArq;
	
	PtrArq = fopen(NArq,"rb");
	if (PtrArq == NULL)  //Não foi aberto!
	{
		printf("\nErro de abertura!");
		printf("\nDeseja cria-lo (S/N)? ");
		if (toupper(getche())=='S')
		{
			PtrArq = fopen(NArq,"wb");
			printf("\nArquivo Criado!");
			fclose(PtrArq);
		}
	}
	else
		{
			printf("\nArquivo pronto para uso!\n");
			fclose(PtrArq);
		}
	getch();
}

void NomeArquivo(char Caminho[80])
{
	printf("\nCaminho/Nome do Arquivo: ");
	fflush(stdin);
	gets(Caminho);
}

void CONSProduto(char Caminho[80]){
	TpProduto RP;
	FILE *PtrProd = fopen(Caminho,"rb");
	clrscr();
	printf("\n## Consulta Produto pelo Codigo\n");
	if(PtrProd == NULL)
		printf("\nErro na Abertura\n");
	else{
		print("Codigo a Consultar: ");
		scanf("%d",&RP.Codigo);
		while(RP.Codigo>0)
		{
			pos = BuscaExaustiva(PtrProd,RP.Codigo);
			if(pos == -1)
				print("\nProduto nao Cadastrado!n");
			else{
				fseek(BUFFER,DESLOCAMENTO); //Posicionar
				fread(); //Ler Registro
				printf("** Detalhes do Produto **\n");
				printf("Codigo: %d\n",RP.Codigo);
				printf("Descricao: %s\n",RP.Descr);
				printf("Estoque: %d\n",RP.Estoque);
				printf("Preco: %.2f\n",RP.Preco);
			}
		}
	}
}

void RELProduto(char Caminho[80]){
	TpProduto RP;
	FILE *PtrProd = fopen(Caminho, "rb");
	clrscr(); printf("\n## Relatorio de Produtos ##\n");
	if (PtrProd == NULL)
		printf("\nErro de Abertura!\n");
	else{
		fread(&RP,sizeof(TpProduto),1,PtrProd);
		while(!feof(PtrProd)){
			printf("\n%d \t %s \t %d \t %.2f",RP.Codigo,RP.Descr,RP.Estoque,RP.Preco);
			fread(&RP,sizeof(TpProduto),1,PtrProd);
		}
		fclose(PtrProd);
	}
	getch();
}


int main(void)
{
	char NomeArq[80];
	
	NomeArquivo(NomeArq);
	VerifArquivo(NomeArq);
	CADProduto(NomeArq);
	RELProduto(NomeArq);
	CONSProduto(NomeArq);
	return 0;
}
