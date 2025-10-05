#include "Bibliotecas/funciones.h"

int main() {
    //71984468   [IPARRAGUIRRE VILLEGAS NICOLAS EDILBERTO]   935441620 A
    int dniClientes[MAX_CLIENTES]{};
    int telfClientes[MAX_CLIENTES]{};
    double totalGastadoCliente[MAX_CLIENTES]{};
    int cantClientes = 0;
    cargarClientes("ArchivosDeDatos/Clientes (7).txt",dniClientes,telfClientes,cantClientes);
    pruebaCargarClientes("ArchivosDeReporte/pruebaClientes.txt",dniClientes,telfClientes,totalGastadoCliente,cantClientes);
    ordenarDatos(dniClientes,telfClientes,totalGastadoCliente,cantClientes);
    pruebaCargarClientes("ArchivosDeReporte/pruebaClientesOrdenado.txt",dniClientes,telfClientes,totalGastadoCliente,cantClientes);
    //397718       *LECHE LALA SEMI DESLACTOSADA 1LT*      1.78    16.98   71378466       26/10/2020
    int codProducto[MAX_PRODUCTO]{};
    double cantPedidaProducto[MAX_PRODUCTO]{};
    double precioProducto[MAX_PRODUCTO]{};
    double totalProducto[MAX_PRODUCTO]{};
    int cantProducto = 0;
    procesarPedidos("ArchivosDeDatos/Pedidos (1).txt",dniClientes,telfClientes,totalGastadoCliente,cantClientes,
        codProducto,cantPedidaProducto,precioProducto,totalProducto,cantProducto);
    imprimirReporte("ArchivosDeReporte/Reporte.txt",dniClientes,telfClientes,totalGastadoCliente,cantClientes,
       codProducto,cantPedidaProducto,precioProducto,totalProducto,cantProducto);
     ordenarClientes(dniClientes,telfClientes,totalGastadoCliente, cantClientes);
     ordenarProductos(codProducto,cantPedidaProducto,precioProducto,totalProducto,cantProducto);
    imprimirReporte("ArchivosDeReporte/ReporteOrdenado.txt",dniClientes,telfClientes,totalGastadoCliente,cantClientes,
   codProducto,cantPedidaProducto,precioProducto,totalProducto,cantProducto);
    return 0;
}