#include <stdio.h>

int main()
{
	int mat[20][15], i, j, liv=0, ocup=0;
	printf("Preencha para cada poltrona\n1 - Reservado\n0 - Nao reservado\n");
	for(i=0; i<20; i++){
		for(j=0; j<15; j++){
			printf("Poltrona[%d][%d]\n",i,j);
			scanf("%d",&mat[i][j]);
			if(mat[i][j] == 0)
				liv++;
			else
				ocup++;
		}
	}
	printf("    Reservas finalizada!\n");
	printf("------------------------------\n");
	printf("Poltronas livres: %d\nPoltronas ocupadas: %d\n",liv,ocup);
	printf("------------------------------\n");
	printf("Mapa de ocupacao das poltronas\n");
	printf("------------------------------\n");
	for(i=0; i<20; i++){
		printf("\n");
		for(j=0; j<15; j++){
			printf("%d ",mat[i][j]);
		}
	}
	printf("\n------------------------------\n");
	printf("Verificacao da poltrona\n");
	printf("Digite a fila:\n");
	scanf("%d",&i);
	printf("Digite a coluna:\n");
	scanf("%d",&j);
	if(mat[i][j] == 1)
		printf("Poltrona reservada\n");
	else
		printf("Poltrona desocupada\n");
	return 0;
}

