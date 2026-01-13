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
    
    system("cls");
    menu_principal();
    
    int op, op1, op2; printf("Opcion: "); scanf("%d", &op);
    while(getchar() != '\n'); // <- Limpia el buffer después de leer la opción principal
    bool b=false; 

    while(b != true)
    {
        switch(op)
        {
            case 1:
                b=true;
                system("cls");
                menu_gestion_org_flia();
                printf("Opcion: "); scanf("%d", &op1); while(getchar() != '\n');

                switch (op1)
                {
                    case 1:
                        system("cls");
                        carga_org_flia(arch_org_flia, of);
                    break;

                    case 2:
                        system("cls");
                        eliminar_org_flia(arch_org_flia, of);
                    break;

                    
                    case 4:
                        system("cls");
                        listar_org_flia(arch_org_flia, of);
                    break;
                    default:
                    break;
                }
            break;

            case 2:
                //gestionar_donaciones(donaciones, org_flia, donacionxorg_flia);
                b=true;
                break;

            default:
                printf("Opcion invalida. Ingrese una opcion valida.\n"); system("pause"); system("cls");
                menu_principal();
                printf("Opcion: "); scanf("%d", &op);
        }
    }



    return 0;
}
