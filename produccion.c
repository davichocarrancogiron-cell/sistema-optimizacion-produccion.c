
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
#define TAM 50

// Prototipos de funciones
int leerEntero(char mensaje[]);
float leerReal(char mensaje[]);
void leerTexto(char texto[], int tam);

int buscarProducto(char nombres[MAX][TAM], int cantidad, char buscado[]);

void registrarProducto(char nombres[MAX][TAM], int demanda[],
                       float tiempo[], float recursos[], int *cantidad);

void mostrarProductos(char nombres[MAX][TAM], int demanda[],
                      float tiempo[], float recursos[], int cantidad);

void editarProducto(char nombres[MAX][TAM], int demanda[],
                    float tiempo[], float recursos[], int cantidad);

void eliminarProducto(char nombres[MAX][TAM], int demanda[],
                      float tiempo[], float recursos[], int *cantidad);

void calcularProduccion(char nombres[MAX][TAM], int demanda[],
                        float tiempo[], float recursos[], int cantidad);


// Funcion principal
int main() {

    char nombres[MAX][TAM];

    int demanda[MAX];
    float tiempo[MAX];
    float recursos[MAX];

    int cantidad = 0;
    int opcion;

    do {

        printf("\n====================================\n");
        printf(" SISTEMA DE OPTIMIZACION DE PRODUCCION\n");
        printf("====================================\n");
        printf("1. Registrar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Calcular produccion y evaluar demanda\n");
        printf("6. Salir\n");
        printf("====================================\n");

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {

            case 1:
                registrarProducto(nombres, demanda, tiempo,
                                  recursos, &cantidad);
                break;

            case 2:
                mostrarProductos(nombres, demanda, tiempo,
                                 recursos, cantidad);
                break;

            case 3:
                editarProducto(nombres, demanda, tiempo,
                               recursos, cantidad);
                break;

            case 4:
                eliminarProducto(nombres, demanda, tiempo,
                                 recursos, &cantidad);
                break;

            case 5:
                calcularProduccion(nombres, demanda, tiempo,
                                   recursos, cantidad);
                break;

            case 6:
                printf("\nSaliendo del sistema...\n");
                break;

            default:
                printf("\nOpcion no valida. Intente nuevamente.\n");
        }

    } while (opcion != 6);

    return 0;
}


// Funcion para leer numeros enteros
int leerEntero(char mensaje[]) {

    char linea[100];
    int valor;

    while (1) {

        printf("%s", mensaje);

        if (fgets(linea, sizeof(linea), stdin) != NULL &&
            sscanf(linea, "%d", &valor) == 1) {

            return valor;
        }

        printf("Error: ingrese un numero entero valido.\n");
    }
}


// Funcion para leer numeros decimales
float leerReal(char mensaje[]) {

    char linea[100];
    float valor;

    while (1) {

        printf("%s", mensaje);

        if (fgets(linea, sizeof(linea), stdin) != NULL &&
            sscanf(linea, "%f", &valor) == 1) {

            return valor;
        }

        printf("Error: ingrese un numero valido.\n");
    }
}


// Funcion para leer nombres de productos
void leerTexto(char texto[], int tam) {

    fgets(texto, tam, stdin);

    texto[strcspn(texto, "\n")] = '\0';
}


// Funcion de busqueda secuencial
int buscarProducto(char nombres[MAX][TAM], int cantidad,
                   char buscado[]) {

    for (int i = 0; i < cantidad; i++) {

        if (strcmp(nombres[i], buscado) == 0) {

            return i;
        }
    }

    return -1;
}


// Funcion para registrar productos
void registrarProducto(char nombres[MAX][TAM], int demanda[],
                       float tiempo[], float recursos[], int *cantidad) {

    char nombre[TAM];
    int posicion;

    if (*cantidad >= MAX) {

        printf("\nNo se pueden registrar mas de 5 productos.\n");
        return;
    }

    printf("\n===== REGISTRO DE PRODUCTO =====\n");

    printf("Ingrese el nombre del producto: ");
    leerTexto(nombre, TAM);

    posicion = buscarProducto(nombres, *cantidad, nombre);

    if (posicion != -1) {

        printf("\nEste producto ya se encuentra registrado.\n");
        return;
    }

    strcpy(nombres[*cantidad], nombre);

    do {

        demanda[*cantidad] = leerEntero(
            "Ingrese la cantidad demandada: ");

        if (demanda[*cantidad] < 0) {
            printf("Error: la cantidad no puede ser negativa.\n");
        }

    } while (demanda[*cantidad] < 0);

    do {

        tiempo[*cantidad] = leerReal(
            "Ingrese el tiempo de fabricacion por unidad: ");

        if (tiempo[*cantidad] <= 0) {
            printf("Error: el tiempo debe ser mayor que cero.\n");
        }

    } while (tiempo[*cantidad] <= 0);

    do {

        recursos[*cantidad] = leerReal(
            "Ingrese los recursos necesarios por unidad: ");

        if (recursos[*cantidad] < 0) {
            printf("Error: los recursos no pueden ser negativos.\n");
        }

    } while (recursos[*cantidad] < 0);

    (*cantidad)++;

    printf("\nProducto registrado correctamente.\n");
}


// Funcion para mostrar los productos
void mostrarProductos(char nombres[MAX][TAM], int demanda[],
                      float tiempo[], float recursos[], int cantidad) {

    if (cantidad == 0) {

        printf("\nNo existen productos registrados.\n");
        return;
    }

    printf("\n===== LISTA DE PRODUCTOS =====\n");

    for (int i = 0; i < cantidad; i++) {

        printf("\nProducto %d\n", i + 1);
        printf("Nombre: %s\n", nombres[i]);
        printf("Cantidad demandada: %d\n", demanda[i]);
        printf("Tiempo por unidad: %.2f\n", tiempo[i]);
        printf("Recursos por unidad: %.2f\n", recursos[i]);
    }
}


// Funcion para editar un producto
void editarProducto(char nombres[MAX][TAM], int demanda[],
                    float tiempo[], float recursos[], int cantidad) {

    char buscado[TAM];
    char nuevoNombre[TAM];

    int posicion;
    int otraPosicion;

    if (cantidad == 0) {

        printf("\nNo existen productos para editar.\n");
        return;
    }

    printf("\n===== EDITAR PRODUCTO =====\n");
    printf("Ingrese el nombre del producto que desea editar: ");
    leerTexto(buscado, TAM);

    posicion = buscarProducto(nombres, cantidad, buscado);

    if (posicion == -1) {

        printf("\nProducto no encontrado.\n");
        return;
    }

    printf("\nIngrese el nuevo nombre: ");
    leerTexto(nuevoNombre, TAM);

    otraPosicion = buscarProducto(nombres, cantidad, nuevoNombre);

    if (otraPosicion != -1 && otraPosicion != posicion) {

        printf("\nYa existe otro producto con ese nombre.\n");
        return;
    }

    strcpy(nombres[posicion], nuevoNombre);

    do {

        demanda[posicion] = leerEntero(
            "Ingrese la nueva cantidad demandada: ");

        if (demanda[posicion] < 0) {
            printf("Error: la cantidad no puede ser negativa.\n");
        }

    } while (demanda[posicion] < 0);

    do {

        tiempo[posicion] = leerReal(
            "Ingrese el nuevo tiempo por unidad: ");

        if (tiempo[posicion] <= 0) {
            printf("Error: el tiempo debe ser mayor que cero.\n");
        }

    } while (tiempo[posicion] <= 0);

    do {

        recursos[posicion] = leerReal(
            "Ingrese los nuevos recursos por unidad: ");

        if (recursos[posicion] < 0) {
            printf("Error: los recursos no pueden ser negativos.\n");
        }

    } while (recursos[posicion] < 0);

    printf("\nProducto actualizado correctamente.\n");
}


// Funcion para eliminar un producto
void eliminarProducto(char nombres[MAX][TAM], int demanda[],
                      float tiempo[], float recursos[], int *cantidad) {

    char buscado[TAM];
    int posicion;

    if (*cantidad == 0) {

        printf("\nNo existen productos para eliminar.\n");
        return;
    }

    printf("\n===== ELIMINAR PRODUCTO =====\n");
    printf("Ingrese el nombre del producto que desea eliminar: ");
    leerTexto(buscado, TAM);

    posicion = buscarProducto(nombres, *cantidad, buscado);

    if (posicion == -1) {

        printf("\nProducto no encontrado.\n");
        return;
    }

    for (int i = posicion; i < *cantidad - 1; i++) {

        strcpy(nombres[i], nombres[i + 1]);

        demanda[i] = demanda[i + 1];
        tiempo[i] = tiempo[i + 1];
        recursos[i] = recursos[i + 1];
    }

    (*cantidad)--;

    printf("\nProducto eliminado correctamente.\n");
}


// Funcion para calcular y evaluar la produccion
void calcularProduccion(char nombres[MAX][TAM], int demanda[],
                        float tiempo[], float recursos[], int cantidad) {

    float tiempoTotal = 0;
    float recursosTotales = 0;

    float tiempoDisponible;
    float recursosDisponibles;

    if (cantidad == 0) {

        printf("\nNo existen productos registrados.\n");
        return;
    }

    printf("\n===== CALCULO DE PRODUCCION =====\n");

    for (int i = 0; i < cantidad; i++) {

        tiempoTotal += demanda[i] * tiempo[i];

        recursosTotales += demanda[i] * recursos[i];
    }

    printf("\n===== RESULTADOS =====\n");

    for (int i = 0; i < cantidad; i++) {

        printf("\nProducto: %s\n", nombres[i]);

        printf("Tiempo requerido: %.2f\n",
               demanda[i] * tiempo[i]);

        printf("Recursos requeridos: %.2f\n",
               demanda[i] * recursos[i]);
    }

    printf("\nTiempo total de fabricacion: %.2f\n", tiempoTotal);

    printf("Recursos totales necesarios: %.2f\n", recursosTotales);

    printf("\n===== CAPACIDAD DE LA FABRICA =====\n");

    do {

        tiempoDisponible = leerReal(
            "Ingrese el tiempo total disponible: ");

        if (tiempoDisponible < 0) {
            printf("Error: el tiempo disponible no puede ser negativo.\n");
        }

    } while (tiempoDisponible < 0);

    do {

        recursosDisponibles = leerReal(
            "Ingrese la cantidad total de recursos disponibles: ");

        if (recursosDisponibles < 0) {
            printf("Error: los recursos disponibles no pueden ser negativos.\n");
        }

    } while (recursosDisponibles < 0);

    printf("\n===== EVALUACION FINAL =====\n");

    if (tiempoTotal <= tiempoDisponible &&
        recursosTotales <= recursosDisponibles) {

        printf("\nLA FABRICA PUEDE CUMPLIR CON LA DEMANDA.\n");

        printf("Tiempo restante: %.2f\n",
               tiempoDisponible - tiempoTotal);

        printf("Recursos restantes: %.2f\n",
               recursosDisponibles - recursosTotales);

    } else {

        printf("\nLA FABRICA NO PUEDE CUMPLIR CON TODA LA DEMANDA.\n");

        if (tiempoTotal > tiempoDisponible) {

            printf("No existe suficiente tiempo de produccion.\n");
        }

        if (recursosTotales > recursosDisponibles) {

            printf("No existen suficientes recursos disponibles.\n");
        }
    }
}
