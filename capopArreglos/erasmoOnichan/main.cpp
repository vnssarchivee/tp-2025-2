#include "bibliotecas/funciones.h"

int main() {
    //double precioMil;
    //artistas  12/03/2019   A1023   BTS    4.85 55001->90311->92110
   // cout<<"ENTER FEE PER MINUTE: "<<endl;
    //cin>>precioMil;
    int fecha_debut[MAX_ARTISTAS]{};
    char carCod[MAX_ARTISTAS]{};
    int numRepro[MAX_ARTISTAS]{};
    int numReplayTotal[MAX_ARTISTAS]{};
    int numCod[MAX_ARTISTAS]{};
    double rating[MAX_ARTISTAS]{};
    int cantArtistas=0;
    cargarArtistas("ArchivosDeDatos/Artistas.txt",fecha_debut,carCod,numCod,rating,cantArtistas);
    probarCargaArtistas("ArchivosDeReporte/ArtistasPrueba.txt",fecha_debut,carCod,numCod,rating,cantArtistas);

    //canciones 55001   Dynamite          3:45
    int codCancion[MAX_CANCIONES]{};
    int duracion[MAX_CANCIONES]{};
    int cantCanciones=0;

    cargarCanciones("ArchivosDeDatos/Canciones.txt",codCancion,duracion,cantCanciones);
    pruebaCargaCanciones("ArchivosDeReporte/CancionesPrueba.txt",codCancion,duracion,cantCanciones);
    //reproducciones 02/01/2024   A1023   55001   1450000
    int totalRep[MAX_CANCIONES]{};
    int fechaCancion[MAX_CANCIONES]{};
    int tiempoTotalRep[MAX_REPRODUCCIONES]{},cantRep=0;
    double revenue[MAX_REPRODUCCIONES]{};
    double precioMil=0.85;

    cargarReproducciones("ArchivosDeDatos/Reproducciones.txt", fechaCancion, carCod,numCod,codCancion,duracion, numRepro, totalRep,
     tiempoTotalRep, precioMil, revenue, cantArtistas, cantCanciones,cantRep,numReplayTotal);
    pruebaCargarReproducciones("ArchivosDeReporte/Reporte.txt", fechaCancion, carCod,numCod, codCancion, duracion, numRepro, totalRep,
      tiempoTotalRep, precioMil, revenue, cantArtistas, cantCanciones, rating,  cantRep,numReplayTotal);

    return 0;
}