//
// Created by Vanessa on 27/09/2025.
//

#include "funciones.h"
void abrirArch(ifstream &arch,const char *nombArch) {
    arch.open(nombArch,ios::in);
    if (!arch.is_open()) {
        cout << "Error opening file " << nombArch << endl;
        exit(1);
    }
}
void abrirArchRep(ofstream &archRep,const char *nombArch) {
    archRep.open(nombArch,ios::out);
    if (!archRep.is_open()) {
        cout << "Error opening file " << nombArch << endl;
        exit(1);
    }
}

//12/03/2019   A1023   BTS    4.85 55001->90311->92110
void cargarArtistas(const char *nombArch,int *fecha_debut,char *carCod,int *numCod,double *rating,int &cantArtistas) {
    ifstream artistas;
    abrirArch(artistas,nombArch);
    int debut;
    while (true) {
        debut=leerFecha(artistas);
        if (debut==0) break;
        else {
            artistas>>carCod[cantArtistas]>>numCod[cantArtistas];
            ignorar(artistas,' ');
            artistas>>rating[cantArtistas];
            ignorar(artistas,'\n');
            fecha_debut[cantArtistas]=debut;
            cantArtistas++;
        }
    }
}

void ignorar(ifstream &arch,char until) {
    char c;
    arch>>ws;
    while (true) {
        c=arch.get();
        if (c==until) break;
    }
}


int leerFecha(ifstream &arch) {
    int dd,mm,aa;
    char c;
    arch>>dd;
    if (arch.eof()) return 0;
    arch>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

void probarCargaArtistas(const char *nombArchRep,int *fecha_debut,char *carCod,int *numCod,double *rating,int cantArtistas) {
    ofstream archRepPrueba;
    abrirArchRep(archRepPrueba,nombArchRep);
    archRepPrueba<<fixed<<setprecision(2);
    archRepPrueba<<"No. "<<setw(9)<<" "<<"FECHA DEBUT"<<setw(8)<<" "<<"CODIGO"<<setw(9)<<" "<<"RATING"<<endl;
    for (int i=0;i<cantArtistas;i++) {
        archRepPrueba<<setfill('0')<<setw(2)<<i+1<<setfill(' ')<<")"<<setw(9)<<" ";
        imprimirFecha(fecha_debut[i], archRepPrueba);
        archRepPrueba<<setw(10)<<" "<<carCod[i]<<numCod[i]<<setw(10)<<" "<<rating[i]<<endl;
    }
    archRepPrueba.close();
}

void imprimirFecha(int valor, ofstream &archRep) {
    int aa=valor/10000, mm=(valor%10000)/100, dd=valor%100;
    archRep<<right<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

//55001   Dynamite          3:45
void cargarCanciones(const char *nombArch,int *codCancion,int *duracion,int &cantCanciones) {
    ifstream canciones;
    abrirArch(canciones,nombArch);
    int cod,duracionCancion;
    char car;
    while (true) {
        canciones>>cod;
        if (canciones.eof())break;
        ignorar(canciones,' ');
        duracion[cantCanciones]=leerDuracion(canciones);
        codCancion[cantCanciones]=cod;
        cantCanciones++;
    }

}
int leerDuracionReturn(ifstream &arch) {
    int min,seg;
    char car;
    arch>>min;
    if (arch.eof()) return 0;
    arch>>car>>seg;
    return min*60+seg;
}

int leerDuracion(ifstream &arch) {
    int min,seg;
    char car;
    arch>>min>>car>>seg;
    return min*60+seg;
}

void pruebaCargaCanciones(const char *nombArch,int *codCancion,int *duracion,int cantCanciones){
    ofstream archRepPrueba;
    abrirArchRep(archRepPrueba,nombArch);
    archRepPrueba<<fixed<<setprecision(2);
    archRepPrueba<<"No. "<<setw(9)<<" "<<"CODIGO"<<setw(8)<<" "<<"DURACION"<<endl;
    for (int i=0;i<cantCanciones;i++) {
        archRepPrueba<<setfill('0')<<setw(2)<<i+1<<setfill(' ')<<")"<<setw(9)<<" "<<codCancion[i];
        archRepPrueba<<setw(10)<<" ";
        imprimirTiempo(duracion[i],archRepPrueba);
        archRepPrueba<<endl;
    }
    archRepPrueba.close();
}

void  imprimirTiempo(int duracion,ofstream &archRepPrueba){
    int hora=duracion/3600,min=(duracion%3600)/60, seg=duracion%60;
    archRepPrueba<<right<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ');
}


//02/01/2024   A1023   55001   1450000
void cargarReproducciones(const char *nombArch,int *fechaCancion,char *carCod,int *numCod,int *codCancion,int *duracion,int *numRepro,int *totalRep,
    int *tiempoTotalRep,double precioMil,double *revenue,int cantArtistas,int cantCanciones, int &cantRep,int *numReplayTotal) {
    ifstream repro;
    abrirArch(repro,nombArch);
    int fechaR,num,cancion,reproducciones,posArtista,posCancion;
    char letra;
    while (true) {
        fechaR=leerFecha(repro);
        if (fechaR==0) break;
        else {
            repro>>letra>>num>>cancion>>reproducciones;
            posArtista=buscarArtista(letra,num,carCod,numCod,cantArtistas);
            posCancion=buscarCancion(cancion,codCancion,cantCanciones);
            if (posArtista!=-1) {
                numRepro[posArtista]+=reproducciones;
                revenue[posArtista]+=reproducciones*precioMil;
            }else cout<<"No se pudo encontrar el codigo del artista"<<endl;
            if (posCancion!=-1) {
                totalRep[posCancion]=reproducciones;
                fechaCancion[posCancion]=fechaR;
                tiempoTotalRep[posCancion]+=reproducciones*duracion[posCancion];
            }else cout<<"No se pudo encontrar el codigo de la cancion"<<endl;
        }
        cantRep++;
    }
}
int buscarArtista(char letra,int num,char *carCod,int *numCod,int cantArtistas) {
    for (int i=0;i<cantArtistas;i++) {
        if (carCod[i]==letra and numCod[i]==num) return i;
    }
    return -1;
}
int buscarCancion(int cancion,int *codCancion,int cantCanciones) {
    for (int i=0;i<cantCanciones;i++) {
        if (codCancion[i]==cancion) return i;
    }
    return -1;
}

void pruebaCargarReproducciones(const char *nombArch,int *fechaCancion,char *carCod,int *numCod,int *codCancion,
    int *duracion,int *numRepro,int *totalRep,int *tiempoTotalRep,double precioMil,double *revenue,int cantArtistas,
    int cantCanciones,double *rating, int cantRep,int *numReplayTotal){
    ofstream archRepPrueba;
    abrirArchRep(archRepPrueba,nombArch);
    archRepPrueba<<fixed<<setprecision(2);
    imprimirTitulo(archRepPrueba,precioMil);
    archRepPrueba<<"ARTISTAS: "<<endl;
    imprimirLinea(90, '-',archRepPrueba);
    archRepPrueba<<"No. "<<setw(10)<<" "<<"CODE"<<setw(9)<<" "<<"RATING"<<setw(10)<<" "<<"REPLAYS"<<setw(10)<<" "<<"REVENUE"<<endl;
    for (int i=0;i<cantArtistas;i++) {
        archRepPrueba<<right<<setfill('0')<<setw(2)<<i+1<<setfill(' ')<<")"<<setw(10)<<" "<<carCod[i]<<numCod[i]<<setw(10)<<" "<<rating[i]<<setw(9)<<" "<<numRepro[i]
        <<setw(10)<<" "<<revenue[i]<<endl;
    }
    imprimirLinea(90, '-',archRepPrueba);
    archRepPrueba<<"CANCIONES: "<<endl;
    archRepPrueba<<"No. "<<setw(11)<<" "<<"DATE"<<setw(11)<<" "<<"CODE"<<setw(17)<<"DURATION"<<setw(6)
       <<" "<<"N PLAYS"<<setw(10)<<" "<<"TOTAL"<<endl;
        for (int i=0;i<cantRep;i++) {
            archRepPrueba<<right<<setfill('0')<<setw(2)<<i+1<<setfill(' ')<<")"<<setw(9)<<" ";
            imprimirFecha(fechaCancion[i],archRepPrueba);
            archRepPrueba<<setw(8)<<" "<<codCancion[i]<<setw(8)<<" ";
            imprimirTiempo(duracion[i],archRepPrueba);
            archRepPrueba<<setw(7)<<" "<<left<<setw(8)<<totalRep[i]<<" "<<setw(7)<<" ";
            print_time(archRepPrueba, tiempoTotalRep[i], false);
            archRepPrueba<<endl;
        }
    imprimirLinea(90, '=',archRepPrueba);
    archRepPrueba.close();
}

void imprimirLinea(int cant, char car,ofstream &archRep) {
    for (int i=0;i<cant;i++) archRep<<car;
    archRep<<endl;
}


void print_time(ofstream &output, int s, bool in_days) {
    if (in_days) {
        output << setfill('0') << setw(4) << s / 86400 << ':';
        s = s % 86400;
    }
    output << setfill('0') << setw(2) << s / 3600 << ':'
           << setw(2) << (s / 60) % 60 << ':'
           << setw(2) << s % 60;
    output << setfill(' ');
}


void imprimirTitulo(ofstream &arch,double precioMil) {
    arch<<setw(60)<<"KPOP_MUSIC_PLATFORM"<<endl;
    arch<<setw(60)<<"REPLAY FEE PER MINUTE : "<<precioMil<<endl;
    imprimirLinea(90, '=',arch);
}