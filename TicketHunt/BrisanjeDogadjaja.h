#ifndef BRISANJE_DOGADJAJA_H
#define BRISANJE_DOGADJAJA_H
// BRISANJE_DOGADJAJA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "KreiranjeDogadjaja.h"

typedef struct listaDogadjaja {
	DOGADJAJ dogadjaj;
	struct listaDogadjaja* next;
} ListaDogadjaja;

void brisanjeDogadjaja();
int provjeraUlaznica(char* IDDogadjaja);
int ponistiUlaznice(char* IDDogadjaja);
void dodajUlaznicu(ULAZNICE** ulaznice, char* sifra, DOGADJAJ* temp, char* ime);
int upisiUlaznice(ULAZNICE* lista);
void brisiUlaznice(ULAZNICE** ulaznice);
int brisiDogadjaj(char* IDDogadjaja);
void dodajUListu(ListaDogadjaja** lista, DOGADJAJ* temp);
void invertujListu(ListaDogadjaja** glava);
int upisiDogadjaje(ListaDogadjaja* lista);
void brisi(ListaDogadjaja** lista);

#endif
