//
// Created by Vanessa on 17/09/2025.
//

#include "funciones.h"
void openArchive(ifstream &arch, const char *nombArch) {
    arch.open(nombArch,ios::in);
    if (!arch.is_open()) {
        cout<<"Error: No se pudo abrir "<<nombArch<<endl;
        exit(1);
    }
}

void openReport(ofstream &archRep, const char *nombArch) {
    archRep.open(nombArch,ios::out);
    if (!archRep.is_open()) {
        cout<<"Error: No se pudo abrir "<<nombArch<<endl;
        exit(1);
    }
}

void elaborarReporte(const char *nombArch1,const char *nombArch2,const char *nombArch3) {
    ifstream archCom,archTran;
    openArchive(archTran, nombArch1);
    openArchive(archCom, nombArch2);
    ofstream archRep;
    openReport(archRep, nombArch3);
    archRep<<fixed<<setprecision(2);
    imprimirTitulo(archRep);
    leerImprimirArch(archTran,archCom,archRep);
    archRep.close();
    archCom.close();
    archRep.close();

}
void imprimirTitulo(ofstream &archRep) {
    archRep<<setw((HEADER_WIDTH+60)/2)<<" "<<"MINISTERIO DE TRANSPORTE"<<endl;
    archRep<<setw((HEADER_WIDTH+50)/2)<<" "<<"MULTAS IMPUESTAS A LAS COMPANIAS"<<endl;
}

void imprimirSubtitulos(ofstream &archRep) {
    archRep<<"VEHICULOS INFRACCIONADOS: "<<endl;
    archRep<<setw(4)<<" "<<"PLACA"<<setw(12)<<" "<<"TIPO"<<setw(14)<<" "<<"FECHA"<<setw(9)<<" "<<"INFRACCION"<<setw(6)<<" "
    <<"GRAVEDAD"<<setw(15)<<" "<<"MULTA"<<setw(8)<<" "<<"DESCRIPCION"<<endl;
}

void imprimirLinea(int cant,char car,ofstream &archRep) {
    for (int i=0;i<cant;i++) archRep<<car;
    archRep<<endl;
}
void  leerImprimirArch(ifstream &archTran,ifstream &archCom,ofstream &archRep) {
    int continua,i=1,dni,cantL,cantG,cantMG, leve=0,grave=0,muyGrave=0,dniMayor,dniMenor;
    double montoL,montoG,montoMG,multaG=0,multaL=0,multaMG=0,montoMayor=0.0,montoMenor=99999.0;
    while (true) {
        archCom>>dni;
        if (archCom.eof()) break;
        datosCabecera(i,dni,archCom,archRep);
        leerDatos( cantL, cantG, cantMG,  multaG, multaL, multaMG,archCom, archTran, archRep,
            leve,grave,muyGrave,montoL,montoG,montoMG);
         imprimirResumenPersonal( dniMayor, dniMenor, montoMenor, montoMayor, dni, cantL,
      cantG,  cantMG,  multaG,  multaL,  multaMG, archRep);
        i++;
        //while (archCom.get()!='\n');
    }
    imprimirResumenFinal(leve,grave,muyGrave,montoL,montoG,montoMG,archRep);
    imprimirComparaciones(dniMayor, dniMenor, montoMenor, montoMayor,archRep);
}

//79672079 CONTRERAS/CHANG/JOHANA-CINTHIA
void datosCabecera(int i,int dni, ifstream &archCom,ofstream &archRep) {
    imprimirLinea(ANCHO,'=',archRep);
    archRep<<"COMPANIA No. "<<i<<endl;
    archRep<<"REPRESENTANTE LEGAL: ";
    leerNombre(archCom,archRep);
    archRep<<"DNI: "<<dni<<endl;
    imprimirLinea(ANCHO,'-',archRep);
}

void to_upperCase(char &c) {
    if (c>='a' and c<='z') c-=('a'-'A');
}

void  leerNombre(ifstream &archCom,ofstream &archRep) {
    char c;
    int size=0;
    archCom>>ws;
    while (true) {
        archCom.get(c);
        if (c==' ')break;
        if (c=='/' or c=='-') c=' ';
        to_upperCase(c);
        archRep.put(c);
        size++;
    }
    int ancho=HEADER_WIDTH/3;
    for (int i=0;i<ancho-size;i++) archRep<<' ';
}

//P599-629    12/12/2023  2036       M852-620  23/01/2024    2029  P282-128    12/11/2023  2067
void leerDatos(int &cantL,int &cantG,int &cantMG, double &multaG,double &multaL,double &multaMG,
    ifstream &archCom,ifstream &archTran,ofstream &archRep,int &leve,int &grave,int &muyGrave,double &montoL,
    double &montoG, double &montoMG){
    int fechaInfracc,infraccCom,placaNum1,placaNum2,cantTotal=0;
    cantL=0,cantG=0,cantMG=0;
    char gravedad,vehiculo,car;
    double multa,multaTotal=0;
    multaL=0.0,multaMG=0.0,multaG=0.0;
     imprimirSubtitulos( archRep);
    while (true) {
        archCom>>vehiculo>>placaNum1>>car>>placaNum2;
        fechaInfracc=leerValorTemporal('F',archCom,archRep);
        archCom>>infraccCom;
        imprimirColumnas4(vehiculo,placaNum1,placaNum2,fechaInfracc,infraccCom,archRep);
        //imprime la infraccion escrita
        buscarInfraccion(multa,gravedad,infraccCom,archTran,archRep);
        //calcula la suma de datos
        resumenPersonal(cantL,cantG,cantMG,gravedad,multa,archRep,multaG,multaL,multaMG,
            leve,grave,muyGrave,montoL,montoG,montoMG);
        if (archCom.get()=='\n') break;
    }
}


int leerValorTemporal(char tipo,ifstream &arch,ofstream &archRep) {
    int dd_hh, aa_seg, mm_min;
    char c;
    arch>>dd_hh>>c>>mm_min>>c>>aa_seg;
    return compactarValor(tipo,arch,dd_hh,mm_min,aa_seg,archRep);
}

int compactarValor(char tipo, ifstream &arch,int dd_hh,int mm_min,int aa_seg,ofstream &archRep) {
    if (tipo=='F') return aa_seg*10000+mm_min*100+dd_hh;
    else return aa_seg+mm_min*60+dd_hh*3600;
}
void imprimirValorTemporal(int valor, ofstream &archRep,char tipo) {
    int dd_hh, aa_seg, mm_min, n=((tipo=='F')?4:2);
    char c=((tipo=='F')?'/':':');
    decompactarValor(dd_hh, aa_seg, mm_min,tipo,valor);
    archRep<<right<<setfill('0')<<setw(2)<<dd_hh<<c<<setw(2)<<mm_min<<c<<setw(2)<<aa_seg<<setfill(' ');
}
void decompactarValor(int &dd_hh, int &aa_seg, int &mm_min,char tipo,int valor) {
    if (tipo=='F') {
        aa_seg=valor/10000;
        mm_min=(valor%10000)/100;
        dd_hh=valor%100;
    }else {
        dd_hh=valor/3600;
        mm_min=(valor%3600)/60;
        aa_seg=valor%60;
    }
}

//M1001 4791.53     Conducir con presencia de alcohol en la sangre o bajo los efectos de estupefacientes y que haya participado en un accidente de tránsito.
void buscarInfraccion(double &multa,char &gravedad,int infraccCom,ifstream &archTran,ofstream &archRep) {
    int codInfracc;
    archTran.clear();
    archTran.seekg(0,ios::beg);
    while (true) {
        archTran>>gravedad;
        if (archTran.eof()) break;
        archTran>>codInfracc;
        if (infraccCom==codInfracc) {
            archTran>>multa;
            imprimirInfracc(gravedad, multa,archTran,archRep);
            break; //cuando encuentra lo que quiere sale
        }else while (archTran.get()!='\n');
    }
}

void imprimirInfracc(char gravedad, double multa, ifstream &archTran,ofstream &archRep) {
    archTran>>ws;
    char c;
    int size=0;
    imprimirGravedad(gravedad,archRep);
    archRep<<setw(10)<<" "<<multa<<setw(8)<<" ";
    while (true) {
        archTran.get(c);
        if (c=='\n')break;
        archRep.put(c);
        size++;
    }
    int ancho=HEADER_WIDTH/3;
    for (int i=0;i<ancho-size;i++) archRep<<' ';
    archRep<<endl;
}


void imprimirColumnas4(char vehiculo,int placaNum1,int placaNum2,int fechaInfracc,int infraccCom,ofstream &archRep) {
    archRep<<"-  "<<placaNum1<<placaNum2<<right<<setw(10)<<" ";
    imprimirVehiculo(vehiculo,archRep);
    imprimirValorTemporal(fechaInfracc,archRep,'F');
    archRep<<right<<setw(10)<<" "<<infraccCom<<right<<setw(10)<<" ";
}

void imprimirVehiculo(char vehiculo,ofstream &archRep) {
    if (vehiculo=='P') archRep<<"PEQUENO"<<setw(10)<<" ";
    else if (vehiculo=='M') archRep<<"MEDIANO"<<setw(10)<<" ";
    else archRep<<"GRANDE "<<setw(10)<<" ";
}

void imprimirGravedad(char gravedad,ofstream &archRep) {
    if (gravedad=='L') archRep<<"LEVE     "<<setw(2)<<" ";
    else if (gravedad=='G') archRep<<"GRAVE    "<<setw(2)<<" ";
    else archRep<<"MUY GRAVE"<<setw(2)<<" ";
}

void resumenPersonal(int &cantL,int &cantG,int &cantMG,char gravedad,double multa,ofstream &archRep,double &multaG,
    double &multaL,double &multaMG, int &leve,int &grave,int &muyGrave,double &montoL,double &montoG, double &montoMG) {
     if (gravedad=='L') {
         cantL++;
         leve++;
         multaL+=multa;
         montoL+=multa;
     }
     else if (gravedad=='G') {
         cantG++;
         grave++;
         multaG+=multa;
         montoG+=multa;
     }
     else {
         cantMG++;
         muyGrave++;
         multaMG+=multa;
         montoMG+=multa;
     }
}

void imprimirResumenPersonal(int &dniMayor,int &dniMenor,double &montoMenor,double &montoMayor,int dni,int cantL,int  cantG,
    int  cantMG,double  multaG,double  multaL,double  multaMG,ofstream &archRep) {
    int cantTotal;
    double montoTotal;
    imprimirLinea(ANCHO,'-',archRep);
    archRep<<setw(20)<<" "<<"CANTIDAD     MONTO PAGADO"<<endl;
    archRep<<"FALTAS LEVES:         "<<cantL<<setw(10)<<" "<<multaL<<endl;
    archRep<<"FALTAS GRAVES:        "<<cantG<<setw(10)<<" "<<multaG<<endl;
    archRep<<"FALTAS MUY GRAVES:    "<<cantMG<<setw(10)<<" "<<multaMG<<endl;
    cantTotal=cantL+cantG+cantMG;
    montoTotal=multaL+multaG+multaMG;
    if (montoMayor<montoTotal) {
        montoMayor=montoTotal;
        dniMayor=dni;
    }
    if (montoMenor>montoTotal) {
        montoMenor=montoTotal;
        dniMenor=dni;
    }
    imprimirLinea(ANCHO,'-',archRep);
    archRep<<"TOTAL: "<<setw(15)<<" "<<cantTotal<<"          "<<montoTotal<<endl;
}

void imprimirResumenFinal(int leve,int grave,int muyGrave,double montoL,double montoG,double montoMG,ofstream &archRep) {
    int cantTotal;
    double montoTotal;
    imprimirLinea(ANCHO,'=',archRep);
    archRep<<"TOTAL RECAUDADO POR INFRACCIONES"<<endl;
    archRep<<setw(28)<<" "<<"CANTIDAD     MONTO PAGADO"<<endl;
    archRep<<"TOTAL DE FALTAS LEVES:         "<<leve<<setw(11)<<" "<<montoL<<endl;
    archRep<<"TOTAL DE FALTAS GRAVES:        "<<grave<<setw(10)<<" "<<montoG<<endl;
    archRep<<"TOTAL DE FALTAS MUY GRAVES:    "<<muyGrave<<setw(10)<<" "<<montoMG<<endl;
    cantTotal=leve+grave+muyGrave;
    montoTotal=montoL+montoG+cantTotal;
    archRep<<"PAGO TOTAL: "<<setw(19)<<" "<<cantTotal<<"         "<<montoTotal<<endl;
    imprimirLinea(ANCHO,'=',archRep);
}

void  imprimirComparaciones(int dniMayor, int dniMenor,double  montoMenor,double montoMayor,ofstream &archRep) {
    imprimirLinea(43,'/',archRep);
    archRep<<"//COMPANIA CON MAYOR PAGO POR INFRACCIONES: "<<endl;
    archRep<<"//DNI: "<<setw(10)<<" "<<dniMayor<<endl;
    archRep<<"//TOTAL PAGADO: "<<setw(1)<<" "<<montoMayor<<endl;
    archRep<<"//COMPANIA CON MENOR PAGO POR INFRACCIONES: "<<endl;
    archRep<<"//DNI: "<<setw(10)<<" "<<dniMenor<<endl;
    archRep<<"//TOTAL PAGADO: "<<setw(1)<<" "<<montoMenor<<endl;
    imprimirLinea(43,'/',archRep);
}