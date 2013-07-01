#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct estructuraPozo {
	char idPozo[50];
	float x;
	float y;
	float radio;
};

struct estructuraTanque {
	char idTanque[50];
	float x;
	float y;
	float radio;
	char direccion[2];
	char idPozo[50];
	float distancia;
};

bool intersectar(struct estructuraTanque *t, struct estructuraPozo *p, struct estructuraTanque *final){
bool x=false;
bool y=false;	
	if ((strcmp(t->direccion,"H") == 0 )){
		if ( (t->x <= p->x - p->radio) && ((t->x + 100)>=(p->x + p->radio)) ){
			final->x = p->x;
			x=true;
		}
		if ( (t->y >= (p->y - p->radio)) && ((t->y)<=((p->y)+(p->radio)))){
			final->y = p->y;
			y=true;
		}
		final->distancia = (p->x - t->x) - sqrt(pow(p->radio,2) - pow((t->y)-(p->y),2));
	}

	if ((strcmp(t->direccion,"V") == 0 )){
			if ( (t->x >= p->x - p->radio) && ((t->x)<=(p->x + p->radio)) ){
			final->x = p->x;
			x=true;
		}
		if ( (t->y <= (p->y - p->radio)) && ((t->y + 100 )>=((p->y)+(p->radio)))){
			final->y = p->y;
			y=true;
		}
		final->distancia = (p->y - t->y) - sqrt(pow(p->radio,2) - pow((t->x)-(p->x),2));
	}
	if (x && y){
		return true;
	}else
		return false;
}

int main (){
	FILE* handler=NULL;
	char caracter = ' ';
	char aux[50];
	int i = 0;
	char espacio[4] = " \n\t";
	char *ptr;
	struct estructuraPozo p[10];
	struct estructuraTanque t[10], final[1];

	//parseo de parametros POZO
	handler = fopen("pozos.txt","r");
	while (!feof(handler)){
		fgets(aux,50,handler);
		ptr = strtok(aux, espacio);
		strcpy(p[i].idPozo,ptr);
		ptr = strtok(NULL, espacio);
		p[i].x = atof(ptr);
		ptr = strtok(NULL, espacio);
		p[i].y = atof(ptr);
		ptr = strtok(NULL, espacio);
		p[i].radio = atof(ptr);
		i++;
	}
	int maxPozo = i;
	i=0;
	fclose(handler);

	//parseo de parametros TANQUE
	handler = fopen("tanques.txt","r");
	while (!feof(handler)){
		fgets(aux,50,handler);
		ptr = strtok(aux, espacio);
		strcpy(t[i].idTanque,ptr);
		ptr = strtok(NULL, espacio);
		t[i].x = atof(ptr);
		ptr = strtok(NULL, espacio);
		t[i].y = atof(ptr);
		ptr = strtok(NULL, espacio);
		strcpy(t[i].direccion,ptr);
		t[i].distancia = 100;
		i++;
	}
	int maxTanque = i;
	fclose(handler);

	//intersectar
	int j=0;
	int f=0;
	for (i=0;i<maxTanque;i++){
		for(j=0;j<maxPozo;j++){
			if (intersectar(&t[i],&p[j],&final[0])){
				if (final[0].distancia < t[i].distancia){
					t[i].distancia = final[0].distancia;
					strcpy(t[i].idPozo,p[j].idPozo);
				}
			}
		}
		j=0;
	}

	// imprimir de menor a mayor las distancias
	struct estructuraTanque estru;
	estru.distancia = 99;
	int exit=maxTanque;
	int valor=0;

	while (exit !=0){
		for (i=0;i<maxTanque;i++){
			if (t[i].distancia < estru.distancia){
				estru = t[i];
				valor = i;
			}
		}
		if (estru.distancia < 99){
			printf("Id Pozo: %s\n",estru.idPozo);
			printf("Id Tanque: %s\n",estru.idTanque);
			printf("Distancia: %f\n\n",estru.distancia);
		}
		t[valor].distancia = 100;
		estru.distancia = 100;
		exit--;
	}
return 0;
}
