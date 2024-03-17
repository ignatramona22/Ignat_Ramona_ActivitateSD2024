#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Restaurant {
	char* numeRestaurant;
	int nrAngajati;
	int* salariiAngajati;
	int vechimeRestaurant;
};

void inserareRestaurant(struct Restaurant** restaurante, int* dim, struct Restaurant restaurant)
{
	struct Restaurant* copie;
	copie = (struct Restaurant*)malloc(sizeof(struct Restaurant) * (++(*dim)));
	for (int i = 0; i < (*dim) - 1; ++i)
	{
		copie[i] = (*restaurante)[i];
	}
	copie[(*dim) - 1] = restaurant;
	if ((*restaurante) != NULL)
	{
		free((*restaurante));
	}
	(*restaurante) = copie;
}


void afisareRestaurant(struct Restaurant r)
{
	printf("\nNumele restaurantului: %s, Numar angajati: %i", r.numeRestaurant, r.nrAngajati);
	if (r.salariiAngajati > 0)
	{
		printf("Salariile angajatilor sunt: ");
		for (int i = 0; i < r.nrAngajati; ++i)
			printf("%i, ", r.salariiAngajati[i]);
	}
	printf("Vechimea restaurantului: %i\n", r.vechimeRestaurant);
}

void afiseazaVectoriRestaurante(struct Restaurant* restaurante, int dim)
{
	if (restaurante != NULL)
	{
		for (int i = 0; i < dim; ++i)
		{
			printf("\n");
			afisareRestaurant(restaurante[i]);
		}
	}
}

struct Restaurant** creeazaMatrice(struct Restaurant* restaurante, int dim, int* nrLinii, int** nrCol, int pragAn)
{
	struct Restaurant** matrice;
	*nrLinii = 2;
	matrice = malloc(sizeof(struct Restaurant*) * (*nrLinii));
	*nrCol = malloc(sizeof(int) * (*nrLinii));
	for (int i = 0; i < (*nrLinii); ++i)
	{
		(*nrCol)[i] = 0;
		matrice[i] = NULL;
	}
	for (int i = 0; i < dim; ++i)
	{
		if (restaurante[i].vechimeRestaurant > pragAn)
		{
			inserareRestaurant(&(matrice[0]), &((*nrCol)[0]), restaurante[i]);
		}
		else
		{
			inserareRestaurant(&(matrice[1]), &((*nrCol)[1]), restaurante[i]);
		}
	}

	return matrice;
}

void afiseazaMatrice(struct Restaurant** matrice, int nrLinii, int* nrColoane)
{
	for (int i = 0; i < nrLinii; ++i)
	{
		afiseazaVectoriRestaurante(matrice[i], nrColoane[i]);
		printf("\n\n");
	}
}

struct Restaurant initializareRestaurant(const char* numeRestaurant, int nrAngajati, int* salariiAngajati, int vechimeRestaurant)
{
	struct Restaurant restaurant;
	restaurant.numeRestaurant = (char*)malloc(sizeof(char) * (strlen(numeRestaurant) + 1));
	strcpy(restaurant.numeRestaurant, numeRestaurant);
	restaurant.nrAngajati = nrAngajati;
	restaurant.salariiAngajati = malloc(sizeof(int) * nrAngajati);
	for (int i = 0; i < nrAngajati; ++i)
	{
		restaurant.salariiAngajati[i] = salariiAngajati[i];
	}
	restaurant.vechimeRestaurant = vechimeRestaurant;
	return restaurant;
}
//
//void inserareRestaurant(struct Restaurant** vector, int* dim, struct Restaurant r)
//{
//	struct Restaurant* copie;
//	copie = malloc(sizeof(struct Restaurant) * (++(*dim)));
//	for (int i = 0; i < (*dim) - 1; ++i)
//		copie[i] = (*vector)[i];
//	copie[(*dim) - 1] = r;
//	if ((*vector) != NULL)
//		free((*vector));
//	(*vector) = copie;
//}

struct Restaurant* citesteFisier(const char* numeFisier, int* nrRestaurante)
{
	if (numeFisier != NULL && numeFisier > 0)
	{
		FILE* f = fopen(numeFisier, "r");
		if (f != NULL)
		{
			(*nrRestaurante) = 0;
			struct Restaurant* restaurante = NULL;
			char buffer[100];
			char delim[] = ",\n";
			while (fgets(buffer, 100, f) != NULL)
			{
				struct Restaurant restaurant;
				char* token;
				token = strtok(buffer, delim);
				restaurant.nrAngajati = atoi(token);
				restaurant.salariiAngajati = malloc(sizeof(int) * restaurant.nrAngajati);
				for (int i = 0; i < restaurant.nrAngajati; ++i)
				{
					token = strtok(NULL, delim);
					restaurant.salariiAngajati[i] = atoi(token);
				}
				token = strtok(NULL, delim);
				restaurant.vechimeRestaurant = atoi(token);
				inserareRestaurant(&restaurante, nrRestaurante, restaurant);

			}
			fclose(f);
			return restaurante;
		}

	}
}

void salvareFisier(const char* numeFisier, struct Restaurant restaurant)
{
	if (numeFisier != NULL && numeFisier > 0)
	{
		FILE* f = fopen(numeFisier, "w");
		if (f != NULL)
		{
			fprintf(f, "%s\n", restaurant.numeRestaurant);
			fprintf(f, "%s\n", restaurant.nrAngajati);
			for (int i = 0; i < restaurant.nrAngajati; ++i)
			{
				fprintf(f, "%i, ", restaurant.salariiAngajati[i]);
			}
			fprintf(f, "\n%i\n", restaurant.vechimeRestaurant);
			fclose(f);
		}
	}
}

void salvareVectorFisier(const char* numeFisie, struct Restaurant* restaurante, int dim)
{
	if (numeFisie != NULL && numeFisie > 0)
	{
		FILE* f = fopen(numeFisie, "w");
		if (f != NULL)
		{
			for (int i = 0; i < dim; ++i)
			{
				fprintf(f, "%s", restaurante[i].numeRestaurant);
				fprintf(f, "%i", restaurante[i].nrAngajati);
				for (int j = 0; j < restaurante[i].nrAngajati; ++j)
				{
					fprintf(f, "%i, ", restaurante[i].salariiAngajati[j]);
				}
				fprintf(f, "%i\n", restaurante[i].vechimeRestaurant);
			}
			fclose(f);
		}
	}
}

void swap(struct Restaurant** a, struct Restaurant** b, int* nrColoaneA, int* nrColoaneB) {
	struct Restaurant* aux = *a;
	*a = *b;
	*b = aux;

	int aux1 = *nrColoaneA;
	*nrColoaneA = *nrColoaneB;
	*nrColoaneB = aux1;
}

void sortareLinii(struct Restaurant*** matrice, int nrLinii, int* nrColoane) {
	for (int i = 0; i < nrLinii - 1; ++i) {
		for (int j = 0; j < nrLinii - i - 1; ++j) {
			if (nrColoane[j] > nrColoane[j + 1]) {
				swap(&(*matrice) + j, &(*matrice) + j + 1, &nrColoane[j], &nrColoane[j + 1]);
			}
		}
	}
}




void main()
{
	struct Restaurant* restaurante = NULL;
	int dim = 0;
	int nrLinii = 0;
	int* vectorColoane = NULL;
	restaurante = citesteFisier("restaurante.txt", &dim);
	//afiseazaVectoriRestaurante(restaurante, dim);

	int* vector2 = malloc(sizeof(int) * 4);
	for (int i = 0; i < 4; ++i)
	{
		vector2[i] = (i + 2) * 100 + (500 - i * 22);
	}
	struct Restaurant restaurant1 = initializareRestaurant("Italian Restaurant", 4, vector2, 1999);
	salvareFisier("restaurant.txt", restaurant1);

	salvareVectorFisier("restauranteSalvate.txt", restaurante, dim);

	struct Restaurant** matrice = creeazaMatrice(restaurante, dim, &nrLinii, &vectorColoane, 1950);
	afiseazaMatrice(matrice, nrLinii, vectorColoane);
	sortareLinii(matrice, nrLinii, vectorColoane);
	printf("\n\nMatricea dupa sortare:\n");
	afiseazaMatrice(matrice, nrLinii, vectorColoane);
}

