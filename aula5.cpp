#include <stdio.h>

#define PI 3.14

float area(int r);

int main(void){
	int raio;
	float area_esfera;
	printf("Digite o raio da esfera: ");
	scanf("%d",&raio);
	area_esfera = area(raio);
	printf("A area da esfera e %.2f",area_esfera);
}

float area(int r)
{
	return(4*PI*r*r);
}
