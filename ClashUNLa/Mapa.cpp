#include "Mapa.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Bloque.h"

using namespace std;

void crearMapa(Mapa &mapa,SDL_Renderer *renderer){
    mapa.ancho = 800;
    mapa.alto = 600;
    mapa.col = mapa.ancho/40;
    mapa.fil = mapa.alto/40;
    mapa.textura = IMG_LoadTexture(renderer,"img/suelo.png");
    mapa.destino.x = 0;
    mapa.destino.y = 0;
    mapa.destino.w = mapa.ancho;
    mapa.destino.h = mapa.alto;
    //mapa.bloques = crearBloques(mapa.fil,mapa.col);

    int id = 1;
    for(int i = 0 ; i<mapa.fil;i++){
        for(int j = 0;j< mapa.col;j++){
            mapa.bloques[i][j]=crearBloque(id,i+1,j+1);
            id++;
        }
    }
}
void dibujarMapa(Mapa &mapa,SDL_Renderer *renderer){
    SDL_RenderCopy(renderer,mapa.textura,NULL,&mapa.destino);

}
void destruirMapa(Mapa &mapa){

    SDL_DestroyTexture(mapa.textura);
}

void mostrarBloquesMapa(Mapa &mapa){
    for(int i = 0;i<mapa.fil;i++){
        for(int j=0 ;j<mapa.col;j++ ){
            mostrarBloque(mapa.bloques[i][j]);
        }
    }
}


void evaluarColiciones(Lista &lista,Ventana &ventana,Mapa &mapa,Tren &tren){
    evaluarLimites(ventana,mapa,tren);
    evaluarGrid(lista,ventana,mapa,tren);
}

void evaluarLimites(Ventana &ventana,Mapa &mapa,Tren &tren){
    if((tren.rectImag.x<0)||((tren.rectImag.x+40)>800)||(tren.rectImag.y<0)||((tren.rectImag.y+40)>600)){
        setRun(ventana,false);
        cout<<tren.rectImag.x<<endl;
        cout<<tren.rectImag.y<<endl;
    }
}

void evaluarGrid(Lista &lista,Ventana &ventana,Mapa &mapa,Tren &tren){
    Bloque bloque = mapa.bloques[tren.f][tren.c];
    if(bloque.ocupado){
            if(verificarTipo(tren,"c1")){
                if(bloque.estacion!=NULL&&tren.monedas>0){
                    colisionEstacion(lista,tren);
                }
                if(bloque.moneda!=NULL){
                    colisionMoneda(lista,tren,bloque);
                }
                if(bloque.mina!=NULL){
                    colisionMina(lista,tren,bloque);
                }
            }
    }
}

void colisionEstacion(Lista &lista,Tren &tren){
    cout<<"Colision estacion"<<endl;
    int kilos = tren.monedas*5;
    tren.monedas=0;
    Tren* trenAux = new Tren;
    PtrNodoLista aux = ultimo(lista);
    Tren* trenAnterior = ((Tren*)aux->ptrDato);
    crearTren(*trenAux,"c2",trenAnterior->anterior.direccionAnterior,trenAnterior->anterior.filaAnterior,trenAnterior->anterior.columnaAnterior,kilos);
    adicionarFinal(lista,trenAux);

}

void colisionMoneda(Lista &lista,Tren &tren,Bloque &bloque){
    setMonedas(tren,getMonedas(tren)+1);
    bloque.moneda->activa=false;
    liberarBloque(bloque);
}

void colisionMina(Lista &lista,Tren &tren,Bloque &bloque){
    Mina *mina = getMina(bloque);
    TiposMinerales tipo = getMina(bloque)->tipo;

    bool encontrado = false;
    bool terminado = false;

    if(getCajasDisponibles(*mina)>0){
    //cursor empieza desde el segundo vagon
    //verificarTrenesConMinerales(lista,bloque);
    PtrNodoLista cursor = siguiente(lista,primero(lista));
    while((cursor!=finLista())&&(!encontrado)){
        Tren *trenAux = new Tren;
        trenAux = (Tren*) cursor->ptrDato;
        //compara el tipo mineral del vagon con el mineral de la mina
        //si son iguales , de tener espacio agrega los kilos ocupados
        //sino resetea la mina
        if(CompararMinerales(getTipoMineral(*trenAux),tipo)){
            int caja = entregarCaja(*mina);
            if(getKilosOcupados(*trenAux)+caja<=getKilos(*trenAux)){
                setKilosOcupados(*trenAux,getKilosOcupados(*trenAux)+caja);
                encontrado = true;

            }
        }
    cursor=siguiente(lista,cursor);
    }
    //en caso que no haya tren disponible
    PtrNodoLista cursor2 = siguiente(lista,primero(lista));
    while((cursor2!=finLista())&&((!encontrado)&&(!terminado))){

        Tren *trenAux2 = new Tren;
        trenAux2 = (Tren*) cursor2->ptrDato;

        //compara el tipo mineral del vagon con el mineral de la mina
        //si son iguales , de tener espacio agrega los kilos ocupados
        //sino resetea la mina
        if(CompararMinerales(getTipoMineral(*trenAux2),vacio)){
            setTipoMineral(*trenAux2,tipo);

            int caja = entregarCaja(*mina);
            if(getKilosOcupados(*trenAux2)+caja<=getKilos(*trenAux2)){
                setKilosOcupados(*trenAux2,getKilosOcupados(*trenAux2)+caja);
                encontrado = true;
            }
            terminado = true;
        }
    cursor2=siguiente(lista,cursor2);
    }

    }
    else{
        resetearCajasMina(*mina);
    }

}


