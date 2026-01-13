#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "structs.h"
#include <ctype.h>

bool id_invalido(char id[20])
{
    char caracteres_prohibidos[100] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,+- ";
    int id_int;

    if (strpbrk(id, caracteres_prohibidos))  return true; 
    
    if (sscanf(id, "%d", &id_int) < 1)  return true; 
    
    return false;
}


bool id_repetido_org_flia(FILE *arch_Org_flia, char id[20])
{
    Org_flia of;
    rewind(arch_Org_flia);
    while(fread(&of, sizeof(Org_flia), 1, arch_Org_flia))
    {
        if (strcmp(of.id_org_flia, id) == 0) return true;
    }
    return false;
}

bool telefono_invalido(char telefono[20])
{
    int longitud = strlen(telefono);

    if (longitud < 7 || longitud > 15) return true;

    for (int i = 0; i < longitud; i++)
    {
        if (!isdigit(telefono[i])) return true; 
    }

    return false; 
}


void carga_org_flia(FILE *arch_Org_flia, Org_flia of)
{
    bool corte = false; int op;
    
        while(corte != true)
        {    
            printf("Ingrese el ID unico de la Organizacion/Familia: "); 
            fgets(of.id_org_flia, 20, stdin); 
            of.id_org_flia[strcspn(of.id_org_flia, "\n")] = 0;

            if(id_invalido(of.id_org_flia) || id_repetido_org_flia(arch_Org_flia, of.id_org_flia))
            {
                printf("ID invalido, Ingrese formato valido o un ID distinto\n"); //system("pause"); system("cls");
                continue;
            }

            printf("\nIngrese el Nombre/Apellido de la Organizacion/Familia: "); 
            scanf("%s",&of.nombre);
            while(getchar() != '\n');

           printf("\nIngrese la Direccion de la Organizacion/Familia: ");
           fgets(of.direccion, sizeof(of.direccion), stdin);
           of.direccion[strcspn(of.direccion, "\n")] = '\0';

            printf("\nIngrese el Telefono de la Organizacion/Familia: "); 
            scanf("%s",&of.telefono);
            while(getchar() != '\n');

            if(telefono_invalido(of.telefono))
            {
                printf("Telefono invalido, Ingrese formato valido\n"); //system("pause"); system("cls");
                continue;
            }

            printf("\nIngrese el Correo de la Organizacion/Familia: "); 
            scanf("%s",&of.correo);
            while(getchar() != '\n');

            fwrite(&of, sizeof(Org_flia), 1, arch_Org_flia);

            printf("\n\nDesea cargar otra Organizacion/Familia? (1-SI / 0-NO): "); scanf("%d", &op);
            while(getchar() != '\n');
            if(op == 0) corte = true;
        
        } 
}

void listar_org_flia(FILE *arch_Org_flia, Org_flia of)
{
    rewind(arch_Org_flia);
    printf("\n\n******************** LISTA DE FAMILIAS/ORGANIZACIONES REGISTRADA *********************\n\n");
    printf("%-5s %-20s %-20s %-15s %-30s\n","ID", "Nombre", "Direccion", "Telefono", "Correo");
    printf("-------------------------------------------------------------------------------\n");

    while (fread(&of, sizeof(Org_flia), 1, arch_Org_flia))
    {
        printf("%-5s %-20s %-20s %-15s %-30s\n",of.id_org_flia,of.nombre,of.direccion, of.telefono,of.correo);
    }

    system("pause");
}

void eliminar_org_flia(FILE *arch_Org_flia, Org_flia of)
{
}