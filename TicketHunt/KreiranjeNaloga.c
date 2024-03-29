#include "KreiranjeNaloga.h"
#include "Registracija.h"
#include "LoadConfig.h"
void kreirajNalog() {

	char vrstaNaloga[MAX];
	printf("Unesite vrstu naloga koji zelite da kreirate (administratorski/klijentski) ");
	scanf("%s", vrstaNaloga);

	printf("Unesite podatke o nalogu:\n");

	FILE* f = 0;

	if (strcmp(vrstaNaloga, "klijentski") == 0) {

		KLIJENT klijent;

		unosKlijenta(&klijent);

		if (dodajKlijenta(f, &klijent))
			printf("Nalog je uspjesno kreiran.\n");
	}

	else if (strcmp(vrstaNaloga, "administratorski") == 0) {

		ADMINISTRATOR administrator;

		unosAdministratora(&administrator);

		if (dodajAdministratora(f, &administrator))
			printf("Nalog je uspjesno kreiran.\n");
	}

	else printf("Neispravna vrsta naloga.\n");
}

int dodajKlijenta(FILE* f, KLIJENT* klijent) {

	while (traziKlijenta(f, klijent->korisnickoIme)) {
		printf("Korisnicko ime vec postoji.\n");
		printf("korisnickoIme:"); scanf("%s", klijent->korisnickoIme);
	}
	while (traziAdministratora(f, klijent->korisnickoIme)) {
		printf("Korisnicko ime vec postoji.\n");
		printf("korisnickoIme:"); scanf("%s", klijent->korisnickoIme);
	}
	while (provjeriUsername(klijent->korisnickoIme)) {
		printf("Korisnicko ime vec postoji.\n");
		printf("korisnickoIme:"); scanf("%s", klijent->korisnickoIme);
	}

	if (f = fopen(concat(CONFIG_DEV_FOLDER,"Klijenti.txt"), "a")) {

		fprintf(f, "%s %s %s %s\n", klijent->ime, klijent->prezime, klijent->korisnickoIme, klijent->sifra);
		fclose(f);
	}

	else {
		printf("Neuspjesno otvaranje datoteke.");
		return 0;
	}

	return 1;
}

int dodajAdministratora(FILE* f, ADMINISTRATOR* administrator) {

	while (traziAdministratora(f, administrator->korisnickoIme)) {
		printf("Korisnicko ime vec postoji.\n");
		printf("korisnickoIme:"); scanf("%s", administrator->korisnickoIme);
	}
	while (traziKlijenta(f, administrator->korisnickoIme)) {
		printf("Korisnicko ime vec postoji.\n");
		printf("korisnickoIme:"); scanf("%s", administrator->korisnickoIme);
	}
	while (provjeriUsername(administrator->korisnickoIme)) {
		printf("Korisnicko ime vec postoji.\n");
		printf("korisnickoIme:"); scanf("%s", administrator->korisnickoIme);
	}

	if (f = fopen(concat(CONFIG_DEV_FOLDER,"Administratori.txt"), "a")) {

		fprintf(f, "%s %s %s %s\n", administrator->ime, administrator->prezime, administrator->korisnickoIme, administrator->sifra);
		fclose(f);
	}
	else {
		printf("Neuspjesno otvaranje datoteke.");
		return 0;
	}
	return 1;
}

int traziKlijenta(FILE* f, char* korisnickoIme) {
	KLIJENT klijent;

	if (f = fopen(concat(CONFIG_DEV_FOLDER,"Klijenti.txt"), "r")) {
		while (fscanf(f, "%s %s %s %s", klijent.ime, klijent.prezime, klijent.korisnickoIme, klijent.sifra) == 4) {
			if (strcmp(klijent.korisnickoIme, korisnickoIme) == 0) {
				fclose(f);
				return 1;
			}
		}
		fclose(f);
	}
	return 0;
}

int traziAdministratora(FILE* f, char* korisnickoIme) {

	ADMINISTRATOR administrator;
	if (f = fopen(concat(CONFIG_DEV_FOLDER,"Administratori.txt"), "r")) {
		while (fscanf(f, "%s %s %s %s", administrator.ime, administrator.prezime, administrator.korisnickoIme, administrator.sifra) == 4) {
			if (strcmp(administrator.korisnickoIme, korisnickoIme) == 0) {
				fclose(f);
				return 1;
			}
		}
		fclose(f);
	}
	return 0;
}
int provjeraFormataSifre(char* sifra) {

	if (strlen(sifra) < 8) {
		printf("Neispravan format.\n");
		return 0;
	}

	int broj = 0;
	int velikoSlovo = 0;

	for (int i = 0; i < strlen(sifra); i++) {
		if (sifra[i] >= '0' && sifra[i] <= '9') broj++;
		if (sifra[i] >= 'A' && sifra[i] <= 'Z') velikoSlovo++;
	}

	if (!broj || !velikoSlovo) {
		printf("Neispravan format.\n");
		return 0;
	}

	return 1;
}

void unosKlijenta(KLIJENT* klijent) {

	printf("Ime:"); scanf("%s", klijent->ime);
	printf("Prezime:"); scanf("%s", klijent->prezime);
	printf("korisnickoIme:"); scanf("%s", klijent->korisnickoIme);
	printf("Sifra mora imati bar 8 znakova od kojih je jedan veliko slovo, a jedan broj.\n");
	printf("sifra:"); scanf("%s", klijent->sifra);

	while (provjeraFormataSifre(klijent->sifra) == 0) {
		printf("sifra:"); scanf("%s", klijent->sifra);
	}
}

void unosAdministratora(ADMINISTRATOR* administrator) {

	printf("Ime:"); scanf("%s", administrator->ime);
	printf("Prezime:"); scanf("%s", administrator->prezime);
	printf("korisnickoIme:"); scanf("%s", administrator->korisnickoIme);
	printf("Sifra mora imati bar 8 znakova od kojih je jedan veliko slovo, a jedan broj.\n");
	printf("sifra:"); scanf("%s", administrator->sifra);

	while (provjeraFormataSifre(administrator->sifra) == 0) {
		printf("sifra:"); scanf("%s", administrator->sifra);
	}
}
