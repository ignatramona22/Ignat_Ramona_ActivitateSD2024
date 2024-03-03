#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Restaurant {
	char* numeRestaurant;
	int nrAngajati;
	float* salariiAngajati;
};

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

float salariuMax(struct Restaurant r)
{
	float salariuMax = 0;
	for (int i = 0; i < r.nrAngajati; i++)
	{
		if (r.salariiAngajati[i] > salariuMax) {
			salariuMax = r.salariiAngajati[i];
		}
	}
	return salariuMax;
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


	struct Restaurant r;
	r.numeRestaurant = (char*)malloc(strlen("Bule Events") + 1);
	strcpy(r.numeRestaurant, "Bule Events");
	r.nrAngajati = 4;
	r.salariiAngajati = malloc(sizeof(float) * r.nrAngajati);
	for (int i = 0; i < r.nrAngajati; i++) {
		r.salariiAngajati[i] = 1000.0 + i * 200.0;
	}
	afisareRestaurant(r);
	printf("\nSalariul maxim este: %5.2f ", salariuMax(r));
	dezalocareRestaurant(&r);
	printf("\n\n============Restaurant citit de la tastatura==========");
	struct Restaurant r2 = citireRestaurant();
	modificaNume(&r2, "Sea Food Restaurant");
	afisareRestaurant(r2);
	dezalocareRestaurant(&r2);
}

