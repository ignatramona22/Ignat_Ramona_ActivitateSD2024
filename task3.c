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

struct Restaurant initializareRestaurant(const char* numeRestaunat, int nrAngajati, int* salariiAngajati, int vechimeRestaurant)
{
	struct Restaurant restaurant;
	restaurant.numeRestaurant = (char*)malloc(sizeof(char) * (strlen(numeRestaunat) + 1));
	strcpy(restaurant.numeRestaurant, numeRestaunat);
	restaurant.nrAngajati = nrAngajati;
	restaurant.salariiAngajati = malloc(sizeof(int) * nrAngajati);
	for (int i = 0; i < nrAngajati; ++i)
	{
		restaurant.salariiAngajati[i] = salariiAngajati[i];
	}
	restaurant.vechimeRestaurant = vechimeRestaurant;
	return restaurant;

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

void inserareRestaurant(struct Restaurant** vector, int* dim, struct Restaurant r)
{
	struct Restaurant* copie;
	copie = malloc(sizeof(struct Restaurant) * (++(*dim)));
	for (int i = 0; i < (*dim) - 1; ++i)
		copie[i] = (*vector)[i];
	copie[(*dim) - 1] = r;
	if ((*vector) != NULL)
		free((*vector));
	(*vector) = copie;
}

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



void main()
{
	struct Restaurant* restaurante = NULL;
	int dim = 0;
	restaurante = citesteFisier("restaurante.txt", &dim);
	afiseazaVectoriRestaurante(restaurante, dim);
	int* vector2 = malloc(sizeof(int) * 4);
	for (int i = 0; i < 4; ++i)
	{
		vector2[i] = (i + 2) * 100 + (500 - i * 22);
	}
	struct Restaurant restaurant1 = initializareRestaurant("Italian Restaurant", 4, vector2, 1999);
	salvareFisier("restaurant.txt", restaurant1);

	salvareVectorFisier("restauranteSalvate.txt", restaurante, dim);
}

