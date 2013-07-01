#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pared.h"
#include "bala.h"


int intersectar(structBala* b,structPared* p){
int x=0;//false
int y=0;//false
	if ((b->x) < (p->x)){
		x=1;//true
	}
	if ((b->y > p->y) && ((b->y) < (p->y + p->altura))){
		y=1;//true
	}
	if (x==1 && y==1){
		return 1;
	}else return 0;
}

int main(int argc, char* argv[])
{
	FILE* handlerPared;
	FILE* handlerBala;
	char aux[50]="\0";
	char espacio[4] = " \n\t";
	char *ptr;
	structPared pared[50];
	structBala bala[50];
	structPared paredAuxiliar[1];
	int i;
	int j;
	int k;
	int maxBala;
	int maxPared;

	for (i=0;i<50;i++)
	{
		bala[i].pared1[0] = '\0';
		bala[i].pared2[0] = '\0';
		bala[i].pared3[0] = '\0';
		bala[i].pared4[0] = '\0';
		bala[i].pared5[0] = '\0';
	}
	
	//PARSEO de archivos
	i=0;
	handlerPared = fopen("pared.txt","r");
	while (!feof(handlerPared)){
		fgets(aux,50,handlerPared);
		ptr = strtok(aux, espacio);
		strcpy(pared[i].id,ptr);
		ptr = strtok(NULL, espacio);
		pared[i].x = atof(ptr);
		ptr = strtok(NULL, espacio);
		pared[i].y = atof(ptr);
		ptr = strtok(NULL, espacio);
		pared[i].altura = atof(ptr);
		ptr = strtok(NULL, espacio);
		pared[i].energia = atoi(ptr);
		i++;
	}

	maxPared= i;
	fclose(handlerPared);

	i=0;
	handlerBala = fopen("bala.txt","r");
	while (!feof(handlerBala)){
		fgets(aux,50,handlerBala);
		ptr = strtok(aux, espacio);
		strcpy(bala[i].id,ptr);
		ptr = strtok(NULL, espacio);
		bala[i].x = atof(ptr);
		ptr = strtok(NULL, espacio);
		bala[i].y = atof(ptr);
		ptr = strtok(NULL, espacio);
		bala[i].energia = atoi(ptr);
		i++;
	}

	maxBala= i;
	fclose(handlerBala);
//FIN PARSEO de archivos

//ORDENO paredes	

	j=0;
	for(i=0;i<maxPared;i++){
		for(j=i+1;j<maxPared;j++){
			if (pared[j].x < pared[i].x){
			paredAuxiliar[0] = pared[j];
			pared[j] = pared[i];
			pared[i] = paredAuxiliar[0];
			}
		}
		j=i+2;
	}
//FIN ORDENO paredes
	
//RECORRO lista balas	
	k=0;
	for (i=0;i<maxBala;i++)
	{
		for (j=0;j<maxPared;j++){
			if (intersectar(&bala[i],&pared[j]) == 1)
			{
				k++;
				if (k==1) strcpy(bala[i].pared1,pared[j].id);
				if (k==2) strcpy(bala[i].pared2,pared[j].id);
				if (k==3) strcpy(bala[i].pared3,pared[j].id);
				if (k==4) strcpy(bala[i].pared4,pared[j].id);
				if (k==5) strcpy(bala[i].pared5,pared[j].id);
				bala[i].energia = bala[i].energia - pared[j].energia;
				if (bala[i].energia <= 0){
					j=maxPared;
				}
			}
		}
		k=0;
		j=0;
	}
//FIN RECORRO lista balas

//IMPRIMO balas
	for (i=0;i<maxBala;i++){
		printf ("Id Bala: %s\n",bala[i].id);
		printf ("Pos Inicial Bala (x): %f\n",bala[i].x);
		printf ("Pos Inicial Bala (y): %f\n",bala[i].y);
		if (bala[i].pared1[0] != '\0') printf ("Pared atravezada: %s\n", bala[i].pared1);
		if (bala[i].pared2[0] != '\0') printf ("Pared atravezada: %s\n", bala[i].pared2);
		if (bala[i].pared3[0] != '\0') printf ("Pared atravezada: %s\n", bala[i].pared3);
		if (bala[i].pared4[0] != '\0') printf ("Pared atravezada: %s\n", bala[i].pared4);
		if (bala[i].pared5[0] != '\0') printf ("Pared atravezada: %s\n", bala[i].pared5);
	}
//FIN IMPRIMO balas

	return 0;
}
