#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "structs.h"
#include <ctype.h>

void carga_org_flia(FILE arch_Org_flia, Org_flia of)
{
    bool corte = false; int op;
    while(corte != true)
    {
        
        printf("Ingrese el ID unico de la Organizacion/Familia: "); 
        scanf("%d", &of.id_org_flia); 
        printf("\nIngrese el Nombre de la Organizacion/Familia: "); 
        scanf("%s",&of.nombre);
        printf("\nIngrese la Direccion de la Organizacion/Familia: "); 
        scanf("%s",&of.direccion);
        printf("\nIngrese el Telefono de la Organizacion/Familia: "); 
        scanf("%s",&of.telefono);
        printf("\nIngrese el Correo de la Organizacion/Familia: "); 
        scanf("%s",&of.correo);

        fwrite(&of, sizeof(Org_flia), 1, arch_Org_flia);

        printf("\n\nDesea cargar otra Organizacion/Familia? (1-SI / 0-NO): "); scanf("%d", &op);
        if(op == 0) corte = true;
        
    }
    
}

bool validar_id(int id)
{ 
    char caracteres_prohibidos[100] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,+- ";
    char id_str[20];  sprintf(id_str, "%d", id);
    
    if(strpbrk(id_str, caracteres_prohibidos) || id < 1 ) return false;
    else return true;
}

