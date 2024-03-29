#ifndef ManejoVentana_h
#define ManejoVentana_h
#include <SDL.h>
#include <SDL_image.h>
#include "Tren.h"
/*Definicion del tipo de dato para manejo de ventana*/
/*
Atributos:
 *p_ventana-->puntero de tipo SDL_Window
 *p_render-->puntero de tipo SDL_Renderer
 *run
Axiomas:
 *p_ventana = 0
 *p_render = 0
 *run = true
*/
/*Tipo de estructura de la ventana*/
typedef struct{
    SDL_Window *p_ventana;
    SDL_Renderer *p_render;
    bool run;
    int ciclo;
    int turno;
}Ventana;
/*---------------------------------*/
/*
PRE: ventana no debe haber sido creada
POST: ventana creada con crearVentana
ventana: instancia sobre la cual se invoca la primitiva
*/
void crearVentana(Ventana &ventana);
/*---------------------------------*/
/*
PRE:ventana creada con crearVentana
POST: run seteado con el dato ingresado
ventana: instancia sobre la cual se invoca la primitiva
run dato ingresado
*/
/*---------------------------------*/
/*
PRE: ventana debe haber sido creada
POST: atributo turno de ventana seteado
ventana: instancia sobre la cual se invoca la primitiva
turno: valor que se va a setear
*/
void setTurno(Ventana &ventana,int turno);
/*---------------------------------*/
/*
PRE: ventana debe haber sido creada
POST: valor del turno devuelto
ventana: instancia sobre la cual se invoca la primitiva
*/
int getTurno(Ventana &ventana);
/*---------------------------------*/
/*
PRE: ventana debe haber sido creada
POST: atributo run seteado
ventana: instancia sobre la cual se invoca la primitiva
run: valor a setear
*/
void setRun(Ventana &ventana,bool run);
/*---------------------------------*/
/*
PRE:ventana creada con crearVentana
POST:devuelve el atributo run
ventana:instancia sobre la cual se invoca la primitiva
*/
bool getRun(Ventana &ventana);
/*---------------------------------*/
/*
PRE: ventana creada con crear
POST: ventana inicializada
ventana:instancia sobre la cual se invoca la primitiva
titulo,posx,posy,ancho,alto,flags datos ingresados
*/
bool InicializarVentana(Ventana &ventana,const char *titulo,int posx,int posy,int ancho,int alto,int flags);
/*----------------------------------*/
/*
PRE: ventana creada con crear
POST: manejo de distintos eventos
ventana:instancia sobre la cual se invoca la primitiva
*/
bool ManejarEventos(Ventana &ventana,Tren &tren);
/*----------------------------------*/
/*
PRE: ventana creada con crear
POST: render seteado
ventana:instancia sobre la cual se invoca la primitiva
*/
void renderClear(Ventana &ventana);
/*----------------------------------*/
/*
PRE: ventana creada con crear
POST: render seteado
ventana:instancia sobre la cual se invoca la primitiva
*/
void renderPresent(Ventana &ventana);
/*----------------------------------*/
/*
PRE: ventana creada con crear
POST: ventana actualizada
ventana:instancia sobre la cual se invoca la primitiva*/
void actualizar(Ventana &ventana);
/*----------------------------------*/
/*
PRE: ventana creada con crear
POST: ventana destruida
ventana:instancia sobre la cual se invoca la primitiva
*/
void destruirVentana(Ventana &ventana);
/*----------------------------------*/
/*
PRE: ventana creada con crear
POST: retorna el ciclo
ventana: instancia sobre la que actua la primitiva
*/
int getCiclo(Ventana &ventana);
/*----------------------------------*/
/*
PRE: ventana creada con crear
POST: seteado el ciclo
ventana: instancia sobre la que actua la primitiva
ciclo: valor a setear
*/
void setCiclo(Ventana &ventana,int ciclo);
bool pagarBandidoTecla(Ventana &ventana);

#endif // ManejoVentana_h
