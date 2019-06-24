#include <iostream>
#include <string.h>//permite utilizar strcat(char,char) strcpy(char,char);
#include <conio.h>// agrega la funcuion getch(); que es trabante de procesos
#include <stdlib.h>
#include <SDL.h>
#include "ManejoVentana.h"
#include "Estacion.h"
#include "Moneda.h"
#include "Mapa.h"
#include "Tren.h"
#include "VariablesFijas.h"

using namespace std;

int main(int argc,char *args[])
{
    //variables para capear los fps
    const int FPS = 120;
    const int frameDelay = 1000/FPS;
    //variables para bloquear el maximo de FPS.
    int frameStart;
    int frameTime;
    Ventana ventana;
    Moneda moneda;
    Tren tren;
    Estacion estacion;
    Mapa mapa;

    crearVentana(ventana);//creo ventana
    InicializarVentana(ventana,"ClashUNLa",pos,pos,ancho,alto,SDL_WINDOW_RESIZABLE);//la inicializo
    crearEstacion(estacion,ventana.p_render);//creo estacion
    crearMoneda(moneda,ventana.p_render);
    crearMapa(mapa,ventana.p_render);
    crearTren(tren,"c1");

    bool doOnce = true;
    bool turnoMoneda = true;
    int ciclosRender = 0;
    int turno = getTurno(ventana);
    while(getRun(ventana)){


                renderClear(ventana);
                dibujarMapa(mapa,ventana.p_render);
                while(doOnce){
                    renderPresent(ventana);
                    doOnce = false;
                }
                //tomo el tiempo del primer frame
                frameStart = SDL_GetTicks();
                dibujarMapa(mapa,ventana.p_render);
                dibujarEstacion(estacion,ventana.p_render);
                dibujarMoneda(moneda,ventana.p_render,turnoMoneda);
                if(ciclosRender==0){
                    ManejarEventos(ventana,tren);
                }
                dibujarTren(tren,ventana.p_render);

                renderPresent(ventana);
                evaluarColiciones(ventana,mapa,tren);

                frameTime = SDL_GetTicks() - frameStart;
                //si lo que tarda es mas rapido de lo necesario para realizar la cantidad de FPS que asigne , realizara un delay
                if(frameDelay> frameTime){
                    SDL_Delay(frameDelay - frameTime);
                }
                ciclosRender++;
                turnoMoneda= false;
                if(ciclosRender==40){
                    ciclosRender = 0;
                    setTurno(ventana,getTurno(ventana)+1);
                    turnoMoneda= true;
                }

    }
    destruirEstacion(estacion);
    destruirTren(tren);
    destruirVentana(ventana);
    return 0;
}


