#include <stdio.h>
#include <conio.h>
#include <malloc.h>

// definicija strukture za evidenciju vozila
typedef struct {
	char marka[20+1];
	char modelRijec[20+1];
	int modelBroj;
	int godina;
	char reg1[2+1];
	int reg2;
	char reg3[2+1];
	int vrijeme;
} Auti;

// definicija strukture za listu
typedef struct Celija {
	Auti element;
	struct Celija *sljedeca;
} Lista;

// funkcija vraca zadnji element liste 
Lista *zadnjaCelija(Lista *pokLista) {
	Lista *celija;
	celija = pokLista;
	do{
		celija = celija->sljedeca;
		if (celija==NULL) return pokLista;
		if (celija->sljedeca ==NULL) return celija;
	}
	while (celija->sljedeca !=NULL);
}

void ubaci (Auti x, Lista *pozicija_ubacivanja) {
	Lista *privremeno;
	privremeno = pozicija_ubacivanja->sljedeca;
	pozicija_ubacivanja->sljedeca = (Lista*)  malloc(sizeof(Lista));
	pozicija_ubacivanja->sljedeca->element = x;
	pozicija_ubacivanja->sljedeca->sljedeca=privremeno;
}


void ispis (Lista *lista) {
	Lista *celija;
	int brojac=0;
	celija = lista;
	printf("\nR.Br.\tMarka\tModel\tGodina\tRegistracija\tVrijeme\n");
	while (celija->sljedeca!=NULL){
		brojac=brojac+1;
		celija = celija->sljedeca;
		printf("%d.\t%s\t%d%s\t%d\t%s-%d-%s\t%d\n", brojac, celija->element.marka, celija->element.modelBroj, celija->element.modelRijec, celija->element.godina, celija->element.reg1, celija->element.reg2, celija->element.reg3, celija->element.vrijeme);
	}
}

//funkcija koja sprema u datoteku
void spremiUDatoteku(char *nazivDatoteke, Lista *pokStrPodataka) {
	FILE *datoteka;
	datoteka = fopen(nazivDatoteke, "wb");
	if(datoteka == NULL) {
		printf("Problem u otvaranju datoteke!");
	}
	else {
		fwrite(pokStrPodataka, sizeof(*pokStrPodataka),1, datoteka);
	}
	fclose(datoteka);
}

//funkcija koja cita iz datoteke
void procitajIzDatoteke(char *nazivDatoteke, Lista *pokStrPodataka) {
	FILE *datoteka;
	
	datoteka = fopen(nazivDatoteke, "rb");
	if (datoteka == NULL) {
		printf("Problem u otvaranju datoteke!");
	}
	else {
		fread(pokStrPodataka,sizeof(*pokStrPodataka),1,datoteka) ;
	}    
	fclose(datoteka);   
}

//funkcija za brisanje
/*void obrisi(int pozicija_brisanja, Lista *pokLista) {
	int pozicija;
	if ((pozicija_brisanja>pokLista->zadnji) || (pozicija_brisanja<0))
		printf("Pozicija ne postoji!");
	else {
		pokLista->zadnji--;    
		for (pozicija=pozicija_brisanja; pozicija<=pokLista->zadnji; pozicija++)
			pokLista->elementi[pozicija] = pokLista->elementi[pozicija+1];
	}
}*/



int main () {
	Auti korisnickiAuti;
	
	Lista *listaGaraza;
	listaGaraza = (Lista*) malloc(sizeof(Lista));
	listaGaraza->sljedeca = NULL;
	
	procitajIzDatoteke ("evidencija.hor", listaGaraza);
	
	int izbor;
	//glavni izbornik
	do {
    	printf("\nEVIDENCIJA AUTOMOBILA");
    	printf("\nOdaberite jednu od radnji:");
		printf("\n\n1 - Ispis podataka\n2 - Unos novog reda podataka\n3 - Brisanje\n4 - Izlaz");
		printf("\nOdabir: ");
		scanf("%d", &izbor);

		if (izbor==1) {
			ispis (listaGaraza);
		}
		
		else if (izbor==2) {
			printf("NOVI UNOS:\n");
			printf("Unesite marku vozila: ");
			scanf("%s", &korisnickiAuti.marka);
			
			printf("Unesite model vozila ako sadrzi brojeve (u protivnom ostavite prazno): ");
			scanf("%d", &korisnickiAuti.modelBroj);
			
			printf("Unesite model vozila ako sadrzi rijeci (u protivnom ostavite prazno): ");
			scanf("%s", &korisnickiAuti.modelRijec);
			
			printf("Unesite godinu vozila: ");
			scanf("%d", &korisnickiAuti.godina);
			
			printf("Unesite prvu registraciju vozila (npr. 'RI' od RI-1234-AB): ");
			scanf("%s", &korisnickiAuti.reg1);
			
			printf("Unesite drugu registraciju vozila (npr. '1234' od RI-1234-AB): ");
			scanf("%d", &korisnickiAuti.reg2);
			
			printf("Unesite trecu registraciju vozila (npr. 'AB' od RI-1234-AB): ");
			scanf("%s", &korisnickiAuti.reg3);
			
			//printf("Upisite registraciju vozila: ");
			//scanf("%s-%d-%s", &korisnickiAuti.reg1, &korisnickiAuti.reg2, &korisnickiAuti.reg3);
			
			printf("Unesite vremensko razdoblje parkinga (u satima): ");
			scanf("%d", &korisnickiAuti.vrijeme);
			
			ubaci (korisnickiAuti, zadnjaCelija(listaGaraza));
			spremiUDatoteku ("evidencija.hor", listaGaraza);
		}
		
		else if (izbor==3) {
			int unosBiranja;
			ispis(listaGaraza);
    		printf("\n\nUnesite redni broj unosa kojeg zelite obrisati: ");
			scanf("%d", &unosBiranja);
    		//obrisi(unosBiranja-1, &listaGaraza));
    		ispis(listaGaraza);
    		spremiUDatoteku("evidencija.hor", listaGaraza);
		}
		
		else if (izbor==4) {
			printf("Izlazak iz programa.");
		}
		
		else {
			printf("Krivi unos. Pokusajte ponovno.");
		}
	} while (izbor!=4);
}
