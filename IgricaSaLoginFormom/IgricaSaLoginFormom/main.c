////Mladen Laloviæ NRT 52/20

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


struct korisnik{

	char ime[50];
	char email[50];
	char password[50];
	char username[50];

};

void uzimanjePodataka(char karakter[50]); /*funkcija uzimanjePodataka sluzi kako bi pokupila podatke koje korisnik unese. Poziva se u funkciji reg(). Ima argument char koji uzima karaktere koje korisnik unese*/
char pravljenjeUsername(char email[50], char username[50]); /*funkcija pravljenjeUsername sluzi kako bi od emaail adrese napravila username. Poziva se u funkciji reg(). Ima argumente char email i username. iz email cemo generisati username, a u username cemo sacuvati izgenerisani username*/
void uzimanjeSifre(char sifra[50]); /*funkcija uzimanjeSifre sluzi kako bi uzela sifru u formatu ****. Poziva se u funkciji reg() i login(). Ima argument char sifra koja prikuplja sifru i zamenjuje je sa znakom *.*/
void login(); /*funkcija login sluzi kako bi prikupila podatke za logovanje, uzima podatke iz datoteke, kako bi korisnik mogao da nastavi u rad sa aplikacijom. Poziva se u main funkciji i u reg() funkciji. Nema prosledjivanja argumenata*/
void reg(); /*funkcija reg()* sluzi kako bi korisnik napravio svoj racun, cuvaju se bodaci u datoteci. Poziva se u main funkciji i u login() funkciji. Nema argumente za prosledjivanje */
int SumaJedinica(int num); /*funkcija SumaJedinica sluzi kako bi svaki karakter koji je unet napravila kao zbirni broj. Poziva se u funkciji igrica(). Ima argument koji prosledjuje a to je int num za izracunavanje sume */
void igrica(); /*funkcija igrica() sluzi da izracunavanje procenta poklapanja dva para. Poziva se u funkciji main() i u login(). Nema prosledjivanja vrednosti */

main(){
	
	int opcija;

	XY:

	system("color 70"); /*sluzi za definisanje boje*/
	printf("\n\t\t\t\t Dobro dosli\n\n");
	puts("Izaberite zeljenu opciju koju hocete:");
	puts("1. Registracija");
	puts("2. Prijava");
	puts("3. Igrica");
	puts("4. Izlaz");

	printf("\nIzabrali ste:\t");
	scanf("%d", &opcija);
	fflush(stdin);
	
	switch(opcija)
	{
	case 1: 
		reg();
		break;
	case 2:
		login();
		break;
	case 3:
		login();
		igrica();
		break;	
	case 4:
		printf("\nHvala Vam sto ste nas posetili!\n");
		break;
	default:
		system("cls");
		goto XY;
	}
}


void uzimanjePodataka(char karakter[50])
{
	fgets(karakter,50,stdin);
	karakter[strlen(karakter)-1] = 0; /*Brisanje praznog znaka na kraju imena karaktera, u slucaju da je novi red*/
}
char pravljenjeUsername(char email[50], char username[50])
{
	/*primer123@gmail.com uzimacemo sve ispred @*/
	int i=0;
	for(i=0; i<strlen(email); i++)
	{
		if(email[i] == '@')
		{ 
			username[i] = '\0';
			break;
		}
		else  username[i] = email[i];
	}
return 0;
}
void uzimanjeSifre(char sifra[50])
{
	int i=0;
	char ch;
	while(1)
	{
		ch = getch();
		if(ch == 13)
		{ /*Kada je enter pritisnut*/
			sifra[i] = '\0';
			break;
		}
		else if(ch == 8)
		{ /*Kada koristi backspace*/
			if(i>0)
			{
				i--;
				printf("\b \b");
			}
		}
		else
		{ /*Zamena za karakter **/
			sifra[i++] = ch;
			printf("* \b");
		}
	}
}
void reg()
{
	FILE *f;
	struct korisnik k;
	char sifra2[50+1];
	int izborR;
		
	system("cls");
	printf("\n\n\t\t\tDobro dosli u registraciju\n\n");
	printf("Unesite Vase ime:\t");
	uzimanjePodataka(k.ime);
	printf("Unesite Vas mejl:\t");
	uzimanjePodataka(k.email);
	/*printf("\n%s",k.email);*/
	printf("Unesite Vasu sifru:\t");
	uzimanjeSifre(k.password); 
	/*printf("%s\n", k.password); provera rada sifre*/
	printf("\nPotvrdite sifru:\t");
	uzimanjeSifre(sifra2);

	if(!strcmp(k.password,sifra2)) /*sluzi da proveri da si se ponovljena sifra poklapa sa sifrom iz strukture*/
	{
		pravljenjeUsername(k.email,k.username);
		f = fopen("korisnik.txt", "ab+");
		if(f == NULL)
			{
				puts("Neuspelo otvaranje datoteke");
				exit(1);
			}
		fwrite(&k,sizeof(struct korisnik), 1, f);
		if(fwrite != 0)
			{
				printf("\n\nRegistracija uspesna, tvoj username je  %s\n\n", k.username);
				fclose(f);
				puts("Zelite li da se prijavite? Pritisnite 1 za DA ili 2 za NE");
				scanf("%d",&izborR);
				switch(izborR)
				{
				case 1: 
					system("cls");
					login();
					break;
				case 2:
					printf("\n\nHvala vam sto ste se registrovali\n");
					break;
				default: 
					puts("Prava opcija nije izabrana");
					break;
				}
				
			}
			else 
				printf("\nGreska! Nesto je poslo naopako! :/ \n");
	
	}
	else{
			puts("\n\nSifre nisu iste\n");
			Beep(600, 400);/*Ukuliko sifra nije tacna daje zvucni signal frekvencije 600 i trajanja 400*/
			printf("\nProbajte ponovo pritiskom na bilo koji taster\n");
			getch();
			reg();
		}
	
}
void login()
{
	FILE *f;
	struct korisnik k;
	char username[50+1],sifr[50+1];
	int nadjenKorisnik = 0; /*inicijalizacija na 0, kako bi mogli da znamo da li je korisnik unet u datoteku, ona se menja ukoliko korisnik postoji*/

	system("cls");
	printf("\n\n\t\t\tDobro dosli u prijavljivanje\n");
	printf("\t\tPrijavljivanjem cete pristupiti nasoj igrici\n");
	fflush(stdin);
	printf("\nUnesite Vas username:\t");
	uzimanjePodataka(username);
	printf("Unesite Vasu sifru:\t");
	uzimanjeSifre(sifr);
			
	f = fopen("korisnik.txt","r");
	while(fread(&k,sizeof(struct korisnik),1,f))
	{
		if(!strcmp(k.username,username))
		{
			if(!strcmp(k.password,sifr))
			{
				system("cls");
				printf("\n\t\t\t\tDobro dosli %s",k.ime);
				printf("\n\n|Ime:\t\t%s",k.ime);
				printf("\n|Email:\t\t%s",k.email);
				printf("\n|Username:\t%s\n\n",k.username);
				printf("\n\nUnesite enter kako bi zapoceli igricu\n");
				printf("Drugim karakterom izlazite iz programa\n");
				if(getchar() == '\n')
					igrica();
				else
					printf("Hvala na prijavljivanju\n");
					exit(1);
			}
			else
			{
				printf("\n\nNetacna sifra!\n");
				Beep(800,300);
				printf("\nProbajte ponovo\n");
				printf("\n\nUnesite enter kako bi probali ponovo\n");
				if(getchar() == '\n')
					login();
				else
					exit(1);
			}
			nadjenKorisnik = 1;
		}
	}
	if(!nadjenKorisnik)
	{
		printf("\n\nKorisnik nije registrovan!\n");
		Beep(800,300);
		printf("Pritisnite bilo koji karakter da se registrujete\n");
		getch();
		reg();
	}
	fclose(f);
}
int SumaJedinica(int num)
{
    int sum = 0;
    while (num > 0) {
        sum += (num % 10); /*generalni nacin za zbir sume cifara od nekog broja*/
        num /= 10;
    }
    return sum;
}

void igrica()
{
	char *tvojeIme, *partnerIme;
    int sum, sum1, i, izbor, brSlova;
    float procenat = 0;

	system("cls");
	printf("\n\n\t\t\tDobro dosli u igricu procenat para\n\n");
	do {
	printf("Koliko slova ima Vase ime?\n");
	scanf("%d", &brSlova);
	fflush(stdin);

	tvojeIme = malloc(sizeof(char) * brSlova);

	if(tvojeIme == NULL)
	{
		printf("\nNeuspela dodela memorije\n");
		exit(1);
	}

    printf("\nUnesite Vase ime:\t ");
    fflush(stdin);
    gets(tvojeIme);
	printf("\n\n");

	printf("Koliko slova ima osoba sa kojom hocete da provetite slaganje?\t\n");
	scanf("%d", &brSlova);
	fflush(stdin);

	partnerIme = malloc(sizeof(char) * brSlova);

	if(partnerIme == NULL)
	{
		printf("\nNeuspela dodela memorije\n");
		exit(1);
	}

    printf("\nUnesite ime osobe za slaganje:\t ");
    fflush(stdin);
    gets(partnerIme);
	printf("\n\n");

    sum = 0;
    for (i = 0; i < (strlen(tvojeIme)); i++) {
        sum += tolower(tvojeIme[i]);
    }

    sum1 = 0;
    for (i = 0; i < (strlen(tvojeIme)); i++) {
        sum1 += tolower(partnerIme[i]);
    }

    procenat = (SumaJedinica(sum) + SumaJedinica(sum1)) + 40;
    if (procenat > 100)
        procenat = 100;

    printf("Tvoj procenat slaganja sa unetom osobom je: %.02f\n\n", procenat);

    printf("Da li zelite da izracunate sa nekim drugim (ukoliko ne zelite 0 za izlaz) ?: ");
    scanf("%d", &izbor);
	fflush(stdin);

} while (izbor != 0);

free(tvojeIme);
free(partnerIme);

printf("\n\nHvala Vam sto ste igrali\n\n");
exit(1);
}