#include "PonistavanjeUlaznice.h"
#include "OtkazivanjeKupljeneUlaznice.h"
#include "LoadConfig.h"
void ponistavanjeUlaznice()
{
    int sifra_validna = 0;
    int broj_linije = 0;
    while (sifra_validna == 0)
    {
        printf("Unesite sifru ulaznice koju zelite da ponistite: ");
        scanf("%s", sifra_ulaznice);
        broj_linije = validacijaSifre(sifra_ulaznice);
        if (broj_linije > 0)
        {
            sifra_validna = 1;
        }
    }
    int line_number = 0;
    FILE* fptr1 = fopen(concat(CONFIG_DEV_FOLDER,"Ulaznice.txt"), "r");
    FILE* fptr2 = fopen(concat(CONFIG_DEV_FOLDER,"replica.txt"), "w");
    char curr = getc(fptr1);
    if (curr != EOF) { line_number = 1; }
    while (1)
    {
        if (broj_linije != line_number)
            putc(curr, fptr2);
        curr = getc(fptr1);
        if (curr == '\n') line_number++;
        if (curr == EOF) break;
    }
    fclose(fptr1);
    fclose(fptr2);
    const char* filename = "Ulaznice.txt";
    const char* pomocnifajl = "pomocni.txt";
    rename(concat(CONFIG_DEV_FOLDER, filename), concat(CONFIG_DEV_FOLDER, pomocnifajl));
    remove(concat(CONFIG_DEV_FOLDER, filename));
    rename(concat(CONFIG_DEV_FOLDER, "replica.txt"), concat(CONFIG_DEV_FOLDER, filename));
    remove(concat(CONFIG_DEV_FOLDER, pomocnifajl));
    obrisiLiniju(broj_linije);
    printf("Ulaznica je uspjesno ponistena! ");
}

int validacijaSifre(char* sifra)
{
    int broj_linije=0;
    int validna_sifra = 0;
    FILE* f;
    if (f = fopen(concat(CONFIG_DEV_FOLDER,"Ulaznice.txt"), "r"))
    {
        int lineLength = 255;
        char line[255];

        while (fgets(line, lineLength, f)) {

            broj_linije++;
            char delimiter[] = " ";
            char* prva_rijec = strtok(line, delimiter);
            if (strcmp(prva_rijec, sifra_ulaznice) == 0)
            {
                validna_sifra = 1;
                fclose(f);
                return broj_linije;
            }
        }
        if (validna_sifra == 0)
        {
            printf("Ulaznica sa datom sifrom ne postoji! \n");
            fclose(f);
            return 0;
        }
    }
    else
    {
        printf("Neuspjesno otvaranje datoteke.");
        return 0;
    }
    return 1;
}