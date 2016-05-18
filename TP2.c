#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define ERRARCHIVO "Archivo no válido\n"
#define MAX 100
#define PRND 1
#define PORD 2
#define PREC 3
#define ADD 4
#define LST 5
#define SCH 6
#define EXIT 7
#define SEARCH "Ingrese su busqueda aqui\n"
#define CORR "El archivo fue agregado correctamente.\n"
#define BUSQ "Ingrese el nombre de su archivo\n"
#define BIENV "¡Bienvenido a CMD-Player!"
#define MENU "\n1. Play Randomly.\n2. Play in order.\n3. Play record.\n4. Add record\n5. List\n6. Search\n7. Exit\n"
#define ERROR "Error: Esa no es una opción válida, saliendo.\n"
#define CHAU "Gracias por usar nuestro programa. All rights reserved.\n"
#define CANT "¿Cuántas canciones quieres escuchar?\n"

 /*-------------------------PLAY RECORD---------------------------------------*/
/*Recibe una cadena de caracteres y reproduce un archivo con ese nombre*/
void playRecord(char *lista)
{
    
	char* cmd[3];
	int pid;
	cmd[0] = "mpg123";
	cmd[1] = lista;
	cmd[2] = NULL;
	pid = fork();
	if (!pid)
    	execvp(cmd[0], cmd);
	waitpid(pid, NULL, 0);
}

/*-------------------------ERROR---------------------------------------*/
  /*Imprime mensaje de error y sale del programa*/
void error()
{
    printf(ERROR);
    exit(0);
}

/* --------------------------LIST------------------------------ */
/* Imprime la lista actual de canciones */
void list(char lista[MAX][MAX], int *cantidad)
{
	int i;
	for(i=0;i<(*cantidad);i++) printf("%d-%s\n",i+1,lista[i]);
}

/*-------------------------PLAY ORDER---------------------------------------*/
  /*Reproduce en orden toda la lista de canciones*/
void playOrder(char lista[MAX][MAX], int *cantidad)
{
    int crec = 0;
    while (crec < (*cantidad))
    {
   	 playRecord(lista[crec]);
   	 crec += 1;
    }
}

/*-------------------------PLAY RANDOM---------------------------------------*/
  /*Pide un numero y reproduce esa cantidad de canciones de manera aleatoria*/

void playRandom(char lista[MAX][MAX], int *cantidad)
{
    int cant=0, crec, ran;
    printf(CANT);
    scanf("%d", &cant);
    if (cant < 1) error();
    srand(time(NULL));
    crec = 0;
    while (crec < cant)
    {
   	 ran = rand() % (*cantidad);
   	 playRecord(lista[ran]);
   	 crec += 1;
    }
}

  /*-------------------------PLAY SINGLE SONG---------------------------------------*/
  /*Imprime la lista de canciones, pide un numero y reproduce esa cancion*/
void playSingle(char lista[MAX][MAX], int *cantidad)
{
    int elec;
    list(lista, cantidad);
    scanf("%d", &elec);
    if (elec < 1 || elec > (*cantidad)) error();
    playRecord(lista[elec-1]);
}

/*-------------------------CLEAN STDIN----------------------------------*/

void cleanstdin(void)
{
	int c;
	do{
    	c=getchar();
	}while(c!='\n' && c!=EOF);
}

/* ------------------------------FILE CHECK------------------------------------ */
/* Chequea que el archivo exista, se pueda leer, editar y ejecutar, devuelve una variable de control para saber si al menos existe, se puede leer y editar */
int filecheck(const char file_Name[])
{
	int control=0;    
	if(!access(file_Name,F_OK))
	{
    	printf("The file %s was found\n", file_Name);
    	control++;
	}   	 
	else printf("The file %s was not found\n", file_Name);
	if(!access(file_Name,R_OK))
	{
    	printf("The file %s can be readed\n", file_Name);
    	control++;   	 
	}
	else printf("The file %s cannot be readed\n", file_Name);
	if(!access(file_Name,W_OK))
	{    
    	printf("The file %s can be edited\n",file_Name);
    	control++;
	}    
	else printf("The file %s cannot be edited\n", file_Name);
	if(!access(file_Name,X_OK))
	{    
    	printf("The file %s was executable\n", file_Name);
    	control++;
	}   	 
	else printf("The file %s was not executable\n", file_Name);
	return control;
}

/* ------------------------------ADD SONG---------------------------------- */
/* Agrega nuevas canciones a la lista, chequeando si existe y se puede leer */
void addsong(char lista[MAX][MAX],int *cantidad)
{    
	const char *file;
	char filee[MAX];
	printf(BUSQ);    
	fgets(filee,sizeof(filee),stdin);       	 
	filee[strlen(filee)-1]='\0';       	 
	file=filee;
	if(filecheck(file)>=3)
	{
        strcpy(lista[(*cantidad)],filee);    
    	*cantidad +=1;
        printf(CORR);
 	}
else printf(ERRARCHIVO);    
}

/* ------------------------------SEARCH----------------------------------- */
/* Busca en la lista coincidencias con lo ingresado por el usuario y las imprime*/
void search(char lista[MAX][MAX], int *cantidad)
{
	char busqueda[MAX];    
	int cancion,letra_cancion;
	int alguna_coinc=0,coinc=0;
	printf(SEARCH);
	fgets(busqueda,sizeof(busqueda),stdin);

	busqueda[(strlen(busqueda)-1)]='\0';  /* borra el \n */

	for(cancion=0;cancion<(*cantidad);cancion++)  /* pasa por todas las canciones de la lista */
	{
    	coinc=0;
    	for(letra_cancion=0;letra_cancion<strlen(lista[cancion]);letra_cancion++) /*pasa por todas las letras del nonbre de la cancion*/
    	{
        	if(busqueda[coinc]==lista[cancion][letra_cancion]) /* compara con la letra de la cancion con la letra de la busqueda */
        	{   
            	coinc++;
            	if (coinc>=(strlen(busqueda)))  /* si concidieron todas las letras de la buqueda */
            	{
                	printf("%s\n",lista[cancion]);
                	alguna_coinc=1;
                	letra_cancion=strlen(lista[cancion]);
            	}
        	}
        	else
        	{
            	if (coinc>=1) /* para volver a preguntar con la letra siguiente con la que empezo a conseguir coincidencias*/
                	letra_cancion -=coinc;
            	coinc=0;
        	}

    	}
   	 
	}

	if(alguna_coinc==0) printf("No se encontraron coincidencias \n");
}

  /*-------------------------MAIN---------------------------------------*/
  /* Consta de un bucle while, una variable de control y un switch. Imprime las opciones de menu y luego espera una respuesta para realizar la funcion correspondiente*/
int main ()
{
    int control = 1, cantidad=0, opc;
    char lista[MAX][MAX];
    printf(BIENV);
    while (control == 1)
    {
   	 opc=0;
   	 printf(MENU);
   	 scanf("%d", &opc);
   	 cleanstdin();
   	 switch(opc)
   	 {
   		 case PRND : playRandom(lista, &cantidad); opc=0; break;
   		 case PORD : playOrder(lista, &cantidad); opc=0; break;
   		 case PREC : playSingle(lista, &cantidad); opc=0; break;
   		 case ADD : addsong(lista, &cantidad); opc=0; break;
   		 case LST : list(lista, &cantidad); opc=0; break;
   		 case SCH : search(lista, &cantidad); opc=0; break;
   		 case EXIT : control = 0; opc=0; break;
   		 default : error();
   	 }
    }
    printf(CHAU);
    return 1;
}


