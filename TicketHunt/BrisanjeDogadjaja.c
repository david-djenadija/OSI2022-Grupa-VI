#include "BrisanjeDogadjaja.h"
#include "KreiranjeDogadjaja.c"

void brisanjeDogadjaja() {

	char IDDogadjaja[150];
	printf("Unesite ID dogadjaja koji zelite da obrisete: ");
    scanf("%s", IDDogadjaja);
	while (!provjeraID(IDDogadjaja)) {
		printf("Dogadjaj ne postoji. Izaberite ponovo.\n");
        scanf("%s", IDDogadjaja);
	}
	//if (provjeraUlaznica(IDDogadjaja)) {
	//	ponistiUlaznice(IDDogadjaja);
	//}

	if(brisiDogadjaj(IDDogadjaja)){
	printf("Dogadjaj uspjesno obrisan.\n");
    }
}

//int provjeraUlaznica(char* IDDogadjaja) {

//}
//int ponistiUlaznice(char* IDDogadjaja) {

//}
int brisiDogadjaj(char* IDDogadjaja) {
	
    FILE* fp;
    ListaDogadjaja* lista = 0;
    if (fp = fopen("Dogadjaji.txt", "r"))
    {
        DOGADJAJ temp;

        while (fscanf(fp, "%s %d.%d.%d %d:%d %s %d %d %d %d %s\n", temp.naziv, &temp.datum.dan,
            &temp.datum.mjesec, &temp.datum.godina, &temp.vrijeme.sat, &temp.vrijeme.minut, temp.mjesto,
            &temp.cijena_ulaznice, &temp.broj_mjesta, &temp.broj_prodatih_ulaznica, &temp.kupuje_na_ime, temp.ID) != EOF) {
            if (strcmp(IDDogadjaja, temp.ID) != 0) {
                dodajUListu(&lista, &temp);
            }
		else{
			strcat(temp.naziv, ".txt"); 
			if(remove(temp.naziv) != 0){
				fclose(fp);
				return 0;
			}
		}
        }
        fclose(fp);
    }
    else
    {
        printf("Neuspjesno otvaranje datoteke za citanje.\nNeuspjesno brisanje.\n");
        return 0;
    }

    invertujListu(&lista);

    if (!upisiDogadjaje(lista))
        return 0;
	
    brisi(&lista);
    return 1;
}

void dodajUListu(ListaDogadjaja** lista, DOGADJAJ* temp) {

    ListaDogadjaja* novi = (ListaDogadjaja*)malloc(sizeof(ListaDogadjaja));

    if (!novi) return;

    strcpy(novi->dogadjaj.naziv, temp->naziv);
    novi->dogadjaj.datum = temp->datum;
    novi->dogadjaj.vrijeme = temp->vrijeme;
    strcpy(novi->dogadjaj.mjesto, temp->mjesto);
    novi->dogadjaj.cijena_ulaznice = temp->cijena_ulaznice;
    novi->dogadjaj.broj_mjesta = temp->broj_mjesta;
    novi->dogadjaj.broj_prodatih_ulaznica = temp->broj_prodatih_ulaznica;
    novi->dogadjaj.kupuje_na_ime = temp->kupuje_na_ime;
    strcpy(novi->dogadjaj.ID, temp->ID);

    novi->next = *lista;
    *lista = novi;
}

void invertujListu(ListaDogadjaja** glava) {
    ListaDogadjaja* p1 = *glava, * p2 = 0, * p3;
    while (p1) {
        p3 = p1->next;
        p1->next = p2;
        p2 = p1;
        p1 = p3;
    }
    *glava = p2;
}

int upisiDogadjaje(ListaDogadjaja* lista) {
    FILE* f = 0;
    if (f = fopen("Dogadjaji.txt", "w")) {
        while (lista) {
            fprintf(f, "%s %d.%d.%d %d:%d %s %d %d %d %d %s\n", lista->dogadjaj.naziv, lista->dogadjaj.datum.dan, lista->dogadjaj.datum.mjesec, lista->dogadjaj.datum.godina,
                lista->dogadjaj.vrijeme.sat, lista->dogadjaj.vrijeme.minut, lista->dogadjaj.mjesto, lista->dogadjaj.cijena_ulaznice, 
                lista->dogadjaj.broj_mjesta, lista->dogadjaj.broj_prodatih_ulaznica, lista->dogadjaj.kupuje_na_ime, lista->dogadjaj.ID);

            lista = lista->next;
        }
        fclose(f);
        return 1;
    }
    else {
        printf("Neuspjesno brisanje.\n");
        return 0;
    }
}
void brisi(ListaDogadjajaG** lista) {

	while(*lista){
	ListaDogadjaja* pom = *lista;
	*lista = pom->next;
	free(pom);
	}
}
