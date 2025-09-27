//
// Created by Vanessa on 17/09/2025.
//

#ifndef VARIOSARCH_FUNCIONES_H
#define VARIOSARCH_FUNCIONES_H
#include "utils.h"
void openArchive(ifstream &arch, const char *nombArch);
void openReport(ofstream &archRep, const char *nombArch);
void elaborarReporte(const char *nombArch1,const char *nombArch2,const char *nombArch3);
void  leerImprimirArch(ifstream &archTran,ifstream &archCom,ofstream &archRep);
void datosCabecera(int i,int dni, ifstream &archCom,ofstream &archRep);
void  leerNombre(ifstream &archCom,ofstream &archRep);
void to_upperCase(char &c);
void imprimirTitulo(ofstream &archRep);
void imprimirSubtitulos(ofstream &archRep);
void imprimirLinea(int cant,char car,ofstream &archRep);
void leerDatos(int &cantL,int &cantG,int &cantMG, double &multaG,double &multaL,double &multaMG,
    ifstream &archCom,ifstream &archTran,ofstream &archRep,int &leve,int &grave,int &muyGrave,double &montoL,
    double &montoG, double &montoMG);
int leerValorTemporal(char tipo,ifstream &arch,ofstream &archRep);
int compactarValor(char tipo, ifstream &arch,int dd_hh,int mm_min,int aa_seg,ofstream &archRep);
void buscarInfraccion(double &multa,char &gravedad,int infraccCom,ifstream &archTran,ofstream &archRep);
void imprimirInfracc(char gravedad, double multa,ifstream &archTran,ofstream &archRep);
void imprimirValorTemporal(int valor, ofstream &archRep,char tipo);
void decompactarValor(int &dd_hh, int &aa_seg, int &mm_min,char tipo,int valor);
void imprimirVehiculo(char vehiculo,ofstream &archRep);
void imprimirGravedad(char gravedad,ofstream &archRep) ;
void resumenPersonal(int &cantL,int &cantG,int &cantMG,char gravedad,double multa,ofstream &archRep,double &multaG,
    double &multaL,double &multaMG,int &leve,int &grave,int &muyGrave,double &montoL,double &montoG, double &montoMG);
void imprimirColumnas4(char vehiculo,int placaNum1,int placaNum2,int fechaInfracc,int infraccCom,ofstream &archRep);
void imprimirResumenPersonal(int &dniMayor,int &dniMenor,double &montoMenor,double &montoMayor,int dni,int cantL,
    int  cantG,int  cantMG,double  multaG,double  multaL,double  multaMG,ofstream &archRep);
void sumasTotales(int cantL,int cantG,int cantMG,double multaG,double multaL,double multaMG,double &multaTotal,int &cantTotal);
void imprimirResumenFinal(int leve,int grave,int muyGrave,double montoL,double montoG,double montoMG,ofstream &archRep);
void  imprimirComparaciones(int dniMayor, int dniMenor,double  montoMenor,double montoMayor,ofstream &archRep);
#endif //VARIOSARCH_FUNCIONES_H