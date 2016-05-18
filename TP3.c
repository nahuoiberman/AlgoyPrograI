#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
typedef struct record{
    char *recordName_;
    int duration_;
    }record_t;
typedef struct album{
    record_t **album_;
    char *nombre_;   
    int recordnumber_;
    }album_t;
typedef struct band{
    record_t **band_;
    char *nombre_;
    int recordnumber_;
    }band_t;
typedef struct artist{
    record_t **artis_;
    char *nombre_;
    int recordnumber_;
    }artist_t;
typedef struct lista{
    record_t *lista_;
    int cant_;
    }lista_t;

int cargar(lista_t *lista,album_t **albumes,artist_t **artistas){
    char aux[100];
    char *ptr;
    int i=0;
    fgets(aux,100,stdin);
    aux[strlen(aux)-1] = '\0';
    while(strcmp(aux,"#newSong")==0){
        fgets(aux,100,stdin);
        lista->lista_=(record_t *)realloc(lista->lista_,sizeof(record_t)*(i+1));
        ptr=strtok(aux," ");
        ptr=strtok(NULL,"\n");
        lista->lista_[i].recordName_=(char *)malloc(sizeof(char)*strlen(ptr));        
        strcpy(lista->lista_[i].recordName_,ptr);
        i++;
        fgets(aux,100,stdin);
         aux[strlen(aux)-1] = '\0';
        }
    return i;
    }
int main(int argc, char *argv[]) {
    char *tok;
    lista_t lista;
    lista.lista_=NULL;
    album_t *albumes;
    artist_t *artistas;
    /*
    tok=strtok(argv[1],DELIM_I);
    if(strcmp(tok,LISTSONG)==0) {
        listSongs();
    }
    else if (strcmp(tok,LISTSONG)==0) {
        listAlbums();
    }*/
    lista.cant_=cargar(&lista,&albumes,&artistas);
    printf("%s\n",lista.lista_[0].recordName_);
    printf("%s\n",lista.lista_[1].recordName_);
    free(lista.lista_[0].recordName_);
    free(lista.lista_[1].recordName_);    
    free(lista.lista_);    
    return 0;
    }
