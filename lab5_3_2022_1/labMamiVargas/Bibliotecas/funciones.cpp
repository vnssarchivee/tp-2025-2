//
// Created by Vanessa on 05/10/2025.
//

#include "funciones.h"
void abrirArch(ifstream &arch, const char *nombArch) {
    arch.open(nombArch,ios::in);
    if(!arch.is_open()) {
        cout<<"ERROR: No se pudo abrir "<<nombArch<<endl;
        exit(1);
    }
}
void abrirArchRep(ofstream &arch, const char *nombArch) {
    arch.open(nombArch,ios::out);
    if(!arch.is_open()) {
        cout<<"ERROR: No se pudo abrir "<<nombArch<<endl;
        exit(1);
    }
}
void ignorar(ifstream &arch, char until) {
    char c;
    arch>>ws;
    while (true) {
        c=arch.get();
        if (c==until)break;
    }
}
void cargarClientes(const char *nombArch,int *dniClientes,int *telfClientes,int &cantClientes) {
    int dni;
    char car;
    ifstream clientes;
    abrirArch(clientes,nombArch);
    while (true) {
        clientes>>dni;
        if (clientes.eof())break;
        ignorar(clientes, ']');
        clientes>>telfClientes[cantClientes]>>car;
        dniClientes[cantClientes]=dni;
        cantClientes++;
    }
}
void pruebaCargarClientes(const char *nombArch,int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes) {
    ofstream archRep;
    abrirArchRep(archRep,nombArch);
    for (int i = 0; i < cantClientes; i++) {
        archRep<<dniClientes[i]<<setw(10)<<" "<<setw(12)<<telfClientes[i]<<" "<<setw(10)<<" "<<totalGastadoCliente[i]<<endl;
    }
}

void ordenarDatos(int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes) {
    for (int i = 0; i < cantClientes-1; i++) {
        for (int j = i+1; j < cantClientes; j++) {
            if (dniClientes[i] < dniClientes[j]) {
                intercambiarInt(dniClientes[i],dniClientes[j]);
                intercambiarInt(telfClientes[i],telfClientes[j]);
                intercambiarDouble(totalGastadoCliente[i],totalGastadoCliente[j]);
            }
        }
    }
}

void intercambiarInt(int &datoI,int &datoJ) {
    int aux=datoI;
    datoI=datoJ;
    datoJ=aux;
}

void intercambiarDouble(double &datoI,double &datoJ) {
    int aux=datoI;
    datoI=datoJ;
    datoJ=aux;
}

//397718       *LECHE LALA SEMI DESLACTOSADA 1LT*      1.78    16.98   71378466       26/10/2020
void procesarPedidos(const char *nombArch,int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes,
    int *codProducto,double *cantPedidaProducto,double *precioProducto,double *totalProducto,int &cantProducto) {
    int codigoProducto,dniCli,entero,posProducto,posCliente;
    double cantidad,precio,total,todo;
    char car;
    ifstream pedidos;
    abrirArch(pedidos,nombArch);
    while (true) {
        pedidos>>codigoProducto;
        if (pedidos.eof())break;
        ignorar(pedidos, '*');
        ignorar(pedidos, '*');
        pedidos>>cantidad>>precio>>dniCli>>entero>>car>>entero>>car>>entero;
        posProducto=buscarProducto(codigoProducto,codProducto,cantProducto);
        if (posProducto==NO_ENCONTRADO) {
            codProducto[cantProducto]=codigoProducto;
            precioProducto[cantProducto]=precio;
            posProducto=cantProducto;
            cantProducto++;
        }
        total=cantidad*precio;
        cantPedidaProducto[posProducto]+=cantidad; //igual va sumando lo anterior
        totalProducto[posProducto]+=total;//aca tambien
        posCliente=buscarPosCliente(dniCli,dniClientes,cantClientes);
        if (posCliente!=NO_ENCONTRADO) totalGastadoCliente[posCliente]+=total;
    }

}
int buscarPosCliente(int dniCli,int *dniClientes,int cantClientes) {
    for (int i = 0; i < cantClientes; i++) {
        if (dniClientes[i] == dniCli) return i;
    }
    return NO_ENCONTRADO;
}
int buscarProducto(int codigoProducto,int *codProducto,int cantProducto) {
    for (int i = 0; i < cantProducto; i++) {
        if (codProducto[i] == codigoProducto) return i;
    }
    return NO_ENCONTRADO;
}

void imprimirProductos(ofstream &archRep,int *codProducto,double *cantPedidaProducto,double *precioProducto,double *totalProducto,int cantProducto) {
    double total=0;
    for (int i = 0; i < cantProducto; i++) {
        archRep<<setfill('0')<<setw(2)<<i+1<<")"<<setfill(' ')<<setw(10)<<" "<<codProducto[i]<<setw(10)
        <<" "<<setw(7)<<precioProducto[i]<<" "<<setw(10)<<" "<<setw(10)<<cantPedidaProducto[i]<<" "
        <<setw(17)<<" "<<totalProducto[i]<<endl;
        total+=totalProducto[i];
    }
    imprimirLinea('-', HEADER, archRep);
    archRep<<setw(58)<<" "<<"TOTAL RECAUDADO: "<<total<<endl;
    imprimirLinea('=', HEADER, archRep);
}
void imprimirClientes(ofstream &archRep,int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes) {
    double min=99999,max=0;
    int clienteMin,clienteMax;
    for (int i = 0; i < cantClientes; i++) {
        archRep<<setfill('0')<<setw(2)<<i+1<<")"<<setfill(' ')<<setw(10)<<" "<<dniClientes[i]<<setw(10)<<" "<<
            setw(12)<<telfClientes[i]<<" "<<setw(10)<<" "<<totalGastadoCliente[i]<<endl;
        if (totalGastadoCliente[i]<min) {
            min=totalGastadoCliente[i];
            clienteMin=dniClientes[i];
        }
        if (totalGastadoCliente[i]>max) {
            max=totalGastadoCliente[i];
            clienteMax=dniClientes[i];
        }
    }
    imprimirLinea('-', HEADER, archRep);
    archRep<<"CLIENTE CON MAYOR GASTO: "<<clienteMax<<" - "<<max<<endl;
    archRep<<"CLIENTE CON MENOR GASTO: "<<clienteMin<<" - "<<min<<endl;
}
void imprimirReporte(const char *nombArch,int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes,
    int *codProducto,double *cantPedidaProducto,double *precioProducto,double *totalProducto,int cantProducto) {
    ofstream archRep;
    int clienteMin,clienteMax;
    abrirArchRep(archRep,nombArch);
    archRep<<setprecision(2)<<fixed;
    imprimirTitulo(archRep);
    imprimirProductos(archRep,codProducto,cantPedidaProducto,precioProducto,totalProducto,cantProducto);
    imprimirSubtitulo2(archRep);
    imprimirClientes(archRep,dniClientes,telfClientes,totalGastadoCliente,cantClientes);
}

void imprimirLinea(char car, int cant, ofstream &archRep) {
    for (int i = 0; i < cant; i++) archRep<<car;
    archRep<<endl;
}

void imprimirTitulo(ofstream &archRep) {
    archRep<<setw(HEADER/2+9)<<"EMPRESA COMERCIALIZADORA ABC S.A."<<endl;
    archRep<<setw(HEADER/2)<<"REPORTE DE VENTAS"<<endl;
    imprimirLinea('=', HEADER, archRep);
    archRep<<"INGRESOS POR PRODUCTO"<<endl;
    archRep<<"No. "<<setw(10)<<" "<<"CODIGO"<<setw(10)<<" "<<"PRECIO"<<setw(10)<<" "<<"CANTIDAD VENDIDA"
    <<setw(10)<<" "<<"MONTO RECAUDADO"<<endl;
}
void imprimirSubtitulo2(ofstream &archRep) {
    archRep<<"INGRESOS POR CLIENTE"<<endl;
    archRep<<"No. "<<setw(10)<<" "<<"DNI"<<setw(15)<<" "<<"TELEFONO"<<setw(10)<<" "<<"TOTAL GASTADO"<<endl;
}

void ordenarProductos(int *codProducto,double *cantPedidaProducto,double *precioProducto,double *totalProducto,int cantProducto) {
    for (int i=0;i<cantProducto-1;i++) {
        for (int j=i+1;j<cantProducto;j++) {
            if (codProducto[i]>codProducto[j]) {
                intercambiarInt(codProducto[i],codProducto[j]);
                intercambiarDouble(precioProducto[j],precioProducto[i]);
                intercambiarDouble(cantPedidaProducto[i],cantPedidaProducto[j]);
                intercambiarDouble(totalProducto[j],totalProducto[i]);
            }
        }
    }
}

void ordenarClientes(int *dniClientes,int *telfClientes,double *totalGastadoCliente,int cantClientes) {
    for (int i=0;i<cantClientes-1;i++) {
        for (int j=i+1;j<cantClientes;j++) {
            if (totalGastadoCliente[i]<totalGastadoCliente[j]) {
                intercambiarInt(dniClientes[i],dniClientes[j]);
                intercambiarDouble(totalGastadoCliente[j],totalGastadoCliente[i]);
                intercambiarInt(telfClientes[i],telfClientes[j]);
            }
        }
    }
}