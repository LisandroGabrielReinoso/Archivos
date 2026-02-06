#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "structs.h"

void login(FILE *arch_usuarios, Usuario u){

    while(true){
        printf("\n\n********** INICIO DE SESION **********\n\n");
        printf("Ingrese su nombre de usuario: "); char usuario[20]; gets(usuario);
        printf("Ingrese su contrasena: "); char contraseña[20]; gets(contraseña);

        rewind(arch_usuarios);
        while(fread(&u, sizeof(Usuario), 1, arch_usuarios))
        {
            if(strcmp(u.nombre_usuario, usuario) == 0 && strcmp(u.contrasena, contraseña) == 0)
            {
                printf("Bienvenido %s\n", u.nombre_usuario);
                system("pause");
                system("cls");
                return;
            }
        }
        printf("Usuario o contrasena incorrectos\n"); system("pause"); system("cls");

    }
    

}


void menu_principal() {
    printf("\n\n\n************************** MENU PRINCIPAL **************************\n");
    printf("\nSeleccione el numero de una de las opciones para continuar\n\n");
    printf("1 - Gestion de Familias/Organizaciones\n");
    printf("2 - Gestion de Donaciones/Ayudas\n");
    printf("3 - Agregar nuevo usuario\n");
    printf("4 - Salir del sistema\n\n");

}

void menu_gestion_org_flia(FILE *arch_org_flia, Org_flia of) {
    int op1;
    while (true) {
        printf("\n\n\n******************** GESTION DE FAMILIAS/ORGANIZACIONES ********************\n");
        printf("\nSeleccione el numero de una de las opciones para continuar\n\n");
        printf("1 - Agregar Nueva Familia/Organizacion\n");
        printf("2 - Modificar Datos de Familia/Organizacion\n");
        printf("3 - Eliminar Familia/Organizacion\n");
        printf("4 - Listar Familias/Organizaciones\n");
        printf("5 - Listar Donaciones de una Familias/Organizaciones\n");
        printf("6 - Volver al Menu Principal\n\n");

        printf("Opcion: "); scanf("%d", &op1);

        switch (op1) {

            case 1:
                system("cls");
                carga_org_flia(arch_org_flia, of);
                system("cls");
                break;

            case 2:
                system("cls");
                actualizar_org_flia(arch_org_flia, of);
                system("cls");
                break;
                
            case 3:
                system("cls");
                eliminar_org_flia(arch_org_flia, of);
                system("cls");

            case 4:
                system("cls");
                listar_org_flia(arch_org_flia, of);
                system("cls");
                break;

            case 5:
                system("cls");
                donaciones_x_org_flia(arch_org_flia, of);
                system("cls");

            case 6:
                system("cls");
                return;

            default:
                printf("Opcion invalida, intente de nuevo.\n");
                system("pause");
                system("cls");
                break;
        }
    }
} 

void gestionar_donaciones(FILE *arch_donaciones, Donacion d)
{
    int op1;
    while (true) {
        printf("\n\n\n******************** GESTION DE DONACIONES/AYUDAS ********************\n");
        printf("\nSeleccione el numero de una de las opciones para continuar\n\n");
        printf("1 - Agregar Nueva Donacion/Ayuda\n");
        printf("2 - Actualizar Donacion/Ayuda\n");
        printf("3 - Eliminar Donacion\n");
        printf("4 - Listar Donaciones/Ayudas\n");
        printf("5 - Volver al Menu Principal\n\n");

        printf("Opcion: "); scanf("%d", &op1);

        switch (op1) {

            case 1:
                system("cls");
                carga_donacion(arch_donaciones, d);
                system("cls");
                break;

            case 2:
                system("cls");
                actualizar_donacion(arch_donaciones, d);
                system("cls");
                break;

            case 3:
                system("cls");
                eliminar_donacion(arch_donaciones, d);
                system("cls");
                break;

            case 4:
                system("cls");
                listar_donaciones(arch_donaciones, d);
                system("cls");
                break;
            
            case 5:
                return;
                system("cls");
                break;
                
            default:
                printf("Opcion invalida, intente de nuevo.\n");
                system("pause");
                system("cls");
                break;
        }
    }
}
