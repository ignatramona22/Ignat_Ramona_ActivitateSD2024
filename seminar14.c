#include <stdio.h>
#include <malloc.h>
# include <string.h>

typedef struct Camion Camion;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Camion {
	int serie;
	char* marca;
	float greutate;
};

struct NodPrincipal
{
	Camion info;
	NodSecundar* vecini;
	NodPrincipal* next;
};

struct NodSecundar
{
	NodPrincipal* nod;
	NodSecundar* next;

};

//inserare in lista principala la inceput
NodPrincipal* inserarePrincipala(NodPrincipal* graf, Camion c)
{
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = c;
	nou->next = graf;
	nou->vecini = NULL;
	return nou;
}
// functie de cautare nod principal dupa Serie camion
NodPrincipal* cautaNodDupaSerie(NodPrincipal* graf, int serie)
{
	while (graf && graf->info.serie != serie)
	{
		graf = graf->next;
	}
	return graf;
}
//inserare la sfarsit pentru lists secundara
void inserareScundara(NodSecundar** cap, NodPrincipal* nod)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->nod = nod;
	nou->next = NULL;
	if (*cap)
	{
		NodSecundar* p = *cap;
		while (p->next)
		{
			p = p->next;
		}

	}
	else
	{

		*cap = nod;
	}
}
//inserare muchie in lista

void inserareMuchie(NodPrincipal* graf, int serieStart, int serieStop)
{
	NodPrincipal* nodStart = cautaNodDupaSerie(graf, serieStart);
	NodPrincipal* nosStop = cautaNodDupaSerie(graf, serieStop);
	inserareScundara(&(nodStart->vecini), nodStart);

}

Camion creareCamion(int serie, const char* marca, float greutate)
{
	Camion c;
	c.serie = serie;
	c.greutate = greutate;
	c.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	return c;
}


#pragma region coada

typedef struct NodCoada NodCoada;

struct NodCoada
{
	int info;
	NodCoada* next;

};

void pushCoada(NodCoada** coada, int seria)
{
	NodCoada* nod = (NodCoada*)malloc(sizeof(NodCoada));
	nod->info = seria;
	nod->info = NULL;
	if (*coada)
	{
		NodCoada* aux = *coada;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nod;
	}

	else
	{
		*coada = nod;
	}
}

void pushStiva(NodCoada** stiva, int seria)
{
	NodCoada* nod = (NodCoada*)malloc(sizeof(NodCoada));
	nod->info = seria;
	nod->next = *stiva;
	*stiva = nod;
}

int popStiva(NodCoada** striva)
{
	return popCoada(striva);
}
int popCoada(NodCoada** coada)
{
	if (*coada)
	{
		int rez = (*coada)->info;
		NodCoada* aux = *coada;
		*coada = (*coada)->next;
		free(aux);
		return rez;
	}
	return -1;
}

#pragma endregion

int calculNoduriGraf(NodPrincipal* graf)
{
	int nrNoduri = 0;
	while (graf)
	{
		nrNoduri++;
		graf = graf->next;
	}
	return nrNoduri;
}


void afisareCamion(Camion c)
{
	printf("%d. Camionul %s are greutatea %f\n", c.serie, c.marca, c.greutate);
}

void afisarePrinParcurgereLatime(NodPrincipal* graf, int serieStart)
{
	if (graf)
	{
		NodCoada* coada = NULL;
		int nrNoduri = calculNoduriGraf(graf);
		char* vizitat = (char*)malloc(sizeof(char) * nrNoduri);
		for (int i = 0; i < nrNoduri; i++)
		{
			vizitat[i] = 0;
		}
		vizitat[serieStart] = 1;
		pushCoada(&coada, serieStart);
		while (coada)
		{
			int serieCurena = popCoada(&coada);
			NodPrincipal* nodCurent = cautaNodDupaSerie(graf, serieCurena);
			afisareCamion(nodCurent->info);
			NodSecundar* vecini = nodCurent->vecini;
			while (vecini)
			{
				if (vizitat[vecini->nod->info.serie] == 0)
				{
					pushCoada(&coada, vecini->nod->info.serie);
					vizitat[vecini->nod->info.serie] = 1;
				}
				vecini = vecini->next;
			}

		}
		if (vizitat)
		{
			free(vizitat);
		}
	}
}


void afisarePrinParcurgereAdancime(NodPrincipal* graf, int serieStart)
{
	if (graf)
	{
		NodCoada* stiva = NULL;
		int nrNoduri = calculNoduriGraf(graf);
		char* vizitat = (char*)malloc(sizeof(char) * nrNoduri);
		for (int i = 0; i < nrNoduri; i++)
		{
			vizitat[i] = 0;
		}
		vizitat[serieStart] = 1;
		pushCoada(&stiva, serieStart);
		while (stiva)
		{
			int serieCurena = popCoada(&stiva);
			NodPrincipal* nodCurent = cautaNodDupaSerie(graf, serieCurena);
			afisareCamion(nodCurent->info);
			NodSecundar* vecini = nodCurent->vecini;
			while (vecini)
			{
				if (vizitat[vecini->nod->info.serie] == 0)
				{
					pushCoada(&stiva, vecini->nod->info.serie);
					vizitat[vecini->nod->info.serie] = 1;
				}
				vecini = vecini->next;
			}

		}

	}
}
void stergeListaVecini(NodSecundar** vecini)
{
	while (*vecini)
	{
		NodSecundar* aux = *vecini;
		(*vecini) = aux->next;
		free(aux);
	}
}

void stergereGraf(NodPrincipal** graf)
{
	while (*graf)
	{
		NodPrincipal* p = *graf;
		free(p->info.marca);
		stergeListaVecini(&(p->vecini));

		(*graf) = p->next;
		free(p);
	}
}

void main()
{
	NodPrincipal* graf = NULL;
	//inseram 5 noduri cu id-urile 0 1 2 3 4
	graf = inserarePrincipala(graf, creareCamion(4, "Scania", 20));
	graf = inserarePrincipala(graf, creareCamion(3, "Volvo", 30));
	graf = inserarePrincipala(graf, creareCamion(2, "Renault", 25));
	graf = inserarePrincipala(graf, creareCamion(1, "MAN", 15));
	graf = inserarePrincipala(graf, creareCamion(3, "Mercedes", 40));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 0, 3);
	inserareMuchie(graf, 3, 4);
	inserareMuchie(graf, 2, 4);

	inserareMuchie(graf, 1, 3);

	afisarePrinParcurgereLatime(graf, 4);
	print("\n\n");
	afisarePrinParcurgereAdancime(graf, 4);

	stergereGraf(&graf);


}