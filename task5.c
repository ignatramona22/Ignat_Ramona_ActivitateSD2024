#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SalonMeu Salon;
typedef struct Nod Nod;

struct SalonMeu
{
	char* nume;
	int nrAngajati;
	float salarii;
};

struct Nod
{
	Salon info;
	Nod* next;
};

Salon initializareSalon(const char* nume, int nrAngajati, float salarii)
{
	Salon salon;
	salon.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(salon.nume, nume);
	salon.nrAngajati = nrAngajati;
	salon.salarii = salarii;
	return salon;
}

Nod* inserareInceput(Salon s, Nod* cap)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->next = cap;
	nou->info = initializareSalon(s.nume, s.nrAngajati, s.salarii);
	return nou;
}



void afisareSalon(Salon s)
{
	printf("Salonul %s are un numar de %i angajati ce primesc un salariu de %5.2f RON lunar\n", s.nume, s.nrAngajati, s.salarii);
}

void afisareVectorSaloane(Salon* s, int nrSaloane)
{
	if (s != NULL)
	{
		for (int i = 0; i < nrSaloane; ++i)
		{
			afisareSalon(s[i]);
		}
	}
}
void afisareLista(Nod* lista)
{
	while (lista != NULL)
	{
		afisareSalon(lista->info);
		lista = lista->next;
	}
}

void stergeNodPozitie(Nod** lista, int pozitie)
{
	Nod* nodCurent = *lista;
	Nod* nodAnterior = NULL;

	for (int i = 0; i < pozitie && nodCurent != NULL; ++i)
	{
		nodAnterior = nodCurent;
		nodCurent = nodCurent->next;
	}

	if (nodCurent != NULL)
	{
		if (nodAnterior == NULL)
		{
			*lista = nodCurent->next;
		}
		else
		{
			nodAnterior->next = nodCurent->next;
		}
		free(nodCurent->info.nume);
		free(nodCurent);
	}

}

void inserareFinal(Nod** lista, Salon s)
{
	if ((*lista) == NULL) {
		(*lista) = inserareInceput(s, *lista);
	}
	else {
		Nod* curent = (*lista);
		while (curent->next != NULL) {
			curent = curent->next;
		}
		Nod* n = (Nod*)malloc(sizeof(Nod));
		n->info = initializareSalon(s.nume, s.nrAngajati, s.salarii); //deep copy
		n->next = NULL;
		curent->next = n;
	}
}

void inserareSortata(Nod** cap, Salon s)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->info = s;
	nou->next = NULL;

	if (*cap == NULL || strcmp(s.nume, (*cap)->info.nume))
	{
		nou->next = *cap;
		*cap = nou;
		return;
	}

	Nod* curent = *cap;
	while (curent->next != NULL && strcmp(s.nume, curent->next->info.nrAngajati) >= 0)
	{
		curent = curent->next;
	}

	nou->next = curent->next;
	curent->next = nou;
}

Salon* salveazaInVector(Nod* cap, int* dim, int prag)
{
	*dim = 0;

	Nod* nodCurent = cap;
	while (nodCurent != NULL)
	{
		if (nodCurent->info.nrAngajati >= prag)
		{
			(*dim)++;
		}
		nodCurent = nodCurent->next;
	}

	Salon* vector = malloc(sizeof(Salon) * (*dim));

	nodCurent = cap;
	int index = 0;
	while (nodCurent != NULL)
	{
		if (nodCurent->info.nrAngajati >= prag)
		{
			vector[index] = initializareSalon(nodCurent->info.nume, nodCurent->info.nrAngajati, nodCurent->info.salarii);
			index++;
		}
		nodCurent = nodCurent->next;
	}
	return vector;
}
void interschimbareElemente(Nod* cap, int pozitie1, int pozitie2)
{
	Nod* nod1 = cap;
	Nod* nod2 = cap;
	Salon temp;
	for (int i = 0; i < pozitie1 && nod1 != NULL; ++i)
		nod1 = nod1->next;

	for (int i = 0; i < pozitie2 && nod2 != NULL; ++i)
		nod2 = nod2->next;

	if (nod1 != NULL && nod2 != NULL && nod1 != nod2)
	{
		temp = nod1->info;
		nod1->info = nod2->info;
		nod2->info = temp;
	}
}


void dezalocare(struct Nod** cap)
{
	while (*cap)
	{
		free((*cap)->info.nume);
		struct Nod* aux = (*cap)->next;
		free((*cap));
		(*cap) = aux;
	}
}
void main()
{

	Nod* cap = NULL;
	Salon salon = initializareSalon("Magic", 12, 2000.9);
	Salon salon2 = initializareSalon("The SetUp", 17, 1700.3);
	Salon salon3 = initializareSalon("Beauty Mania", 65, 3345.8);
	Salon salon4 = initializareSalon("Cristal", 23, 4300.0);
	cap = inserareInceput(salon, cap);
	cap = inserareInceput(salon2, cap);
	cap = inserareInceput(salon3, cap);
	afisareLista(cap);

	printf("\nStergere nod pozitie:\n");
	stergeNodPozitie(&cap, 2);
	afisareLista(cap);

	int prag = 10;
	int dim;
	Salon* vector = salveazaInVector(cap, &dim, prag);
	printf("\nElementele din lista care indeplinesc conditia (pragul %d) si sunt salvate in vector: \n", prag);
	for (int i = 0; i < dim; i++) {
		printf("Nume: %s, Numar angajati: %d, Salarii: %.2f\n", vector->nume, vector->nrAngajati, vector->salarii);
	}

	dezalocare(&cap);
}