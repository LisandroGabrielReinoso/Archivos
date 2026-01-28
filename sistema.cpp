#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "funciones.h"
#include "menus.h"
#include "structs.h"


int main() {

    FILE *arch_org_flia = fopen("org_flia.dat", "ab+");
    FILE *arch_donaciones = fopen("donaciones.dat", "ab+");
    FILE *arch_donacionxorg_flia = fopen("donacionxorg_flia.dat", "ab+");
    
    if (arch_org_flia == NULL || arch_donaciones == NULL || arch_donacionxorg_flia == NULL) printf("Error al abrir los archivos.\n");

    Org_flia of; Donacion d; fecha f;
    
    int op;
    bool salir = false;

    while (salir != true) {

        system("cls");
        menu_principal();
        printf("Opcion: "); scanf("%d", &op);

        switch(op) 
        {
            case 1:
                system("cls");
                menu_gestion_org_flia(arch_org_flia, of);
                break;

            case 2:
                system("cls");
                gestionar_donaciones(arch_donaciones, d);
                break;

            case 3:
                salir = true;
                break;

            default:
                printf("Opcion invalida. Ingrese una opcion valida.\n");
                system("pause");
                break;
        }
    }



    return 0;
}
