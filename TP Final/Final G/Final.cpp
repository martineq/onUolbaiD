#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct estructura {
	char idRec[50];
	float xInfIzq;
	float yInfIzq;
	float xSupDer;
	float ySupDer;
	float area;
	float distancia;
	char idRec1[50];
	char idRec2[50];
	char idRec3[50];
};

bool intersectar(struct estructura *q, struct estructura *w, struct estructura *final){
	if (q->yInfIzq <= w->yInfIzq){
		final->yInfIzq = w->yInfIzq;
	}else final->yInfIzq = q->yInfIzq;
	if (q->xInfIzq <= w->xInfIzq){
		final->xInfIzq = w->xInfIzq;
	}else final->xInfIzq = q->xInfIzq;
	if (q->xSupDer <= w->xSupDer){
		final->xSupDer = q->xSupDer;
	}else final->xSupDer = w->xSupDer;
	if (q->ySupDer <= w->ySupDer){
		final->ySupDer = q->ySupDer;
	}else final->ySupDer = w->ySupDer;
	if ((final->xSupDer - final->xInfIzq == 0) || (final->ySupDer - final->yInfIzq == 0)){
		return false;
	}else
		return true;
}

int main (){
	FILE* handler=NULL;
	char caracter = ' ';
	char aux[50];
	int i = 0;
	char espacio[4] = " \n\t";
	char *ptr;
	struct estructura s[10], final[10];

	//parseo de parametros
	handler = fopen("prueba.txt","r");
	while (!feof(handler)){
		fgets(aux,50,handler);
		ptr = strtok(aux, espacio);
		strcpy(s[i].idRec,ptr);
		ptr = strtok(NULL, espacio);
		s[i].xInfIzq = atof(ptr);
		ptr = strtok(NULL, espacio);
		s[i].yInfIzq = atof(ptr);
		ptr = strtok(NULL, espacio);
		s[i].xSupDer = atof(ptr);
		ptr = strtok(NULL, espacio);
		s[i].ySupDer = atof(ptr);
		i++;
	}
	int max = i;
	fclose(handler);

	//intersectar
	int j=0;
	int k=0;
	int f=0;
	for (i=0;i<max;i++)
	{
		for(j=i+1;j<max;j++)
		{
			if (intersectar(&s[i],&s[j],&final[f]))
			{
				for(k=j+1;k<max;k++){
					if (intersectar(&final[f],&s[k],&final[f])){
						strcpy(final[f].idRec1,s[i].idRec);
						strcpy(final[f].idRec2,s[j].idRec);
						strcpy(final[f].idRec3,s[k].idRec);
						final[f+1] = final[f];
					f++;
					}
				}
				k=0;
			}
		}
		j=0;
	}
	//calcular area
	for (i=0;i<f;i++){
		final[i].area = ((final[i].ySupDer)-(final[i].yInfIzq)) * ((final[i].xSupDer)-(final[i].xInfIzq));
	}
	//calcular distacia a origen
	for (i=0;i<f;i++){
		final[i].distancia = sqrt(pow(final[i].ySupDer,2) + pow(final[i].xInfIzq,2));
	}
	// imprimir de menor a mayor las distancias
	struct estructura estru;
	estru.distancia = 100;
	int exit=f;
	int valor=0;

	while (exit !=0){
		for (i=0;i<f;i++){
			if (final[i].distancia < estru.distancia){
				estru = final[i];
				valor = i;
			}
		}
		printf("Distancia: %f\n",estru.distancia);
		printf("Area: %f\n",estru.area);
		printf("Id_Rec: %s\n",estru.idRec1);
		printf("Id_Rec: %s\n",estru.idRec2);
		printf("Id_Rec: %s\n\n",estru.idRec3);
		final[valor].distancia = 100;
		estru.distancia = 100;
		exit--;
	}
return 0;
}