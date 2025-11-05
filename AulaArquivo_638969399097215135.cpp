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

int BuscaExaustiva(FILE *PtrArq, int Cod)
{
	TpProduto RP;
	rewind(PtrArq);  //fseek(PtrArq,0,0);
	fread(&RP,sizeof(TpProduto),1,PtrArq);
	while (!feof(PtrArq) && Cod!=RP.Codigo)
		fread(&RP,sizeof(TpProduto),1,PtrArq);
	
	if (Cod == RP.Codigo)
		return ftell(PtrArq)-sizeof(TpProduto);
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

void RELProduto(char Caminho[80])
{
	TpProduto RP;
	FILE *PtrProd = fopen(Caminho,"rb");
	clrscr(); printf("\n## Relatorio de Produtos ##\n");
	if (PtrProd == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			fread(&RP,sizeof(TpProduto),1,PtrProd);
			while (!feof(PtrProd))
			{
				printf("\n%d \t %s \t %d \t %.2f",RP.Codigo,RP.Descr,RP.Estoque,RP.Preco);
				fread(&RP,sizeof(TpProduto),1,PtrProd);
			}
			fclose(PtrProd);
		}
	getch();
}

void CONSProduto(char Caminho[80])
{
	TpProduto RP;
	int pos;
	FILE *PtrProd = fopen(Caminho,"rb");
	clrscr();
	printf("\n## Consulta Produtos pelo Codigo ##\n");
	if (PtrProd == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("Codigo a Consultar: ");
			scanf("%d",&RP.Codigo);
			while(RP.Codigo>0)
			{
				pos = BuscaExaustiva(PtrProd,RP.Codigo);
				if(pos==-1)
					printf("\nProduto nao Cadastrado!\n");
				else
					{
						//fseek(BUFFER,DESLOCAMENTO_BYTES,A PARTIR DE ONDE); //Posicionar						
						fseek(PtrProd,pos,SEEK_SET); //SEEK_CUR  SEEK_END
						fread(&RP,sizeof(TpProduto),1,PtrProd); //Ler Registro
						printf("** Detalhes do Produto **\n");
						printf("Codigo: %d\n",RP.Codigo);
						printf("Descricao: %s\n",RP.Descr);
						printf("Estoque: %d\n",RP.Estoque);
						printf("Preco: R$ %.2f\n",RP.Preco);
					}
				
				printf("\nCodigo a Consultar: ");
				scanf("%d",&RP.Codigo);		
			}
			fclose(PtrProd);
		}
}

void ALTProduto(char Caminho[80])
{
	TpProduto RP;
	int pos;
	FILE *PtrProd = fopen(Caminho,"rb+");
	clrscr();
	printf("\n## Altera Produtos pelo Codigo ##\n");
	if (PtrProd == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("Codigo a Alterar: ");
			scanf("%d",&RP.Codigo);
			while(RP.Codigo>0)
			{
				pos = BuscaExaustiva(PtrProd,RP.Codigo);
				if(pos==-1)
					printf("\nProduto nao Cadastrado!\n");
				else
					{
						//fseek(BUFFER,DESLOCAMENTO_BYTES,A PARTIR DE ONDE); //Posicionar						
						fseek(PtrProd,pos,0); //SEEK_SET  SEEK_CUR  SEEK_END
						fread(&RP,sizeof(TpProduto),1,PtrProd); //Ler Registro
						printf("** Detalhes do Produto **\n");
						printf("Codigo: %d\n",RP.Codigo);
						printf("Descricao: %s\n",RP.Descr);
						printf("Estoque: %d\n",RP.Estoque);
						printf("Preco: R$ %.2f\n",RP.Preco);
						printf("\nDeseja Alterar (S/N)? ");
						if (toupper(getche())=='S')
						{
							printf("\nNovo Codigo: ");
							scanf("%d",&RP.Codigo);printf("Nova Descricao: ");
							fflush(stdin);
							gets(RP.Descr);
							printf("Nova Qtde em Estoque: ");
							scanf("%d",&RP.Estoque);
							printf("Novo Preco: R$ ");
							scanf("%f",&RP.Preco);
							fseek(PtrProd,pos,0);
							fwrite(&RP,sizeof(TpProduto),1,PtrProd);
							printf("\nDados do Produto alterados!\n");
						}
					}
				getch();
				printf("\nCodigo a Alterar: ");
				scanf("%d",&RP.Codigo);		
			}
			fclose(PtrProd);
		}
}

void OrdenaArq(char NArq[80])
{
	TpProduto RegA, RegB;
	int a,b, QtReg;
	FILE *PtrProd = fopen(NArq,"rb+");
	if (PtrProd == NULL)
		printf("\nErro de abertura, arquivo nao ordenado!\n");
	else
		{
			fseek(PtrProd,0,2); //SEEK_END
			QtReg = ftell(PtrProd) / sizeof(TpProduto);
			for(a=0; a < QtReg-1; a++)
				for(b=a+1; b < QtReg; b++)
				{
					fseek(PtrProd,a*sizeof(TpProduto),0); //SEEK_SET
					fread(&RegA,sizeof(TpProduto),1,PtrProd);
					
					fseek(PtrProd,b*sizeof(TpProduto),0);
					fread(&RegB,sizeof(TpProduto),1,PtrProd);
					
					if(stricmp(RegA.Descr,RegB.Descr)>0)
					{
						fseek(PtrProd,a*sizeof(TpProduto),0);
						fwrite(&RegB,sizeof(TpProduto),1,PtrProd);
						
						fseek(PtrProd,b*sizeof(TpProduto),0);
						fwrite(&RegA,sizeof(TpProduto),1,PtrProd);
					}
				}
			fclose(PtrProd);
			printf("\nArquivo Ordenado!\n");
		}
	getch();
}


void EXCProduto(char caminho [80]){
	
	TpProduto RP;
	int pos,AuxCod;
	FILE *PtrProd = fopen(caminho,"rb");
	clrscr();
	printf("\n## Excluir Produtos pelo Codigo ##\n");
	if (PtrProd == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("Codigo a excluir: ");
			scanf("%d",&AuxCod);
			if(AuxCod > 0)
			{
				pos = BuscaExaustiva(PtrProd,AuxCod);
				if(pos==-1)
					printf("\nProduto nao Cadastrado!\n");
				else
					{
						//fseek(BUFFER,DESLOCAMENTO_BYTES,A PARTIR DE ONDE); //Posicionar						
						fseek(PtrProd,pos,0); //SEEK_SET = 0  SEEK_CUR = 1 SEEK_END = 2
						fread(&RP,sizeof(TpProduto),1,PtrProd); //Ler Registro
						printf("** Detalhes do Produto **\n");
						printf("Codigo: %d\n",RP.Codigo);
						printf("Descricao: %s\n",RP.Descr);
						printf("Estoque: %d\n",RP.Estoque);
						printf("Preco: R$ %.2f\n",RP.Preco);
						printf("\nDeseja Fazer a EXCLUSAO (S/N)? ");
						if (toupper(getche())=='S')
						{
							FILE *PtrTemp = fopen("Temp.dat", "wb");
							rewind(PtrProd);
							fread(&RP,sizeof(TpProduto),1,PtrProd);
							while(!feof(PtrProd)) //vai percorrer todo o arquivo
							{
								if(RP.Codigo != AuxCod)
									fwrite(&RP,sizeof(TpProduto),1,PtrTemp);
									
								fread(&RP,sizeof(TpProduto),1,PtrProd);
							}
							fclose(PtrProd);
							fclose(PtrTemp);
							remove(caminho);
							rename("Temp.dat", caminho);
							printf("\nProduto deletado!\n");
						}
						else 
						fclose(PtrProd);
					}
				getch();	
			}
			else fclose(PtrProd);
		}
}
int main(void)
{
	char NomeArq[80];
	
	NomeArquivo(NomeArq);
	VerifArquivo(NomeArq);
	CADProduto(NomeArq);
	RELProduto(NomeArq);
	CONSProduto(NomeArq);
	ALTProduto(NomeArq);
	OrdenaArq(NomeArq);
	RELProduto(NomeArq);
	EXCProduto(NomeArq);
	return 0;
}
