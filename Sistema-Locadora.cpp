#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#define TF 30

/*

---------Trabalho feito por-----------

262516217 - Gabriel Ribeiro de Souza
---------------------------------------
262516950 - Leonardo Yukio Kimura
---------------------------------------
262516314  - Luis Antonio Moreira Giolo
----------------------------------------

*/


// Interface
void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
{
	int i; 
	textcolor(CorT);
	textbackground(CorF);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LF);
	printf("%c",188);
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI);
		printf("%c",205);

		gotoxy(i,LF);
		printf("%c",205);
	}

	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i);
		printf("%c",186);

		gotoxy(CF,i);
		printf("%c",186);
	}
	textcolor(7);
	textbackground(0);
}

// Tabelas do Programa

struct TpClientes // Tabela - Clientes
{
	char CPF[15];
	char Nome[120];
	char Telefone[14];
};

struct TpCarros  // Tabela - Carros
{
	int CodCar;
	char Modelo[30];
	char Categoria[30];
	float PrecoDia;
};

struct TpLocacoes{ // Tabela - Locações

	char CPF[15];
	int CodCar, QtdDias;
	float ValorLoc;
};

// Funções do programa

int BuscaCPF(TpClientes Cli[TF], int TC,char CodCPF[15]);    //Busca Exaustiva      - Buscando CPF do cliente
int BuscacomSentinelaCod(TpCarros Car[TF+1], int TL, int cod); //Busca com Sentinela - Buscando código do carro
void InsercDireta(TpClientes Cli[TF], int &TL);          // Inserção direta
void BubbleSort(TpCarros Carros[TF], int TL);           // BubbleSort
int BuscaBinaria(TpCarros Carros[TF], int TL, int cod); // Busca Binária
int SeqIndex(TpLocacoes Loc[TF], int &TLL, char AuxCPF[20]); // Sequencial Indexada
void SelectionSort(TpCarros Carros[TF], int TL);			// Seleção direta

//CLIENTES
void CADAcliente(TpClientes Cli[TF], int &TL);         //Cadastro de Cliente - Cadastrando cliente
void AltCliente(TpClientes Cli[TF],int TL);         //Alterar Cliente - Alterando cliente
void ExcluCliente(TpClientes Cli[TF], int &TL);      // Exluir Cliente - Excluindo cliente
void Relatteste(TpClientes Cli[TF],int TL);         // Relatório de clientes cadastrados


//CARROS
void CadCarros(TpCarros Car[TF], int &TL); // Cadastro de Carros - Cadastrando carros
void ExcluirCarros(TpCarros Car[TF], int &TL); // Excluir Carros - Excluindo carros
void RelaCarros(TpCarros Carros[TF], int TLCA); // Relatório Carros
void AltCarros(TpCarros Carros[TF], int TL); // Alterar Carro - Alterando dados
void OrdenarCod(TpCarros Carros[TF], int TL); //Ordena por código
void OrdenarModel(TpCarros Carros[TF],int TL);//Ordena por modelo

//LOCACOES
void CadaLoc(TpLocacoes Loc[TF],TpCarros carros[TF], TpClientes clientes[TF], int &TLL, int TLC, int TLCA);
void ExcluLoc(TpLocacoes Loc[TF], int &TLL);
void AltLoc(TpLocacoes Loc[TF], TpCarros carros[TF], int TLL, int TLCA);
void RelaLoc(TpLocacoes Loc[TF], int &TLL);


//FUNÇÕES
void RelatorioClientesMais3Locacoes(TpLocacoes Loc[TF], int TLL);
void RelatorioLocacoesAcimaValor(TpLocacoes Loc[TF], int TLL);
void RelatorioCategoria(TpCarros Carros[TF], int TL);

//PRENCHER TABELAS

void PrencherTabelas(TpClientes Clit[TF], TpCarros Carros[TF],  TpLocacoes Locacoes[TF] ,int &TC, int &TCA, int &TLL);
// Prenche cada tabela com 10 dados



int BuscaCPF(TpClientes Cli[TF], int TC,char CodCPF[15])
{
	int i=0;
	while(i<TC && strcmp(CodCPF,Cli[i].CPF)!=0)
		i++;

	if(i<TC)
		return i;
	else
		return -1;
}

int BuscacomSentinelaCod(TpCarros Car[TF+1], int TL, int cod){

	int i=0;
	Car[TL].CodCar = cod; 

	while(cod != Car[i].CodCar)
		i++;

	if(i<TL)
		return i;
	else
		return -1;
}

void BubbleSort(TpCarros Carros[TF], int TL) {
	int j,i;
	TpCarros aux;
	for (i = 0; i < TL - 1; i++) {
        for (j = 0; j < TL - 1 - i; j++) {
            if (strcmp(Carros[j].Modelo, Carros[j + 1].Modelo) > 0) {
                aux = Carros[j];
                Carros[j] = Carros[j + 1];
                Carros[j + 1] = aux;
            }
        }
    }
}

void BubbleSort2(TpLocacoes Loc[TF], int TLL) {
	int i, j;
	TpLocacoes aux;
	for (i = 0; i < TLL - 1; i++){
		for (j = 0; j < TLL - 1 - i; j++){
			if (strcmp(Loc[j].CPF, Loc[j + 1].CPF) > 0){
				aux = Loc[j]; Loc[j] = Loc[j + 1];
				Loc[j + 1] = aux;
				}
		}
	}
}



int PosicaoMaior(TpCarros Carros[TF], int TL){
    int PosMaior = 0, i;

    for(i = 1; i < TL; i++)
        if(Carros[i].CodCar > Carros[PosMaior].CodCar){
            PosMaior = i;
        }
    return PosMaior;
}

void SelectionSort(TpCarros Carros[TF], int TL){
    int PosMaior;
    TpCarros Maior;

    while(TL > 1){
        PosMaior = PosicaoMaior(Carros, TL);
        Maior = Carros[PosMaior];
        Carros[PosMaior] = Carros[TL-1];
        Carros[TL-1] = Maior;
        TL--;
    }
}

void InsercDireta(TpClientes Cli[TF], int &TL){
    int i,j;
    TpClientes AuxCliente;

    for (i=1;i<TL;i++)
    {
        AuxCliente = Cli[i];
        j=i-1;
        while (j>=0 && strcmp(AuxCliente.CPF,Cli[j].CPF)<0)
        {
            Cli[j+1] = Cli[j];
            j--;
        }
        Cli[j+1] = AuxCliente;
    }
}

int BuscaBinaria(TpCarros Carros[TF],int TL, int Cod){
	int i=0,f=TL-1,m;
	while(i<=f){
		m = (i+f)/2;
		if(Cod == Carros[m].CodCar)
			return m;
		if(Cod < Carros[m].CodCar)
			f = m-1;
		else
			i = m+1;
	}
	return -1;
}
int BuscaBinaria2(TpLocacoes Loc[TF], int TLL, char AuxCPF[15])
{
    int i=0,f=TLL-1,m;

    while(i<= f)
    {
        m = (i+f)/2;

        if (strcmp(AuxCPF, Loc[m].CPF) == 0)
            return m;

        if (strcmp(Loc[m].CPF, AuxCPF) < 0)
            i = m+1;
        else
            f = m-1;
    }

    return -1;
}


int SeqIndex(TpLocacoes Loc[TF], int &TLL, char AuxCPF[20])
{
	int i = 0;
	while(i<TLL && strcmp(Loc[i].CPF,AuxCPF)<0)
		i++;
	if(i<TLL && strcmp(AuxCPF,Loc[i].CPF)==0)
		return i;
	else
		return -1;
}

void PrencherTabelas(TpClientes Clit[TF], TpCarros Carros[TF],  TpLocacoes Locacoes[TF] ,int &TC, int &TCA, int &TLL){

	TC=10;
	TCA =10;
	TLL = 10;
	//Prenchendo clientes

	strcpy(Clit[0].CPF, "195.901.258-40");
    strcpy(Clit[0].Nome, "Brenda Renata Almeida");
    strcpy(Clit[0].Telefone, "(18)2656-0872");

    strcpy(Clit[1].CPF, "051.159.728-24");
    strcpy(Clit[1].Nome, "Elza Débora Kamilly Ferreira");
    strcpy(Clit[1].Telefone, "(18)3977-2076");

    strcpy(Clit[2].CPF, "125.911.458-90");
    strcpy(Clit[2].Nome, "Anderson Gael Giovanni Porto");
    strcpy(Clit[2].Telefone, "(18)3715-9504");

    strcpy(Clit[3].CPF, "848.384.258-05");
    strcpy(Clit[3].Nome, "Nathan Thiago Bruno Caldeira");
    strcpy(Clit[3].Telefone, "(18)2897-9046");

    strcpy(Clit[4].CPF, "936.649.248-78");
    strcpy(Clit[4].Nome, "Nicole Antônia Elisa Bernardes");
    strcpy(Clit[4].Telefone, "(18)9994-2453");

    strcpy(Clit[5].CPF, "461.876.807.59");
    strcpy(Clit[5].Nome, "Gabriel Ribeiro de Souza");
    strcpy(Clit[5].Telefone, "(18)9969-0341");

    strcpy(Clit[6].CPF, "341.000.208-13");
    strcpy(Clit[6].Nome, "Leonardo Yukio Kimura");
    strcpy(Clit[6].Telefone, "(18)3744-5441");

     strcpy(Clit[7].CPF, "834.714.968-23");
    strcpy(Clit[7].Nome, "Luiz Antonio Moreira Giolo");
    strcpy(Clit[7].Telefone, "(18)3889-7166");


    strcpy(Clit[8].CPF, "024.815.148-74");
    strcpy(Clit[8].Nome, "Leandro Luiz de Almeida");
    strcpy(Clit[8].Telefone, "(18)2668-5825");


    strcpy(Clit[9].CPF, "493.771.438-45");
    strcpy(Clit[9].Nome, "Wagner Luiz Pense");
    strcpy(Clit[9].Telefone, "(18)1937-2179");

    InsercDireta(Clit, TC); // Ordena os clientes preenchidos


	// Preenchendo carros

	Carros[0].CodCar = 5;
	strcpy(Carros[0].Modelo, "Fiat Uno");
	strcpy(Carros[0].Categoria,"Econômico");
	Carros[0].PrecoDia = 80.00;

	Carros[1].CodCar = 3;
	strcpy(Carros[1].Modelo, "VW Gol");
	strcpy(Carros[1].Categoria, "Econômico");
	Carros[1].PrecoDia = 95.00;

	Carros[2].CodCar = 17;
	strcpy(Carros[2].Modelo, "Chevrolet Onix");
	strcpy(Carros[2].Categoria, "Hatch");
	Carros[2].PrecoDia = 110.00;

	Carros[3].CodCar = 22;
	strcpy(Carros[3].Modelo, "VW Gol");
	strcpy(Carros[3].Categoria, "Econômico");
	Carros[3].PrecoDia = 95.00;

	Carros[4].CodCar = 15;
	strcpy(Carros[4].Modelo, "Toyota Corolla");
	strcpy(Carros[4].Categoria, "Sedan");
	Carros[4].PrecoDia = 150.00;

	Carros[5].CodCar = 46;
	strcpy(Carros[5].Modelo, "Honda HR-V");
	strcpy(Carros[5].Categoria, "SUV");
	Carros[5].PrecoDia = 180.00;

	Carros[6].CodCar = 37;
	strcpy(Carros[6].Modelo, "Mitsubishi L200");
	strcpy(Carros[6].Categoria, "Pickup");
	Carros[6].PrecoDia = 220.00;

	Carros[7].CodCar = 28;
	strcpy(Carros[7].Modelo, "Audi A3");
	strcpy(Carros[7].Categoria, "Luxo");
	Carros[7].PrecoDia = 350.00;

	Carros[8].CodCar = 49;
	strcpy(Carros[8].Modelo, "VW Virtus");
	strcpy(Carros[8].Categoria, "Sedan");
	Carros[8].PrecoDia = 145.00;

	Carros[9].CodCar = 10;
	strcpy(Carros[9].Modelo, "Chevrolet Camaro");
	strcpy(Carros[9].Categoria, "Esportivo");
	Carros[9].PrecoDia = 500.00;


	// Preenchendo Tabela locações
	strcpy(Locacoes[0].CPF, "195.901.258-40"); 
	Locacoes[0].CodCar = 5;
	Locacoes[0].QtdDias = 5;
	Locacoes[0].ValorLoc = 80.00 * Locacoes[0].QtdDias;

	strcpy(Locacoes[1].CPF, "936.649.248-78");
	Locacoes[1].CodCar = 3;
	Locacoes[1].QtdDias = 3;
	Locacoes[1].ValorLoc = 95.00 * Locacoes[1].QtdDias;

	strcpy(Locacoes[2].CPF, "024.815.148-74"); 
	Locacoes[2].CodCar = 17;
	Locacoes[2].QtdDias = 10;
	Locacoes[2].ValorLoc = 110.00 * Locacoes[2].QtdDias;

	strcpy(Locacoes[3].CPF, "341.000.208-13"); 
	Locacoes[3].CodCar = 22;
	Locacoes[3].QtdDias = 1;
	Locacoes[3].ValorLoc = 95.00 * Locacoes[3].QtdDias;

	strcpy(Locacoes[4].CPF, "051.159.728-24"); 
	Locacoes[4].CodCar = 15;
	Locacoes[4].QtdDias = 7;
	Locacoes[4].ValorLoc = 150.00 * Locacoes[4].QtdDias;

    // Adicionando mais locações para o mesmo CPF para testar o relatório
    strcpy(Locacoes[5].CPF, "195.901.258-40"); 
	Locacoes[5].CodCar = 46;
	Locacoes[5].QtdDias = 3;
	Locacoes[5].ValorLoc = 180.00 * Locacoes[5].QtdDias;

	strcpy(Locacoes[6].CPF, "195.901.258-40"); 
	Locacoes[6].CodCar = 37;
	Locacoes[6].QtdDias = 1;
	Locacoes[6].ValorLoc = 220.00 * Locacoes[6].QtdDias;

	strcpy(Locacoes[7].CPF, "195.901.258-40"); 
	Locacoes[7].CodCar = 28;
	Locacoes[7].QtdDias = 5;
	Locacoes[7].ValorLoc = 350.00 * Locacoes[7].QtdDias;

	strcpy(Locacoes[8].CPF, "848.384.258-05"); 
	Locacoes[8].CodCar = 49;
	Locacoes[8].QtdDias = 2;
	Locacoes[8].ValorLoc = 145.00 * Locacoes[8].QtdDias;

	strcpy(Locacoes[9].CPF, "493.771.438-45"); 
	Locacoes[9].CodCar = 10;
	Locacoes[9].QtdDias = 5;
	Locacoes[9].ValorLoc = 500.00 * Locacoes[9].QtdDias;

    BubbleSort2(Locacoes, TLL); // Ordena as locações preenchidas

	clrscr();
	gotoxy(30,12); printf("Tabelas Preenchidas!");
	Sleep(1500);

}

void CADAcliente(TpClientes Cli[TF], int &TL)
{
	char AuxCPF[15];
	int pos;
	clrscr();
    Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,11,1);
    gotoxy(30,3); textcolor(11); printf("CADASTRO DE CLIENTES");
	gotoxy(3,6); textcolor(3);printf("[ENTER com CPF vazio para voltar ao menu]\n\n");
	gotoxy(3,8); textcolor(11); printf("CPF: "); textcolor(15);
	fflush(stdin);
	gets(AuxCPF);
	while(TL<TF && strcmp(AuxCPF,"")!=0)
	{
		pos = BuscaCPF(Cli,TL,AuxCPF);

		if(pos == -1)
		{
			
			strcpy(Cli[TL].CPF,AuxCPF);
			gotoxy(3,9); textcolor(11);  printf("Nome: "); textcolor(15);
			fflush(stdin);
			gets(Cli[TL].Nome);
			gotoxy(3,10); textcolor(11); printf("Telefone: "); textcolor(15);
			fflush(stdin);
			gets(Cli[TL].Telefone);
			TL++;
			InsercDireta(Cli,TL);
            gotoxy(3,12); textcolor(2); printf("Cliente cadastrado com sucesso!");
            textcolor(11);
		}
		else{
		
            gotoxy(3,12);  textcolor(12); printf("ERRO: Cliente com este CPF ja esta cadastrado!");
            textcolor(11);
    	}

        getch();
        gotoxy(3,12); printf("                                                 ");
        gotoxy(3,8); printf("CPF:                         ");
        gotoxy(3,9); printf("Nome:                                                                  ");
        gotoxy(3,10); printf("Telefone:                         ");
        gotoxy(3,8); printf("CPF: ");
        fflush(stdin);
        gets(AuxCPF);
	}
}


void AltCliente(TpClientes Cli[TF],int TL){
	char aux[15];
	int pos;
	clrscr();
    Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,11,1);
    gotoxy(30,3); textcolor(11); printf("ALTERAR DADOS DO CLIENTE");
	if(TL == 0) {
        gotoxy(3,6); printf("Nenhum cliente cadastrado!");
    } else {
        gotoxy(3,6);textcolor(11); printf("Digite o CPF do cliente a ser alterado: ");textcolor(15);
        fflush(stdin);
        gets(aux);
		pos = BuscaCPF(Cli,TL,aux);
		if(pos != -1){
			gotoxy(3,8);textcolor(11); printf("Digite os novos dados do Cliente:");textcolor(15);
			gotoxy(3,9); textcolor(11); printf("CPF: ");textcolor(15);
			fflush(stdin);
			gets(Cli[pos].CPF);
			gotoxy(3,10);textcolor(11); printf("Nome: ");textcolor(15);
			fflush(stdin);
			gets(Cli[pos].Nome);
			gotoxy(3,11); textcolor(11); printf("Telefone: ");textcolor(15);
			fflush(stdin);
			gets(Cli[pos].Telefone);
            gotoxy(3,13); textcolor(2); printf("Dados alterados com sucesso!");textcolor(11);
		}
		else{
            gotoxy(3,8);  textcolor(12); printf("Cliente nao encontrado!");textcolor(11);
        }
	}
    getch();
}

void ExcluCliente(TpClientes Cli[TF], int &TL)
{
	char AuxCPF[15];
	int pos;
	clrscr();
	Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,12,1);
    gotoxy(32,3); textcolor(12); printf("EXCLUIR CLIENTE");

	if(TL == 0) {
        gotoxy(3,6); printf("Nenhum cliente cadastrado!");
    } else {
        gotoxy(3,6); textcolor(12); printf("Digite o CPF do cliente a ser excluido: "); textcolor(15);
        fflush(stdin);
        gets(AuxCPF);

        pos = BuscaCPF(Cli,TL,AuxCPF);

        if(pos == -1) {
            gotoxy(3,8); printf("Cliente nao existe!");
        } else {
            gotoxy(3,8);   printf("Dados do cliente:"); 
            gotoxy(3,9);   printf("CPF: %s", Cli[pos].CPF); 
            gotoxy(3,10);  printf("Nome: %s", Cli[pos].Nome); 
            gotoxy(3,11);  printf("Telefone: %s", Cli[pos].Telefone); 
            gotoxy(3,13);  printf("Confirmar exclusao? [S/N]");
            if(toupper(getche())== 'S') {
                for(int i=pos; i<TL-1; i++)
                    Cli[i] = Cli[i+1];
                TL--;
                gotoxy(3,15);  textcolor(2); printf("Cliente Excluido!");textcolor(15);
            } else {
                gotoxy(3,15); textcolor(12);printf("Exclusao cancelada.");textcolor(15);
            }
        }
    }
	getch();
}


void Relatteste(TpClientes Cli[TF],int TL)
{
	clrscr();
	Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,10,1);
    gotoxy(31,3); textcolor(10); printf("RELATORIO DE CLIENTES");
	int i=0;
	if(TL==0) {
		gotoxy(3,6); printf("Nenhum cliente cadastrado!");
    } else {
        int linha = 6;
		for(i=0; i<TL; i++)
		{
            if (linha + 4 > 24) { 
                gotoxy(3, 24); printf("Pressione para continuar..."); getch();
                clrscr();
                Moldura(1,1,80,25,14,1);
                Moldura(25,2,55,4,10,1);
                gotoxy(31,3); textcolor(10); printf("RELATORIO DE CLIENTES");
                linha = 6;
            }
			gotoxy(3, linha++); printf("CPF: %s", Cli[i].CPF);
            gotoxy(3, linha++); printf("Nome: %s", Cli[i].Nome);
            gotoxy(3, linha++); printf("Telefone: %s", Cli[i].Telefone);
			gotoxy(3, linha++); printf("------------------------------------");
		}
	}
	getch();
}


void CadCarros(TpCarros Car[TF+1], int &TL){
	int auxcod, busca;
	clrscr();
	Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,11,1);
    gotoxy(33,3); textcolor(11); printf("CADASTRAR CARRO");
	gotoxy(3,6); printf("[Codigo 0 para voltar ao menu]");
	gotoxy(3,8); printf("Codigo: "); textcolor(15);
	scanf("%d",&auxcod);

	while(TL<TF && auxcod != 0){
		busca = BuscacomSentinelaCod(Car,TL,auxcod);
		if(busca == -1){
			Car[TL].CodCar = auxcod;
			gotoxy(3,9); textcolor(11); printf("Modelo: "); textcolor(15);
			fflush(stdin); gets(Car[TL].Modelo);
			gotoxy(3,10);textcolor(11); printf("Categoria: "); textcolor(15);
			fflush(stdin); gets(Car[TL].Categoria);
			gotoxy(3,11); textcolor(11); printf("Preco diaria: R$ "); textcolor(15);
			scanf("%f",&Car[TL].PrecoDia);
			TL++;
            gotoxy(3,13); textcolor(2); printf("Carro cadastrado com sucesso!"); textcolor(15);
		}
	 	else{
	 	    gotoxy(3,13); textcolor(12);printf("ERRO: Carro com este codigo ja esta cadastrado!");textcolor(11);
	 	    getch();
		}
        getch();
        gotoxy(3,13); printf("                                                 ");textcolor(15);
        gotoxy(3,8); textcolor(11); printf("Codigo:          ");
        gotoxy(3,9); textcolor(11); printf("Modelo:                                           ");textcolor(15);
        gotoxy(3,10);textcolor(11);  printf("Categoria:                                        ");textcolor(15);
        gotoxy(3,11);textcolor(11);  printf("Preco diaria: R$          ");textcolor(15);
        gotoxy(3,8); textcolor(11); printf("Codigo: ");textcolor(15);
	    scanf("%d",&auxcod);
	}
}


void ExcluirCarros(TpCarros Car[TF+1], int &TL){ 
	int auxcod, i, busca;
	clrscr();
	Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,12,1);
    gotoxy(33,3); textcolor(12); printf("EXCLUIR CARRO");

    if (TL == 0) {
        gotoxy(3,6); printf("Nenhum carro cadastrado!");
    } else {
        gotoxy(3,6); printf("Digite o codigo do carro para excluir: ");
        scanf("%d", &auxcod);
        busca = BuscacomSentinelaCod(Car,TL,auxcod);

        if(busca == -1){
            gotoxy(3,8); printf("Carro nao existe!");
        } else {
            gotoxy(3,8); printf("Dados do Carro:");
            gotoxy(3,9); printf("Codigo: %d",Car[busca].CodCar);
            gotoxy(3,10); printf("Modelo: %s",Car[busca].Modelo);
            gotoxy(3,11); printf("Categoria: %s",Car[busca].Categoria);
            gotoxy(3,12); printf("Preco diaria: R$ %.2f",Car[busca].PrecoDia);
            gotoxy(3,14); printf("Confirmar Exclusao [S/N]: ");

            if(toupper(getche())== 'S'){
                for(i=busca; i<TL-1;i++)
                    Car[i] = Car[i+1];
                TL--;
                gotoxy(3,16); printf("Carro Excluido!");
            } else {
                gotoxy(3,16); printf("Exclusao cancelada.");
            }
        }
    }
    getch();
}

void AltCarros(TpCarros Carros[TF], int TL){
	clrscr();
	int pos,aux;
    Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,11,1);
    gotoxy(32,3); textcolor(11); printf("ALTERAR DADOS DO CARRO");

	if(TL == 0) {
		gotoxy(3,6); printf("Nenhum carro cadastrado!");
    } else {
       
        SelectionSort(Carros, TL); 
        gotoxy(3,6); printf("ATENCAO: A lista de carros foi ordenada por CODIGO para a busca.");
        gotoxy(3,7); printf("Digite o Codigo do Carro: ");textcolor(15);
	    scanf("%d",&aux);
		pos = BuscaBinaria(Carros,TL,aux);
		if(pos == -1) {
			gotoxy(3,9); printf("Carro nao encontrado!");
        } else {
			gotoxy(3,9);textcolor(11); printf("Digite os novos dados:");
			gotoxy(3,10);textcolor(11); printf("Modelo: ");textcolor(15);
			fflush(stdin);
			gets(Carros[pos].Modelo);
			gotoxy(3,11);textcolor(11); printf("Categoria: ");textcolor(15);
			fflush(stdin);
			gets(Carros[pos].Categoria);
			gotoxy(3,12); textcolor(11);printf("Preco diaria: R$ ");textcolor(15);
			scanf("%f",&Carros[pos].PrecoDia);
            gotoxy(3,14); textcolor(2);printf("Dados alterados com sucesso!");textcolor(15);
		}
	}
    getch();
}

void OrdenarCod(TpCarros Carros[TF], int TL){
	SelectionSort(Carros,TL);
	clrscr();
    Moldura(1,1,80,25,14,1);
    gotoxy(25,12); printf("Lista de Carros Ordenada por CODIGO!");
	getch();
}

void OrdenarModel(TpCarros Carros[TF],int TL){
	BubbleSort(Carros,TL);
	clrscr();
    Moldura(1,1,80,25,14,1);
	gotoxy(25,12); printf("Lista de Carros Ordenada por MODELO!");
	getch();
}

void RelaCarros(TpCarros Carros[TF], int TLCA){
	clrscr();
	Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,10,1);
    gotoxy(32,3); textcolor(10); printf("RELATORIO DE CARROS");
	int i;
	if(TLCA == 0){
		gotoxy(3,6); printf("Nenhum carro cadastrado!");
	}
	else{
        int linha = 6;
		for(i=0;i<TLCA;i++){
            if (linha + 5 > 24) { 
                gotoxy(3, 24); printf("Pressione para continuar..."); getch();
                clrscr();
                Moldura(1,1,80,25,14,1);
                Moldura(25,2,55,4,10,1);
                gotoxy(32,3); textcolor(10); printf("RELATORIO DE CARROS");
                linha = 6;
            }
			gotoxy(3, linha++); printf("Codigo do Carro: %d",Carros[i].CodCar);
			gotoxy(3, linha++); printf("Modelo: %s",Carros[i].Modelo);
			gotoxy(3, linha++); printf("Categoria: %s",Carros[i].Categoria);
			gotoxy(3, linha++); printf("Preco: R$ %.2f",Carros[i].PrecoDia);
            gotoxy(3, linha++); printf("----------------------------------------");
		}
	}
    getch();
}


void CadaLoc(TpLocacoes Loc[TF],TpCarros carros[TF+1], TpClientes clientes[TF], int &TLL, int TLC, int TLCA)
{
	char AuxCPF[20];
	int buscaCPF,buscaCar, AuxCod, QtdDias;
    clrscr();
    Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,11,1);
    gotoxy(31,3); textcolor(11); printf("CADASTRO DE LOCACOES");
    gotoxy(3,6); printf("[ENTER com CPF vazio para voltar]");
	gotoxy(3,8); printf("CPF do cliente: "); textcolor(15);
	fflush(stdin);
	gets(AuxCPF);
	while(TLL<TF && strcmp(AuxCPF,"") != 0)
	{
		buscaCPF = BuscaCPF(clientes,TLC,AuxCPF);

		if(buscaCPF != -1)
		{
			gotoxy(3,9); printf("Codigo do carro: ");textcolor(15);
			scanf("%d", &AuxCod);
			buscaCar = BuscacomSentinelaCod(carros,TLCA,AuxCod);

			if( buscaCar != -1){
                if(TLL<TF){
                    strcpy(Loc[TLL].CPF,AuxCPF);
                    Loc[TLL].CodCar = AuxCod;
                    gotoxy(3,10); printf("Quantidade de dias de locacao: "); textcolor(15);
                    scanf("%d",&QtdDias);
                    Loc[TLL].QtdDias = QtdDias;
                    Loc[TLL].ValorLoc = carros[buscaCar].PrecoDia * Loc[TLL].QtdDias;
                    TLL++;
                    BubbleSort2(Loc,TLL); 
                    gotoxy(3,12);textcolor(2); printf("Locacao cadastrada com sucesso!"); textcolor(11);
                } else {
                    gotoxy(3,12);textcolor(12); printf("ERRO: Limite maximo de locacoes atingido!");textcolor(11);
                }
			 } else {
				gotoxy(3,12); textcolor(12);printf("ERRO: Carro nao esta cadastrado!");textcolor(11);
             }
		 } else {
			gotoxy(3,12); textcolor(12);printf("ERRO: Cliente nao cadastrado! Cadastre-o primeiro.");textcolor(11);
       }
        getch();
        gotoxy(3,12); textcolor(11);printf("                                                          ");textcolor(15);
        gotoxy(3,8); textcolor(11);printf("CPF do cliente:                          ");textcolor(15);
        gotoxy(3,9);textcolor(11); printf("Codigo do carro:          ");
        gotoxy(3,10);textcolor(11); printf("Quantidade de dias de locacao:            ");textcolor(15);
        gotoxy(3,8); textcolor(11);printf("CPF do cliente: ");textcolor(15);
        fflush(stdin);
        gets(AuxCPF);
	}
}

void ExcluLoc(TpLocacoes Loc[TF], int &TLL)
{
	char AuxCPF[15];
	int pos;
	clrscr();
	Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,12,1);
    gotoxy(31,3); textcolor(12); printf("EXCLUSAO DE LOCACOES");

    if (TLL == 0) {
        gotoxy(3,6); printf("Nenhuma locacao cadastrada!");
    } else {
        gotoxy(3,6); printf("Digite o CPF do cliente da locacao a ser excluida: ");
        fflush(stdin);
        gets(AuxCPF);

        // A busca sequencial indexada exige que o vetor esteja ordenado.
        // BubbleSort2 na inserção já garante isso.
        pos = SeqIndex(Loc, TLL, AuxCPF);

        if(pos == -1) {
            gotoxy(3,8); printf("Locacao para este CPF nao existe!");
        } else {
            gotoxy(3,8); printf("Dados da locacao:");
            gotoxy(3,9); printf("CPF: %s", Loc[pos].CPF);
            gotoxy(3,10); printf("Codigo do carro: %d", Loc[pos].CodCar);
            gotoxy(3,11); printf("Quantidade de dias: %d", Loc[pos].QtdDias);
            gotoxy(3,12); printf("Valor da Locacao: R$ %.2f", Loc[pos].ValorLoc);
            gotoxy(3,14); printf("Confirmar exclusao? [S/N]");
            if(toupper(getche())== 'S') {
                for(int i=pos; i<TLL-1; i++)
                    Loc[i] = Loc[i+1];
                TLL--;
                gotoxy(3,16); printf("Locacao Excluida!");
            } else {
                gotoxy(3,16); printf("Exclusao cancelada.");
            }
        }
    }
	getch();
}
void AltLoc(TpLocacoes Loc[TF], TpCarros carros[TF+1], int TLL, int TLCA) {
    char auxCPF[15];
    int pos,buscaCar, auxCodCar;
	clrscr();
	Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,11,1);
    gotoxy(33,3); textcolor(11); printf("ALTERAR LOCACAO");

    if (TLL == 0) {
        gotoxy(3,6); printf("Nenhuma locacao cadastrada!");
	} else {
        gotoxy(3,6); printf("Digite o CPF da locacao a ser alterada: ");textcolor(15);
        fflush(stdin);
        gets(auxCPF);

        // A busca binária exige que o vetor esteja ordenado.
        // BubbleSort2 na inserção já garante isso.
        pos = BuscaBinaria2(Loc,TLL,auxCPF);

        if (pos != -1) {
            gotoxy(3,8); printf("Locacao encontrada! Digite os novos dados:");
            gotoxy(3,9);textcolor(11); printf("Codigo do carro: ");textcolor(15);
            scanf("%d", &auxCodCar);
            buscaCar = BuscacomSentinelaCod(carros,TLCA,auxCodCar);

            if (buscaCar != -1) {
                Loc[pos].CodCar = auxCodCar;
                gotoxy(3,10); textcolor(11);printf("Quantidade de dias: ");textcolor(15);
                scanf("%d", &Loc[pos].QtdDias);
                Loc[pos].ValorLoc = carros[buscaCar].PrecoDia * Loc[pos].QtdDias;
                gotoxy(3,12); textcolor(2);printf("Locacao alterada com sucesso!");textcolor(11);
            } else {
                gotoxy(3,12);textcolor(12); printf("ERRO: Carro nao encontrado! A locacao NAO foi alterada.");textcolor(11);
            }
       } else {
           gotoxy(3,8); textcolor(12);printf("Locacao para este CPF nao encontrada!");textcolor(11);
       }
    }
    getch();
}

void RelaLoc(TpLocacoes Loc[TF], int &TLL)
{
	clrscr();
	Moldura(1,1,80,25,14,1);
    Moldura(25,2,55,4,10,1);
    gotoxy(31,3); textcolor(10); printf("RELATORIO DE LOCACOES");
	int i=0;
	if(TLL==0) {
		gotoxy(3,6); printf("Nenhuma locacao cadastrada!");
    } else {
        int linha = 6;
		for(i=0;i<TLL;i++)
		{
            if (linha + 5 > 24) { 
                gotoxy(3, 24); printf("Pressione para continuar..."); getch();
                clrscr();
                Moldura(1,1,80,25,14,1);
                Moldura(25,2,55,4,10,1);
                gotoxy(31,3); textcolor(10); printf("RELATORIO DE LOCACOES");
                linha = 6;
            }
            gotoxy(3, linha++); printf("CPF: %s", Loc[i].CPF);
            gotoxy(3, linha++); printf("Codigo do carro: %d", Loc[i].CodCar);
            gotoxy(3, linha++); printf("Quantidade de dias: %d", Loc[i].QtdDias);
            gotoxy(3, linha++); printf("Valor da Locacao: R$ %.2f", Loc[i].ValorLoc);
            gotoxy(3, linha++); printf("------------------------------------");
		}
	}
	getch();
}

void RelatorioClientesMais3Locacoes(TpLocacoes Loc[TF], int TLL)
{
    clrscr();
    Moldura(1,1,80,25,14,1);
    Moldura(18,2,62,4,10,1);
    gotoxy(20,3); textcolor(10); printf("RELATORIO: CLIENTES COM MAIS DE 3 LOCACOES");

    if (TLL == 0) {
        gotoxy(3,6); printf("Nenhuma locacao cadastrada para gerar o relatorio.");
    } else {
        BubbleSort2(Loc, TLL);

        int cont = 1;
        int linha = 6;
        int encontrou = 0;

        for (int i = 1; i < TLL; i++) {
            if (strcmp(Loc[i].CPF, Loc[i-1].CPF) == 0) {
                cont++;
            } else {
                if (cont > 3) {
                    if (linha > 23) {
                        gotoxy(3, 24); printf("Pressione para continuar..."); getch();
                        clrscr();
                        Moldura(1,1,80,25,14,1);
                        Moldura(18,2,62,4,10,1);
                        gotoxy(20,3); textcolor(10); printf("RELATORIO: CLIENTES COM MAIS DE 3 LOCACOES");
                        linha = 6;
                    }
                    gotoxy(3, linha++);
                    printf("-> Cliente com CPF %s realizou %d locacoes.", Loc[i-1].CPF, cont);
                    encontrou = 1;
                }
                cont = 1;
            }
        }
        if (cont > 3) {
             if (linha > 23) {
                gotoxy(3, 24); printf("Pressione para continuar..."); getch();
                clrscr();
                Moldura(1,1,80,25,14,1);
                Moldura(18,2,62,4,10,1);
                gotoxy(20,3); textcolor(10); printf("RELATORIO: CLIENTES COM MAIS DE 3 LOCACOES");
                linha = 6;
            }
            gotoxy(3, linha++);
            printf("-> Cliente com CPF %s realizou %d locacoes.", Loc[TLL-1].CPF, cont);
            encontrou = 1;
        }

        if (!encontrou) {
            gotoxy(3,6); printf("Nenhum cliente realizou mais de 3 locacoes.");
        }
    }
    getch();
}

void RelatorioLocacoesAcimaValor(TpLocacoes Loc[TF], int TLL)
{
    float limite;
    int i, encontrou = 0;
    clrscr();
    Moldura(1,1,80,25,14,1);
    Moldura(20,2,60,4,10,1);
    gotoxy(22,3); textcolor(10); printf("RELATORIO: LOCACOES ACIMA DE UM VALOR");

    if (TLL == 0) {
        gotoxy(3,6); printf("Nenhuma locacao cadastrada para gerar o relatorio.");
    } else {
        gotoxy(3,6); printf("Digite o valor minimo para a locacao: R$ ");
        scanf("%f", &limite);

        int linha = 8;
        for(i=0; i<TLL; i++)
        {
            if(Loc[i].ValorLoc > limite)
            {
                encontrou = 1;
                if (linha + 4 > 24) {
                    gotoxy(3, 24); printf("Pressione para continuar..."); getch();
                    clrscr();
                    Moldura(1,1,80,25,14,1);
                    Moldura(20,2,60,4,10,1);
                    gotoxy(22,3); textcolor(10); printf("RELATORIO: LOCACOES ACIMA DE UM VALOR");
                    linha = 8;
                }
                gotoxy(3, linha++); printf("CPF: %s", Loc[i].CPF);
                gotoxy(3, linha++); printf("Codigo do carro: %d", Loc[i].CodCar);
                gotoxy(3, linha++); printf("Valor da Locacao: R$ %.2f", Loc[i].ValorLoc);
                gotoxy(3, linha++); printf("------------------------------------");
            }
        }

        if(!encontrou){
            gotoxy(3,8); printf("Nenhuma locacao encontrada com valor acima de R$ %.2f", limite);
        }
    }
    getch();
}


void RelatorioCategoria(TpCarros Carros[TF], int TL){
	char aux[30]; 
	int i, encontrou = 0;

	clrscr();
	Moldura(1,1,80,25,14,1);
	Moldura(25,2,60,4,10,1); 
	gotoxy(30,3); textcolor(10); printf("RELATORIO POR CATEGORIA");

	if(TL == 0){
		gotoxy(3,6); printf("Nenhum carro cadastrado.");
	}
	else{
		
		gotoxy(3,6); printf("Digite a categoria que deseja buscar: ");
		fflush(stdin); 
		gets(aux);

		int linha = 8; 

		for (i = 0; i < TL; i++)
		{
			if (stricmp(Carros[i].Categoria, aux) == 0)
			{
				encontrou = 1; 

                if (linha + 5 > 24) {
                    gotoxy(3, 24); printf("Pressione para continuar..."); getch();
                    clrscr();
                    Moldura(1,1,80,25,14,1);
                    Moldura(25,2,60,4,10,1);
                    gotoxy(30,3); textcolor(10); printf("RELATORIO POR CATEGORIA");
                    linha = 8;
                }

				gotoxy(3, linha++); printf("Codigo do Carro: %d", Carros[i].CodCar);
				gotoxy(3, linha++); printf("Modelo: %s", Carros[i].Modelo);
				gotoxy(3, linha++); printf("Categoria: %s", Carros[i].Categoria);
				gotoxy(3, linha++); printf("Preco: R$ %.2f", Carros[i].PrecoDia);
				gotoxy(3, linha++); printf("----------------------------------------");
			}
		}

		if (encontrou == 0) { 
			gotoxy(3,8); printf("Nenhum carro encontrado para a categoria '%s'.", aux);
		}
	}
	getch(); 
}

void RelatorioCompleto(TpLocacoes Loc[TF], TpCarros Carros[TF], int TLL, int TLCA){
	char aux[15]; 
	int i, j, encontrou = 0;
	 
	clrscr();
	Moldura(1,1,80,25,14,1);
	Moldura(25,2,60,4,10,1); 
	gotoxy(30,3); textcolor(10); printf("RELATORIO COMPLETO");

	if(TLL == 0){
		gotoxy(3,6); printf("Nenhuma locacao cadastrada.");
	}
	else{
		
		gotoxy(3,6); printf("Digite o CPF que deseja buscar: ");
		fflush(stdin); 
		gets(aux);

		int linha = 8; 

		for (i = 0; i < TLL; i++)
		{
			if (stricmp(Loc[i].CPF, aux) == 0)
			{
				encontrou = 1; 

                if (linha + 8 > 24) {
                    gotoxy(3, 24); printf("Pressione para continuar..."); getch();
                    clrscr();
                    Moldura(1,1,80,25,14,1);
                    Moldura(25,2,60,4,10,1);
                    gotoxy(30,3); textcolor(10); printf("RELATORIO POR CLIENTE");
                    linha = 8;
                }
				gotoxy(3, linha++); printf("Quantidade de dias: %d",Loc[i].QtdDias);
				gotoxy(3, linha++); printf("Valor da Locacao: R$%.2f",Loc[i].ValorLoc);
				for(j=0;j<TLCA;j++){
					if(Loc[i].CodCar == Carros[j].CodCar){
					gotoxy(3, linha++); printf("Codigo do Carro: %d", Carros[j].CodCar);
					gotoxy(3, linha++); printf("Modelo: %s", Carros[j].Modelo);
					gotoxy(3, linha++); printf("Categoria: %s", Carros[j].Categoria);
					gotoxy(3, linha++); printf("Preco: R$ %.2f", Carros[j].PrecoDia);
					gotoxy(3, linha++); printf("----------------------------------------");
					}
				}
			}
		}

		if (encontrou == 0) { 
			gotoxy(3,8); printf("Nenhuma locacao encontrada para o CPF: '%s'.", aux);
		}
	}
	getch(); 
}

void conteudo(){
	
	TpClientes TabClientes[TF];
	TpCarros TabCarros[TF+1]; // +1 para sentinela
	TpLocacoes TabLocacoes[TF];
	int TLC=0, TLCA=0, TLL=0;
	char op;
	do
	{
		clrscr();
        // Moldura Principal
		Moldura(1,1,80,25,15,9);
		Moldura(28,2,52,4,15,1);
		gotoxy(32,3); textcolor(15); printf("MENU PRINCIPAL");

        // --- Seção Clientes ---
        Moldura(4, 5, 26, 12, 14, 1);
        gotoxy(11, 6); printf("CLIENTES");
        gotoxy(6, 8); printf("[A] Cadastrar");
        gotoxy(6, 9); printf("[B] Alterar");
        gotoxy(6, 10); printf("[C] Excluir");
        gotoxy(6, 11); printf("[D] Relatorio");

        // --- Seção Carros ---
        Moldura(29, 5, 51, 14, 14, 1);
        gotoxy(38, 6); printf("CARROS");
        gotoxy(31, 8); printf("[E] Cadastrar");
        gotoxy(31, 9); printf("[F] Alterar");
        gotoxy(31, 10); printf("[G] Excluir");
        gotoxy(31, 11); printf("[H] Relatorio");
        gotoxy(31, 12); printf("[I] Ordenar Codigo");
        gotoxy(31, 13); printf("[J] Ordenar Modelo");


        // --- Seção Locações ---
        Moldura(54, 5, 76, 12, 14, 1);
        gotoxy(61, 6); printf("LOCACOES");
        gotoxy(56, 8); printf("[K] Cadastrar");
        gotoxy(56, 9); printf("[L] Alterar");
        gotoxy(56, 10); printf("[M] Excluir");
        gotoxy(56, 11); printf("[N] Relatorio");

        // --- Opções Gerais e Relatórios Especiais ---
        Moldura(4, 15, 76, 21, 10, 1);
        gotoxy(29, 16); textcolor(10); printf("RELATORIOS ESPECIAIS E GERAIS");
        gotoxy(6, 18); printf("[O] Clientes com mais de 3 Locacoes");
        gotoxy(6, 19); printf("[P] Locacoes acima de um Valor");
        gotoxy(6, 20); printf("[Q] Listar carros por Categoria");
        gotoxy(45, 18); printf("[R] Listar locacoes por Cliente");
        gotoxy(45, 19); printf("[S] Preencher Tabelas");
        gotoxy(45, 20); printf("[ESC] Sair do Programa");
        textcolor(15);


        // --- Entrada do Usuário ---
        gotoxy(32, 23); printf("Escolha uma opcao:");
		op = toupper(getche());

		switch(op) {
            // Clientes
            case 'A': CADAcliente(TabClientes, TLC); break;
            case 'B': AltCliente(TabClientes, TLC); break;
            case 'C': ExcluCliente(TabClientes, TLC); break;
            case 'D': Relatteste(TabClientes, TLC); break;

            // Carros
            case 'E': CadCarros(TabCarros, TLCA); break;
            case 'F': AltCarros(TabCarros, TLCA); break;
            case 'G': ExcluirCarros(TabCarros, TLCA); break;
            case 'H': RelaCarros(TabCarros, TLCA); break;
            case 'I': OrdenarCod(TabCarros, TLCA); break;
            case 'J': OrdenarModel(TabCarros, TLCA); break;

            // Locações
            case 'K': CadaLoc(TabLocacoes, TabCarros, TabClientes, TLL, TLC, TLCA); break;
            case 'L': AltLoc(TabLocacoes, TabCarros, TLL, TLCA); break;
            case 'M': ExcluLoc(TabLocacoes, TLL); break;
            case 'N': RelaLoc(TabLocacoes, TLL); break;

			// Relatórios Especiais
            case 'O': RelatorioClientesMais3Locacoes(TabLocacoes, TLL); break;
            case 'P': RelatorioLocacoesAcimaValor(TabLocacoes, TLL); break;
            case 'R': RelatorioCompleto(TabLocacoes, TabCarros, TLL, TLCA); break;
            case 'Q': RelatorioCategoria(TabCarros, TLCA); break;
            case 'S': PrencherTabelas(TabClientes, TabCarros, TabLocacoes, TLC, TLCA, TLL); break;
        }

	}while(op!=27);

    clrscr();
    gotoxy(35,12); printf("Saindo...");
    Sleep(1000);
	
}


int main(void)
{
	conteudo();
	return 0;
}
