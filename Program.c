#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include <sys/wait.h>
#define BIENV "¡Bienvenido a CMD-Player!"
#define MENU "\n1. Play Randomly.\n2. Play in order.\n3. Play record.\n4. Exit\n"
#define CAN1 "1 - Evolución.mp3"
#define CAN2 "2 - A tu favor.mp3"
#define CAN3 "3 - Golosinas.mp3"
#define CAN4 "4 - Mi negra rubia.mp3"
#define CAN5 "5 - Sigue.mp3"
#define CAN6 "6 - Ya sabes.mp3"
#define CAN7 "7 - Candombe va.mp3"
#define CAN8 "8 - Natural.mp3"
#define CAN9 "9 - No quiero.mp3"
#define CAN10 "10 - Nada más.mp3"
#define CAN11 "11 - Dale che (una chacarera porteña).mp3"
#define CAN12 "12 - Efecto de sincronicidad.mp3"
#define CAN13 "13 - En movimiento.mp3"
#define CAN14 "14 - Bonus.mp3"
#define ERROR "Error: Esa no es una opción válida, saliendo.\n"
#define CHAU "Gracias por usar nuestro programa. All rights reserved.\n"
#define CANT "¿Cuántas canciones quieres escuchar?\n"

void playRecord(int i)
{
    char* playList[] = {CAN1 , CAN2 , CAN3 , CAN4 , CAN5 , CAN6 , CAN7 , CAN8 , CAN9 , CAN10 , CAN11 , CAN12 , CAN13 , CAN14};
    char* cmd[3];
    int pid;
    cmd[0] = "mpg123";
    cmd[1] = playList[i];
    cmd[2] = NULL;
    pid = fork();
    if (!pid)
        execvp(cmd[0], cmd);
    waitpid(pid, NULL, 0);
}

void error()
{
	printf(ERROR); 
	exit(0);
}

void playOrder()
{
	int crec = 0;
	while (crec < 14)
	{
		playRecord(crec);
		crec += 1;
	}
}

void playRandom()
{
	int cant, crec, ran;
	printf(CANT);
	scanf("%d", &cant);
	if (cant < 1 || cant>99) error();
	srand(time(NULL));
	crec = 0;
	while (crec < cant)
	{
		ran = rand() % 14;
		playRecord(ran);
		crec += 1;
	}
}

void playSingle()
{
	int elec;
	printf(CAN1"\n"CAN2"\n"CAN3"\n"CAN4"\n"CAN5"\n"CAN6"\n"CAN7"\n"CAN8"\n"CAN9"\n"CAN10"\n"CAN11"\n"CAN12"\n"CAN13"\n"CAN14"\n");
	scanf("%d", &elec);
	if (elec < 1 || elec > 14) error();
	playRecord(elec-1);
}


int main ()
{
	int control = 1;
	printf(BIENV);
	while (control == 1)
	{
		int opc;
		printf(MENU);
		scanf("%d", &opc);
		switch(opc)
		{
			case 1 : playRandom() ; break;
			case 2 : playOrder() ; break ;
			case 3 : playSingle(); break ;
			case 4 : control = 0; break;
			default : error();
		}
	}
	printf(CHAU);
	return 1;
}
