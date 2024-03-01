#include <stdio.h>
#include <stdlib.h>
//in C nu avem metode in structuri
struct Haina
{
	int marime;
	char* marca;
	float pret;
	char gender;
}; 
void afiseazaHaina(struct Haina h)
{
	if (h.marca != NULL)
		printf("Marca: %s\n", h.marca);
	printf("Marime: %d\n", h.marime);
	printf("Pret: %5.2f\n", h.pret);
	printf("Gen: %c\n\n", h.gender);
}
struct Haina initializareHaina(int marime, char* marca, float pret, char gender)
{
	struct Haina h;
	h.marime = marime;
	if (marca != NULL && strlen(marca) > 0)
	{
		h.marca = malloc(strlen(marca) + 1); //nu fac castul
		strcpy(h.marca, marca);
	}
	else
	{
		h.marca = NULL;
	}
	h.pret = pret;
	h.gender = gender;
	return h;
}
void dezalocareHaina(struct Haina* h)
{
	free(h->marca);
	h->marca = NULL;  //(*h).marca
}
void main()
{
	//principiul DRY
	//void* - pointer generic
	struct Haina haina1;
	haina1.marime = 33;
	haina1.marca = (char*)malloc(sizeof(char) * (strlen("Nike") + 1));
	strcpy(haina1.marca, "Nike");
	haina1.pret = 45;
	haina1.gender = 'M';
	afiseazaHaina(haina1);
	dezalocareHaina(&haina1);

	struct Haina haina2 = initializareHaina(27, "Adidas", 23.6, 'F');
	afiseazaHaina(haina2);
	dezalocareHaina(&haina2);

	afiseazaHaina(haina2); //nu mai am dangling pointer
}