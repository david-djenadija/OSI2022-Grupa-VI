#ifndef BRISANJE_NALOGA_H
#define BRISANJE_NALOGA_H
#include "Registracija.h"

#define MAX 20
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef  struct account {
    USER user;
    struct account* next;
} ACCOUNT;

void obrisiNalog();
void dodaj(ACCOUNT** acc, USER* pom);
void invertuj(ACCOUNT** glava);
int ukloniNalog(FILE* f, ACCOUNT* nalog);
void brisi(ACCOUNT** nalog);

#endif
