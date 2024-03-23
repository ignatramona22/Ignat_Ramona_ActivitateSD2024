#include <stdio.h>
#include <malloc.h>

//liste simplu inlantuite
typedef struct CafeneaMea Cafenea;
typedef struct Nod Nod;

struct CafeneaMea
{
	char* nume;
	int nrLocuri;
	float suprafata;
};

struct Nod
{
	Cafenea info; //informatia utila din nod
	Nod* next;  //nodul urmator
};

Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata)
{
	Cafenea cafenea;
	cafenea.nrLocuri;
	cafenea.suprafata;
	cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(cafenea.nume, nume);
	return cafenea;
}

Nod* inserareInceput(Cafenea c, Nod* cap)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->next = cap;
	nou->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
	return nou;
}

void afisareCafenea(Cafenea c)
{
	printf("\nDenumirea cafenelei este %s, are Nr scaune de %i si Suprafata de %.2f\n", c.nume, c.nrLocuri, c.suprafata);
}

void afisareCafenele(Nod* lista)
{
	while (lista != NULL)
	{
		afisareCafenea(lista->info);
		lista = lista->next;
	}
}

//numele cafenelei cu densitatea cea mai mica

char* numeCafeneaDensitateMinima(Nod* lista)
{
	if (lista != NULL)
	{
		if (lista->info.suprafata != 0)
		{
			float minim = lista->info.nrLocuri / lista->info.suprafata;
			Nod* adresa = lista;
			lista = lista->next;
			while (lista != NULL)
			{
				if (lista->info.nrLocuri / lista->info.suprafata < minim)
				{
					minim = lista->info.nrLocuri / lista->info.suprafata;
					adresa = lista;
				}
				lista = lista->next;
			}
			char* nume;
			nume = malloc(sizeof(char) * (strlen(adresa->info.nume) + 1));
			strcpy(nume, adresa->info.nume);
			return nume;
		}
	}
	return NULL;
}

void stergeLista(Nod** nod)
{
	while (*nod != NULL)
	{
		Nod* aux;
		aux = *nod;
		*nod = (*nod)->next;
		free(aux);
	}
	*nod = NULL;
}

void inserareFinal(Nod** lista, Cafenea c)
{
	if ((*lista) == NULL)
	{
		(*lista) = inserareInceput(c, *lista);
	}
	else
	{
		Nod* curent = (*lista);
		while (curent->next != NULL)
		{
			curent = curent->next;
		}
		Nod* n = (Nod*)malloc(sizeof(Nod));
		n->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
		n->next = NULL;
		curent->next = n;
	}
}
void main()
{
	Nod* cap = NULL;
	Cafenea c = initializareCafenea("Tucano", 12, 20);
	Cafenea c1 = initializareCafenea("Teds", 17, 17.3);
	Cafenea c2 = initializareCafenea("Urban", 65, 33);
	Cafenea c3 = initializareCafenea("SB", 23, 43);
	Cafenea c4 = initializareCafenea("5ToGo", 3, 10);

	cap = inserareInceput(c, cap);
	cap = inserareInceput(c1, cap);
	cap = inserareInceput(c2, cap);
	cap = inserareInceput(c3, cap);
	afisareCafenele(cap);

	char* numeMinim = numeCafeneaDensitateMinima(cap);
	printf("\nCafeneaua cu densitatea minima este: %s\n", numeMinim);

	inserareFinal(&cap, c4);
	afisareCafenele(cap);

	stergeLista(&cap);
	printf("\nDupa stergere: \n");
	afisareCafenele(cap);

	free(c.nume);
	c.nume = NULL;

	free(c1.nume);
	c1.nume = NULL;

	free(c2.nume);
	c2.nume = NULL;

	free(c3.nume);
	c3.nume = NULL;

	free(numeMinim);
}