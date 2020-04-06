#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define TAM 20

struct pila{
	int v[TAM];
	int ID[TAM];
	int s;
};

struct state{
	int value;
	int ID;
	int stack;
};

bool Pilavacia(pila *x){
	return((x->s) < 0);
}

bool Pilallena(pila *x){
	return((x->s) >= (TAM - 1));
}

state Sacar(pila *x){
	state devolucion;

	if(!Pilavacia(x)){
		int temp;
		temp = x->s--;
		x->ID[temp]++;
		devolucion.ID = x->ID[temp];
		devolucion.value = x->v[temp];
		return(devolucion);
	}
	else{
		printf("\nPila Vacia.\n");
	}

}

void refreshPile(pila *x){
	for(int i = (1 + x->s); i < TAM; i++){
		x->v[i] = 0;
	}
}

bool Empujar(pila *x, int data){
	if(!Pilallena(x)){
		int temp;
		temp = ++x->s;
		x->v[temp] = data;
		return(1);
	}
	else{
		printf("\nPila Llena.\n");
		return(0);
	}
}

void printPile(pila *x){
	for(int k = (-1 + TAM); k >= 0; k--){
			printf("posicion: %d , Patente: %d\n", k, x->v[k]);
	}
	printf("\n");
}

state readPile(pila *x){
	state lectura;
	lectura.stack = x->s;
	lectura.value = x->v[x->s];
	lectura.ID = x->ID[x->s];
	return(lectura);
}


pila parking, parkaux;
int listaPatentes[TAM];

state autoSacado;

//funcion para no repetir patentes
bool repetido(int w, int vector[]){
	for(int a = 0; a < TAM; a++){
		return(w == vector[a]);
	}
	return(0);
}

void cargarParking(){
	int cont = 0, j;
	srand(time(NULL));
// generamos las patentes
	while(cont < TAM){
		j = (100 + rand() % (1000 - 100));
		if(!repetido(j, listaPatentes)){
			listaPatentes[cont] = j;
			cont++;
		}
	}
//llenamos el estacionamiento
	for(int i = 0; i < TAM; i++){
		Empujar(&parking, listaPatentes[i]);
	}

	system("cls");
}
void meterAuto(int patt)
{
	state autoIn;
	int copyParking[TAM];
	bool equis = 0, de = 0;

	autoIn.ID = 0;
	autoIn.value = 0;

	for(int i=0; i<TAM; i++)
	{
		copyParking[i] = parking.v[i];
	}
	while(equis == 0)
	{
		autoIn.value = patt;
		for(int i = 0; i<TAM; i++)
		{
			if(autoIn.value == copyParking[i])
			{
				de = 1;
			}
		}
		if(de)
		{
			equis = 0;

		}
		if(!de)
		{
			equis = 1;
		}
	}
	Empujar(&parking, autoIn.value);
}
state sacarAuto(int patente)
{
	state devolucion;
	while(patente != readPile(&parking).value)
	{
		Empujar(&parkaux, Sacar(&parking).value);
	}
	devolucion = Sacar(&parking);
	while(!Pilavacia(&parkaux))
	{
		Empujar(&parking, Sacar(&parkaux).value);
	}
	return(devolucion);
}

main(){
	int patSclt, joa, cont, pat;

	while(Empujar(&parking, 0));//null
	while(Empujar(&parkaux, 0));//null

	parking.s = -1;
	parkaux.s = -1;

	system("cls");

	cargarParking();

	while(1){


		printf("\n");
		printf("El estacionamiento esta de la siguiente forma: \n");
		refreshPile(&parking);
		printPile(&parking);

		if(Pilallena(&parking))
		{
			printf("Estacionamiento lleno\n");
			printf("ingrese la patente del auto para retirar: ");
			scanf("%d", &patSclt);
   			printf("\n");
   			autoSacado = sacarAuto(patSclt);
   			printf("Se saco el auto %d \n", autoSacado.value);
   			printf("su auto se reubico %d veces \n", (autoSacado.ID-1));
			getchar();
			getchar();
		}
		if(Pilavacia(&parking))
		{
			printf("Estacionamiento vacio \n");
			getch();
			printf("ingresar patente: ");
			scanf("&d", pat);
			meterAuto(pat);
			printf("Se ingreso el auto : %d  \n", pat);
			getch();
		}
		if(!Pilavacia(&parking) && !Pilallena(&parking))
		{
			printf("Hay espacio en el Estacionamiento \n");
			printf("1. Ingresar auto \n");
			printf("2. Sacar auto \n");
            scanf("%d", &cont);
            if(cont == 1)
            {
				printf("ingresar patente: ");
				scanf("%d", &pat);
   				meterAuto(pat);
				printf("Se ingreso el auto : %d  \n", pat);
    getch();
			}
			if(cont == 2)
			{
			printf("ingrese la patente del auto para retirar: ");
			scanf("%d", &patSclt);
   			printf("\n");
   			autoSacado = sacarAuto(patSclt);
   			printf("Se saco el auto %d \n", autoSacado.value);
   			printf("su auto se reubico %d veces \n", (autoSacado.ID-1));
      getch();
			}
		}

		system("cls");
	}
}

