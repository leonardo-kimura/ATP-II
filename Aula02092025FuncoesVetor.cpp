#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>

#define TF 100

//Declarando do Protótipo da Função
void LeVetor(int V[TF], int &QtdeElem);
void Frequencia(int Vetor[TF],int TL,int &MaiorFreq,int &QtdeVezes);
void ExibeVetor(int Vet[TF], int Qtde);

int SomaElementos(int VetNum[TF], int QtdeN){
	int i,soma=0;
	for(i=0; i < QtdeN;i++)
	soma = soma + VetNum[i];
	return soma;
}

void Frequencia(int Vetor[TF],int TL,int &MaiorFreq,int &QtdeVezes)
{
	int cont, i, j, aux;
	QtdeVezes=0;
	
	for(i=0; i < TL - 1; i++)
	{
		cont=1;
		for(j=i+1; j < TL; j++){
			if(Vetor[i] == Vetor[j])
			cont++;
		}
		if(cont>QtdeVezes){
			MaiorFreq = Vetor[i];	
			QtdeVezes = cont;	
				
		}
	}
}



void ExibeVetor(int Vet[TF], int Qtde)
{
	int i;
	clrscr();
	printf("\n### Conteudo do Vetor ###\n");
	if (Qtde==0)
		printf("\nVetor esta Vazio!\n");
	else
		for(i=0; i<Qtde; i++)
			printf("\nVetor[%d]: %d",i,Vet[i]);
	
	getch();
}

void LeVetor(int V[TF], int &QtdeElem)
{
	int aux;
	clrscr();
	printf("\n### Inserir Elementos em um Vetor ###\n");
	printf("Vetor[%d]: ",QtdeElem);
	scanf("%d",&aux);
	while(QtdeElem<TF && aux>0)
	{
		V[QtdeElem] = aux;
		QtdeElem++;
		
		printf("\nVetor[%d]: ",QtdeElem);
		scanf("%d",&aux);
	}
}
int BuscaElemento(int V[TF], int TL, int Numero)
{	// BUSCA DO CHICO;
	int i=0;
	while(i<TL && Numero != V[i])
	i++;
	if(i<TL){
		return 1;//achou
		
		
		
		
	}else
	  return 0;	// NOT achou
}

void Subtracao(int A[TF],int QA, int B[TF], int QB, int C[TF], int QC){
	int i;
	QC = 0;
	for(i=0; i < QA;i++)
		if(!BuscaElemento(B,QB),A[i]){ //elemetos de A
			if(!BuscaElemento(C,QC,A[i]))
			C[QC++] = A[i]; //++QC primeiro incrementa e dps faz o tem q fzr;
		}
	printf("\nSubtracao concluida!\n");
}


int main(void)
{
	int VA[TF], VB[TF], VC[TF*2], TLA=0, TLB=0, TLC, Valor, Vezes, Num;
	printf("\n*** Vetor A ***\n");
	LeVetor(VA,TLA);
	ExibeVetor(VA,TLA);
	Frequencia(VA,TLA,Valor,Vezes);
	printf("\nValor de Maior Frequencia: %d\n",Valor);
	printf("\nQuantidade de Vezes: %d",Vezes);
	printf("\nSoma dos valores do Vetor: %d\n",SomaElementos(VA,TLA));
	//exercício 3
	printf("Digite o elemento: \n");
	scanf("%d",&Num);
	if(BuscaElemento(VA,TLA,Num))
		printf("Elemento encontrado!");
	else
		printf("Elemento nao encontrado.");	
	//exercício 5a
	printf("\n*** Vetor B ***\n");
	Levetor(VB,TLB);
	ExibeVetor(VB,TLB);
	
	Subtracao(VA,TLA,VB,TLB,VC,TLC);
	printf("\n***Resultado da Subtracao: VA - VB ###\n");
	ExibeVetor(VC,TLC);
	
	getch();
	return 0;
}





