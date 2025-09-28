//
// Created by Vanessa on 27/09/2025.
//

#ifndef ERASMOONICHAN_FUNCIONES_H
#define ERASMOONICHAN_FUNCIONES_H
#include "utils.h"
void abrirArch(ifstream &arch,const char *nombArch);
int leerFecha(ifstream &arch );
int leerDuracion(ifstream &arch);
int leerDuracionReturn(ifstream &arch);
void abrirArchRep(ofstream &archRep,const char *nombArch);
void ignorar(ifstream &arch,char until);
void imprimirFecha(int valor, ofstream &archRep);
void cargarCanciones(const char *nombArch,int *codCancion,int *duracion,int &cantCanciones);
void pruebaCargaCanciones(const char *nombArch,int *codCancion,int *duracion,int cantCanciones);
void cargarCanciones(const char *nombArch,int *codCancion,int *duracion,int &cantCanciones);
void  imprimirTiempo(int duracion,ofstream &archRepPrueba);
void print_time(ofstream &output, int s, bool in_days);
void cargarArtistas(const char *nombArch,int *fecha_debut,char *carCod,int *numCod,double *rating,int &cantArtistas);
void probarCargaArtistas(const char *nombArchRep,int *fecha_debut,char *carCod,int *numCod,double *rating,int cantArtistas);
void cargarReproducciones(const char *nombArch,int *fechaCancion,char *carCod,int *numCod,int *codCancion,int *duracion,int *numRepro,int *totalRep,
    int *tiempoTotalRep,double precioMil,double *revenue,int cantArtistas,int cantCanciones, int &cantRep,int *numReplayTotal);
void pruebaCargarReproducciones(const char *nombArch,int *fechaCancion,char *carCod,int *numCod,int *codCancion,
    int *duracion,int *numRepro,int *totalRep,int *tiempoTotalRep,double precioMil,double *revenue,int cantArtistas,
    int cantCanciones,double *rating, int cantRep, int *numReplayTotal);
int buscarArtista(char letra,int num,char *carCod,int *numCod,int cantArtistas);
int buscarCancion(int cancion,int *codCancion,int cantCanciones);
void imprimirLinea(int cant, char car,ofstream &archRep) ;
void imprimirTitulo(ofstream &arch,double precioMil);
#endif //ERASMOONICHAN_FUNCIONES_H