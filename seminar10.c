#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Cinema Cinema;
typedef struct Nod Nod;


struct Cinema
{
	int id;
	int nrFirme;
	char** listaFirme;
};

struct Nod
{
	Cinema info;
	Nod* st;
	Nod* dr;
};

void inserareInArbore(Nod** radacina, Cinema c)
{
	if (*radacina)
	{
		if ((*radacina)->info.id > c.id)
		{
			inserareInArbore(&((*radacina)->st), c);
		}
		else
		{
			inserareInArbore(&((*radacina)->dr), c);
		}
	}
	else
	{
		Nod* nod = malloc(sizeof(Nod));
		nod->dr = NULL;
		nod->st = NULL;
		nod->info = c;
		*radacina = nod;

	}
}

Cinema citireCinema(FILE* f)
{
	Cinema c;
	fscanf(f, "%d", &c.id);
	fscanf(f, "%d", &c.nrFirme);
	if (c.nrFirme != 0)
	{
		c.listaFirme = (char**)malloc(sizeof(char*) * c.nrFirme);
		for (int i = 0; i < c.nrFirme; i++)
		{
			char* buffer[100];
			fscanf(f, "%s", buffer);
			c.listaFirme[i] = malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy(c.listaFirme[i], buffer);
		}

	}
	else
	{
		c.listaFirme = NULL;
	}
	return c;
}


Nod* citireDinFiser(const char* nume_fisier)
{
	Nod* radacina = NULL;
	if (nume_fisier != NULL && strlen(nume_fisier) > 0)
	{
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL)
		{
			int dim = 0;

			fscanf(f, "%d", &dim);
			for (int i = 0; i < dim; i++)
			{
				Cinema cinema;
				cinema = citireCinema(f);
				inserareInArbore(radacina, cinema);

			}
		}
	}
	return radacina;

}
void afisareCinema(Cinema c)
{
	printf("Cinematograful cu id-ul %d are in derulare %d firme: ", c.id, c.nrFirme);
	for (int i = 0; i < c.nrFirme; i++)
	{
		printf("%s", c.listaFirme[i]);
	}
	printf("\n");
}

void afisareArborePreordine(Nod* rad)
{
	if (rad)
	{
		afisareCinema(rad->info);
		afisareArborePreordine(rad->st);
		afisareArborePreordine(rad->dr);
	}
}

void afisareArboreInOrdine(Nod* rad)
{
	if (rad)
	{
		afisareArboreInOrdine(rad->st);
		afisareCinema(rad->info);
		afisareArboreInOrdine(rad->dr);
	}
}
int calculNrFirmeRedate(Nod* rad)
{
	if (rad)
	{
		int suma = rad->info.nrFirme;
		suma += calculNrFirmeRedate(rad->st);
		suma += calculNrFirmeRedate(rad->dr);
		return suma;
	}
	else
	{
		return 0;
	}
}
void main()
{
	Nod* arbore = NULL;
	arbore = citireDinFiser("arbore.txt");
	afisareArboreInOrdine(arbore);
	printf("\n\nNumar filme: %d", calculNrFirmeRedate(arbore));

}