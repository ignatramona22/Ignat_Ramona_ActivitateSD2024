#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Restaurant {
	char* numeRestaurant;
	int nrAngajati;
	float* salariiAngajati;
	int vechimeRestaurant;
};

struct Restaurant initializareRestaurant(const char* numeRestaunat, int nrAngajati, float* salariiAngajati, int vechimeRestaurant)
{
	struct Restaurant restaurant;
	restaurant.numeRestaurant = (char*)malloc(sizeof(char) * (strlen(numeRestaunat) + 1));
	strcpy(restaurant.numeRestaurant, numeRestaunat);
	restaurant.nrAngajati = nrAngajati;
	restaurant.salariiAngajati = malloc(sizeof(float) * nrAngajati);
	for (int i = 0; i < nrAngajati; i++)
	{
		restaurant.salariiAngajati[i] = salariiAngajati[i];
	}
	restaurant.vechimeRestaurant = vechimeRestaurant;
	return restaurant;

}
struct Restaurant citireRestaurant()
{
	struct Restaurant restaurant;
	printf("\nNumele restaurantului: ");
	char aux[25];
	scanf("%s", aux);
	restaurant.numeRestaurant = (char*)malloc(sizeof(float) * restaurant.nrAngajati);
	printf("\nSalariile angajatilor: ");
	for (int i = 0; i < restaurant.nrAngajati; i++)
	{
		printf("\ns[%i]=  "); scanf("%f", &restaurant.salariiAngajati[i]);
	}
	return restaurant;
}

struct Restaurant* modificaNume(struct Restaurant* r, const char* numeNou)
{
	if (numeNou != NULL)
	{
		free(r->numeRestaurant);
		r->numeRestaurant = NULL;
		r->numeRestaurant = malloc(strlen(numeNou) + 1);
		strcpy(r->numeRestaurant, numeNou);
	}
	return r;
}

void afisareRestaurant(struct Restaurant r)
{
	printf("\nNumele restaurantului: ");
	if (r.numeRestaurant != NULL)
	{
		printf("%s", r.numeRestaurant);
	}
	else
	{
		printf("-");
	}
	printf("\nNumarul angajatilor restaurantului: %i", r.nrAngajati);
	printf("\nSalariile angajatilor sunt: ");
	if (r.salariiAngajati == NULL && r.nrAngajati == 0)
	{
		printf("-");
	}
	else
	{
		for (int i = 0; i < r.nrAngajati; i++)
		{
			printf("%5.2f", r.salariiAngajati[i]);
		}
	}
}

void afiseazaVectoriRestaurante(struct Restaurant* restaurante, int nrRestaurante)
{
	if (restaurante != NULL)
	{
		for (int i = 0; i < nrRestaurante; i++)
		{
			printf("\n");
			afisareRestaurant(restaurante[i]);
		}
	}
}

void dezalocare(struct Restaurant** restaurante, int* nrRestaurante)
{
	if ((*restaurante) != NULL)
	{
		for (int i = 0; i < *nrRestaurante; i++)
		{
			free((*restaurante)[i].numeRestaurant);
			free((*restaurante)[i].salariiAngajati);
		}
		free(*restaurante);
		*nrRestaurante = 0;
		*restaurante = NULL;
	}
}

void copiazaNoiRestaurante(struct Restaurant* restaurante, int nrRestaurante, int an, struct Restaurant** noiRestaurante, int* nrNou)
{
	if ((*noiRestaurante) != NULL)
	{
		dezalocare(noiRestaurante, nrNou);
	}
	else {
		*nrNou = 0;
	}
	for (int i = 0; i < nrRestaurante; ++i)
	{
		if (restaurante[i].vechimeRestaurant > an);
		{
			(*nrNou)++;
		}
	}
	*noiRestaurante = (struct Restaurant*)malloc(sizeof(struct Restaurant) * (*nrNou));
	int k = 0;
	for (int i = 0; i < nrRestaurante; ++i)
	{
		if (restaurante[i].vechimeRestaurant > an)
		{
			(*noiRestaurante)[k++] = initializareRestaurant(restaurante[i].numeRestaurant, restaurante[i].nrAngajati, restaurante[i].salariiAngajati, restaurante[i].vechimeRestaurant);

		}
	}
}

void copiazaRestauranteDinAceeasiTara(struct Restaurant* restaurante, int nrRestaurante, const char* tara, struct Restaurant** restauranteNoi, int* nrNou)
{
	if ((*restauranteNoi) != NULL)
	{
		dezalocare(restauranteNoi, nrNou);
	}
	else
	{
		*nrNou = 0;
	}
	for (int i = 0; i < nrRestaurante; ++i)
	{
		if (strcmp(restaurante[i].numeRestaurant, tara) == 0)
		{
			(*nrNou)++;
		}
	}
	*restauranteNoi = (struct Restaurant*)malloc(sizeof(struct Restaurant) * (*nrNou));
	int k = 0;
	for (int i = 0; i < nrRestaurante; ++i)
		if (strcmp(restaurante[i].numeRestaurant, tara) == 0)
		{
			(*restauranteNoi)[k++] = initializareRestaurant(restaurante[i].numeRestaurant, restaurante[i].nrAngajati, restaurante[i].salariiAngajati, restaurante[i].vechimeRestaurant);
		}
}

struct Restaurant* concatenareRestaurante(struct Restaurant* restaurante1, int nr1, struct Restaurant* restaurante2, int nr2)
{
	struct Restaurant* restauranteConcat;
	int nrConcat = nr1 + nr2;
	restauranteConcat = (struct Restaurant*)malloc(sizeof(struct Restaurant) * nrConcat);
	for (int i = 0; i < nr1; ++i)
	{
		restauranteConcat[i] = initializareRestaurant(restaurante1[i].numeRestaurant, restaurante1[i].nrAngajati, restaurante1[i].salariiAngajati, restaurante1[i].vechimeRestaurant);
	}
	for (int i = nr1; i < nrConcat; ++i)
	{
		restauranteConcat[i] = initializareRestaurant(restaurante2[i - nr1].numeRestaurant, restaurante2[i - nr1].nrAngajati, restaurante2[i - nr1].salariiAngajati, restaurante2[i - nr1].vechimeRestaurant);
	}
	return restauranteConcat;
}

void dezalocareRestaurant(struct Restaurant* r)
{
	if (r->numeRestaurant != NULL)
	{
		free(r->numeRestaurant);
	}
	r->numeRestaurant = NULL;
}

void main()
{
	float* vector1 = malloc(sizeof(float) * 3);
	vector1[0] = 6578;
	vector1[1] = 2453.7;
	vector1[2] = 4567;

	float* vector2 = malloc(sizeof(float) * 4);
	for (int i = 0; i < 4; ++i)
	{
		vector2[i] = i * 400 + 230 * (7 - i);
	}

	int nrRestaurante = 10;
	struct Restaurant* restaurante = (struct Restaurant*)malloc(sizeof(struct Restaurant) * nrRestaurante);
	for (int i = 0; i < nrRestaurante; ++i)
	{
		if (i % 2)
		{
			restaurante[i] = initializareRestaurant("Blue Events", 3, vector1, 2001 + (10 - i * 2));
		}
		else
		{
			restaurante[i] = initializareRestaurant("Sea Food Restaurant", 4, vector2, 2003 - (i * 3));
		}
	}
	afiseazaVectoriRestaurante(restaurante, nrRestaurante);

	struct Restaurant* noiRestaurante = NULL;
	int nrRestauranteNoi = 0;
	copiazaNoiRestaurante(restaurante, nrRestaurante, 2001, &noiRestaurante, &nrRestauranteNoi);
	printf("\n\n===================Restaurantele deschise dupa 2001: ==========================");
	afiseazaVectoriRestaurante(noiRestaurante, nrRestauranteNoi);

	struct Restaurant* restauranteTara = NULL;
	int nrRestauranteTara = 0;
	copiazaRestauranteDinAceeasiTara(restaurante, nrRestaurante, "Blue Events", &restauranteTara, &nrRestauranteTara);
	printf("\n\n===============Restaurante Blue Events: =====================");
	afiseazaVectoriRestaurante(restauranteTara, nrRestauranteTara);

	float* vector3 = malloc(sizeof(float) * 2);
	vector3[0] = 9345;
	vector3[1] = 1246.2;
	int nrRestaurante1 = 7;
	struct Restaurant* restaurante1 = (struct Restaurant*)malloc(sizeof(struct Restaurant) * nrRestaurante1);
	restaurante1[0] = initializareRestaurant("Pizzerie", 2, vector3, 2007);
	restaurante1[1] = initializareRestaurant("Asian Restaurant", 2, vector3, 2009);

	struct Restaurant* restauranteConcat = concatenareRestaurante(restaurante, nrRestaurante, restaurante1, nrRestaurante1);
	int dimConcat = nrRestaurante + nrRestaurante1;
	printf("\n\n============Concatenare: =====================");
	afiseazaVectoriRestaurante(restauranteConcat, dimConcat);

	dezalocare(&restaurante, &nrRestaurante);
	dezalocare(&restaurante1, &nrRestaurante1);
	dezalocare(&noiRestaurante, &nrRestauranteNoi);
	dezalocare(&restauranteTara, &nrRestauranteTara);
	dezalocare(&restauranteConcat, &dimConcat);
}

