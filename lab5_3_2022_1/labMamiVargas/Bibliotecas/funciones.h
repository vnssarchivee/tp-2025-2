//
// Created by Vanessa on 05/10/2025.
//

#ifndef LABMAMIVARGAS_FUNCIONES_H
#define LABMAMIVARGAS_FUNCIONES_H
#include "utils.h"
void abrirArch(ifstream &arch, const char *nombArch);
void abrirArchRep(ofstream &arch, const char *nombArch);
void cargarClientes(const char *nombArch,int *dniClientes,int *telfClientes,int &cantClientes);
void ignorar(ifstream &arch, char until);
void ordenarDatos(int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes);
void intercambiarInt(int &datoI,int &datoJ);
void intercambiarDouble(double &datoI,double &datoJ);
void pruebaCargarClientes(const char *nombArch,int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes);
void procesarPedidos(const char *nombArch,int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes,
    int *codProducto,double *cantPedidaProducto,double *precioProducto,double *totalProducto,int &cantProducto);
int buscarProducto(int codigoProducto,int *codProducto,int cantProducto);
void imprimirReporte(const char *nombArch,int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes,
    int *codProducto,double *cantPedidaProducto,double *precioProducto,double *totalProducto,int cantProducto);
void imprimirReporte(const char *nombArch,int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes,
    int *codProducto,double *cantPedidaProducto,double *precioProducto,double *totalProducto,int cantProducto);
void imprimirLinea(char car, int cant, ofstream &archRep);
void imprimirTitulo(ofstream &archRep);
void imprimirSubtitulo2(ofstream &archRep);
int buscarPosCliente(int dniCli,int *dniClientes,int cantClientes);
void imprimirProductos(ofstream &archRep,int *codProducto,double *cantPedidaProducto,double *precioProducto,double *totalProducto,int cantProducto) ;
void ordenarClientes(int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes);
void ordenarProductos(int *codProducto,double *cantPedidaProducto,double *precioProducto,double *totalProducto,int cantProducto);
#endif //LABMAMIVARGAS_FUNCIONES_H