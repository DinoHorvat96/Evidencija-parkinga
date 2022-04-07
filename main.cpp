#include <stdio.h>
#include <conio.h>
#include <math.h>

float pitagorinPoucak(float a, float b) {
	float suma=sqrt(pow(a,2)+pow(b,2)); // c=korjen(a^2+b^2)
	return suma;
}

int main() {
	float a, b, c;
	printf("Brojevi trebaju biti veci od 0!\n");
	printf("Unesi stranicu a: ");
	scanf("%f", &a);
	printf("Unesi stranicu b: ");
	scanf("%f", &b);
	printf("Unesi stranicu c: ");
	scanf("%f", &c);
	float suma=pitagorinPoucak(a, b);
	
	if (a>0 && b>0 && c>0) {
		if ((a==b) && (a==c) && (b==c)) {
			printf("Trokut sa stranicama a(%f), b(%f) i c(%f) je istostranican.", a, b, c);
		}
		else if (suma==c) {
			printf("Trokut sa stranicama a(%f), b(%f) i c(%f) je pravokutan.", a, b, c);
		}
		else if ((a==b) || (a==c) || (b==c)) {
			printf("Trokut sa stranicama a(%f), b(%f) i c(%f) je jednakokracan.", a, b, c);
		}
		else if ((a!=b) && (a!=c) && (b!=c)) {
			printf("Trokut sa stranicama a(%f), b(%f) i c(%f) je raznostranican.", a, b, c);
		}
	}
	else {
		printf("Stranice moraju biti vece od 0.");
	}
}
