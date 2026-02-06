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
            printf("Ingrese el ID unico de la Organizacion/Familia: "); gets(of.id_org_flia);

            if(id_invalido(of.id_org_flia) || id_repetido_org_flia(arch_Org_flia, of.id_org_flia))
            {
                printf("ID invalido, ingrese formato valido o un ID distinto\n"); //system("pause"); system("cls");
                continue;
            }

            printf("\nIngrese el Nombre/Apellido de la Organizacion/Familia: "); gets(of.nombre);

            printf("\nIngrese la Direccion de la Organizacion/Familia: "); gets(of.direccion);

            printf("\nIngrese el Telefono de la Organizacion/Familia: "); gets(of.telefono);

            if(telefono_invalido(of.telefono))
            {
                printf("Telefono invalido, ingrese formato valido\n"); //system("pause"); system("cls");
                continue;
            }

            printf("\nIngrese el Correo de la Organizacion/Familia: "); gets(of.correo);
            fwrite(&of, sizeof(Org_flia), 1, arch_Org_flia);

            printf("\n\nDesea cargar otra Organizacion/Familia? (1-SI / 0-NO): "); scanf("%d", &op);
            while(getchar() != '\n'); //se limpia el salto de linea que queda en el buffer por el scanf
            if(op == 0) corte = true;
        } 
}

void listar_org_flia(FILE *arch_Org_flia, Org_flia of)
{
    rewind(arch_Org_flia);
    printf("\n\n******************** LISTA DE FAMILIAS/ORGANIZACIONES REGISTRADA *********************\n\n");
    printf("ID    Nombre               Direccion                 Telefono        Correo\n");
    printf("-----------------------------------------------------------------------------------------------\n");

    while (fread(&of, sizeof(Org_flia), 1, arch_Org_flia))
    {
        printf("%-5s %-20s %-25s %-15s %-30s\n",of.id_org_flia,of.nombre,of.direccion, of.telefono,of.correo);
        printf("-----------------------------------------------------------------------------------------------\n");
    }

    system("pause");
}

void eliminar_org_flia(FILE *arch_Org_flia, Org_flia of)
{
    char id_eliminar[20];
    FILE *arch_temp = fopen("temp.dat", "wb");
    FILE *arch_donaciones = fopen("donaciones.dat", "rb");
    Donacion d;

    fflush(stdin); 
    printf("Ingrese el ID de la Organizacion/Familia a eliminar: "); gets(id_eliminar);

    rewind(arch_donaciones);
    while (fread(&d, sizeof(Donacion), 1, arch_donaciones))
    {
        if (strcmp(d.id_org_flia, id_eliminar) == 0)
        {
            printf("No se puede eliminar la Organizacion/Familia con ID %s porque tiene donaciones registradas, primero elimine las donaciones asociadas.\n", id_eliminar);
            fclose(arch_temp);
            fclose(arch_donaciones);
            remove("temp.dat");
            system("pause");
            return;
        }
    }

    fclose(arch_donaciones);

    rewind(arch_Org_flia);
    bool encontrado = false;
    while (fread(&of, sizeof(Org_flia), 1, arch_Org_flia))
    {
        if (strcmp(of.id_org_flia, id_eliminar) != 0) fwrite(&of, sizeof(Org_flia), 1, arch_temp);
        
        else encontrado = true;
    }

    fclose(arch_Org_flia);
    fclose(arch_temp);

    remove("org_flia.dat");
    rename("temp.dat", "org_flia.dat");

    arch_Org_flia = fopen("org_flia.dat", "rb+"); // aqui se reabre el archivo para futuras operaciones 

    if (encontrado) printf("Organizacion/Familia con ID %s eliminada exitosamente.\n", id_eliminar);

    else printf("No se encontro una Organizacion/Familia con ID %s.\n", id_eliminar);   

    system("pause");
}

void actualizar_org_flia(FILE *arch_Org_flia, Org_flia of)
{
    char id_modificar[20];
    bool encontrado = false;
    fflush(stdin); 
    printf("Ingrese el ID de la Organizacion/Familia a modificar: "); gets(id_modificar);

    arch_Org_flia = fopen("org_flia.dat", "rb+");
    rewind(arch_Org_flia);

    while (fread(&of, sizeof(Org_flia), 1, arch_Org_flia))
    {
        if (strcmp(of.id_org_flia, id_modificar) == 0)
        {
            encontrado = true;

            printf("Ingrese el nuevo Nombre/Apellido de la Organizacion/Familia: "); gets(of.nombre);

            printf("Ingrese la nueva Direccion de la Organizacion/Familia: "); gets(of.direccion);

            printf("Ingrese el nuevo Telefono de la Organizacion/Familia: "); gets(of.telefono);

            printf("Ingrese el nuevo Correo de la Organizacion/Familia: "); gets(of.correo);

            fseek(arch_Org_flia, -sizeof(Org_flia), SEEK_CUR);
            fwrite(&of, sizeof(Org_flia), 1, arch_Org_flia);
            break;
        }
    }

    if (encontrado) printf("Organizacion/Familia con ID %s actualizada con exito.\n", id_modificar);
    else printf("No se encontro una Organizacion/Familia con ID %s.\n", id_modificar);

    system("pause");
    fclose(arch_Org_flia);
}


void donaciones_x_org_flia(FILE *arch_Org_flia, Org_flia of)
{
    FILE *arch_donaciones = fopen("donaciones.dat", "rb"); Donacion d;
    char id_buscar[20];

    fflush(stdin);
    printf("Ingrese el ID de la Organizacion/Familia para listar sus donaciones: "); gets(id_buscar);
    rewind(arch_Org_flia); 
    bool encontrado = false;

    while(fread(&of, sizeof(Org_flia), 1, arch_Org_flia))
    {
        if(strcmp(of.id_org_flia, id_buscar) == 0) 
        {
            printf("\n\nID Organizacion/Familia: %s - Nombre: %s\n\n", of.id_org_flia, of.nombre);
            printf("----------------------------------------------\n\n");
            break;
        }
        
    }
    rewind(arch_donaciones);

    while(fread(&d, sizeof(Donacion), 1, arch_donaciones))
    {
        if (strcmp(d.id_org_flia, id_buscar) == 0)
        {
            printf("ID Donacion: %s - Nombre Donacion: %s - Tipo de donacion: %s - Fecha: %02d/%02d/%04d\n\n", d.id_donacion, d.nombre, d.tipo_donacion,
                   d.fecha_donacion.dia, d.fecha_donacion.mes, d.fecha_donacion.anio);
            encontrado = true;
        }
    }

    system("pause");
}

//-------------------------------------------------------------------------------------------------------------
//Gestion de donaciones

bool id_repetido_donacion(FILE *arch_donacion, char id[20])
{
    Donacion d;
    rewind(arch_donacion);
    while(fread(&d, sizeof(Donacion), 1, arch_donacion))
    {
        if (strcmp(d.id_donacion, id) == 0) return true;
    }
    return false;
}


void carga_donacion(FILE *arch_donaciones, Donacion d)
{
    FILE *arch_Org_flia = fopen("org_flia.dat", "rb");
    
    bool corte = false; int op; 
    
        while(corte != true)
        {    
            printf("Ingrese el ID unico de la Donacion: "); gets(d.id_donacion);

            if(id_invalido(d.id_donacion) || id_repetido_donacion(arch_donaciones, d.id_donacion))
            {
                printf("ID invalido, ingrese formato valido o un ID distinto\n"); //system("pause"); system("cls");
                continue;
            }

            printf("Ingrese el ID de la Organizacion/Familia quien recibe la ayuda (debe de estar registrada): "); gets(d.id_org_flia);

            if(id_invalido(d.id_org_flia) || !id_repetido_org_flia(arch_Org_flia, d.id_org_flia))
            {
                printf("ID invalido, Ingrese formato valido o un ID distinto\n"); //system("pause"); system("cls");
                continue;
            }

            printf("\nIngrese un Nombre para la donacion a registrar: "); gets(d.nombre);

            printf("\nIngrese que Tipo de donacion es: "); gets(d.tipo_donacion);

            printf("Ingrese el dia que se hizo la donacion: "); 
            if(scanf("%d",&d.fecha_donacion.dia) == 0)
            {
                printf("Dia invalido, ingrese formato valido\n");
                continue;
            }

            printf("Ingrese el mes que se hizo la donacion: "); 
            if(scanf("%d",&d.fecha_donacion.mes) == 0)
            {
                printf("Mes invalido, ingrese formato valido\n");
                continue;
            } 

            printf("Ingrese el año que se hizo la donacion: "); 
            if(scanf("%d",&d.fecha_donacion.anio) == 0)
            {
                printf("año invalido, ingrese formato valido\n");
                continue;
            } 
            while(getchar() != '\n');
           

            printf("\nIngrese una descripcion o detalle que considere importante: "); gets(d.descripcion);

            fwrite(&d, sizeof(Donacion), 1, arch_donaciones);

            printf("\n\nDesea cargar otra Donacion? (1-SI / 0-NO): "); scanf("%d", &op);  while(getchar() != '\n');
            if(op == 0) corte = true;
        
        } 
}


void eliminar_donacion(FILE *arch_donaciones, Donacion d)
{
    char id_eliminar[20];
    FILE *arch_temp = fopen("temp_donacion.dat", "wb");
    fflush(stdin);  // limpiar buffer de entrada 
    printf("Ingrese el ID de la Donacion a eliminar: "); gets(id_eliminar);
    
    rewind(arch_donaciones);
    bool encontrado = false;

    while (fread(&d, sizeof(Donacion), 1, arch_donaciones))
    {
        if (strcmp(d.id_donacion, id_eliminar) != 0) fwrite(&d, sizeof(Donacion), 1, arch_temp);
        else encontrado = true;
    }

    fclose(arch_donaciones);
    fclose(arch_temp);

    remove("donaciones.dat");
    rename("temp_donacion.dat", "donaciones.dat");

    arch_donaciones = fopen("donaciones.dat", "rb"); // aqui se reabre el archivo para futuras operaciones
    if (encontrado) printf("Donacion con ID %s eliminada exitosamente\n", id_eliminar);
    else  printf("No se encontro una Donacion con ID %s\n", id_eliminar);

    system("pause");
}


void listar_donaciones(FILE *arch_donaciones, Donacion d)
{
    FILE *arch_Org_flia = fopen("org_flia.dat", "rb");
    Org_flia of;

    rewind(arch_donaciones);
    printf("\n\n==================== LISTA DE DONACIONES REGISTRADAS ====================\n\n");
    printf("ID         Nombre Donacion           Organizacion/Familia           Tipo de donacion          Fecha        Descripcion\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&d, sizeof(Donacion), 1, arch_donaciones))
    {
        rewind(arch_Org_flia);
        while (fread(&of, sizeof(Org_flia), 1, arch_Org_flia))
        {
            if (strcmp(d.id_org_flia, of.id_org_flia) == 0)
            {
                printf("%-10s %-25s %-30s %-20s %02d/%02d/%04d %-50s\n", d.id_donacion, d.nombre, of.nombre, d.tipo_donacion, d.fecha_donacion.dia, 
                       d.fecha_donacion.mes, 
                       d.fecha_donacion.anio, 
                       "      .....");
                printf("-----------------------------------------------------------------------------------------------------------------------------\n");
                break;
            }
        }
    }

    

    printf("\n\n");
    while(getchar() != '\n');

    while(true)
    {
        printf("SI DESEA LEER LA DESCRIPCION DE ALGUNA DONACION INGRESE SU ID, SI NO DESEA LEER NINGUNA INGRESE 0 PARA TERMINAR: "); 
        char id_donacion[20]; gets(id_donacion);

        if (strcmp(id_donacion, "0") != 0)
        {
            rewind(arch_donaciones);
            while (fread(&d, sizeof(Donacion), 1, arch_donaciones))
            {
                if (strcmp(d.id_donacion, id_donacion) == 0)
                {
                    printf("\n------------------------------------------------------\n");
                    printf("ID Donacion: %s\n", d.id_donacion); printf("Nombre Donacion: %s\n", d.nombre);
                    printf("Tipo de donacion: %s\n", d.tipo_donacion);
                    printf("Descripcion de la donacion: %s\n", d.descripcion);
                    printf("------------------------------------------------------\n\n");
                    //system("pause");
                    //system("cls");
                    continue;
                }
            }
        }
        else return;
    }
    system("pause");
    
}



void actualizar_donacion(FILE *arch_donaciones, Donacion d)
{
    char id_modificar[20];
    bool encontrado = false;
    fflush(stdin);
    printf("Ingrese el ID de la Donacion a modificar: "); gets(id_modificar);

    arch_donaciones = fopen("donaciones.dat", "rb+");
    rewind(arch_donaciones);

    while (fread(&d, sizeof(Donacion), 1, arch_donaciones))
    {
        if (strcmp(d.id_donacion, id_modificar) == 0)
        {
            encontrado = true;

            printf("Ingrese un nuevo Nombre para la donacion a registrar: "); gets(d.nombre);

            printf("Ingrese que Tipo de donacion es: "); gets(d.tipo_donacion);

            printf("Ingrese una descripcion o detalle nuevo que considere importante: "); gets(d.descripcion);

            printf("Ingrese el dia que se hizo la donacion: "); 
            if(scanf("%d",&d.fecha_donacion.dia) == 0)
            {
                printf("Dia invalido, ingrese formato valido\n");
                continue;
            } 

            printf("Ingrese el mes que se hizo la donacion: "); 
            if(scanf("%d",&d.fecha_donacion.mes) == 0)
            {
                printf("Mes invalido, ingrese formato valido\n");
                continue;
            } 

            printf("Ingrese el año que se hizo la donacion: "); 
            if(scanf("%d",&d.fecha_donacion.anio) == 0)
            {
                printf("Año invalido, ingrese formato valido\n");
                continue;
            } 

            fseek(arch_donaciones, -sizeof(Donacion), SEEK_CUR);
            fwrite(&d, sizeof(Donacion), 1, arch_donaciones);
            
            break;
        }
    }

    if (encontrado) printf("Donacion con ID %s modificada exitosamente\\n", id_modificar);
    
    else printf("No se encontro una Donacion con ID %s\n\n", id_modificar);

    system("pause");
    fclose(arch_donaciones);
}


bool contraseña_valida(char contraseña[20])
{
    //pautas para una contraseña bien formateada
    bool a = false, b = false, c = false, d = false, e = false;

    bool tiene_mayuscula = false;
    bool tiene_minuscula = false;
    bool tiene_digito = false;
    
    int longitud = strlen(contraseña);

    for(int i = 0; i < longitud; i++)
    {
        if(isupper(contraseña[i])) tiene_mayuscula = true;
        if(islower(contraseña[i])) tiene_minuscula = true;
        if(isdigit(contraseña[i])) tiene_digito = true;
    }
    
    if(tiene_mayuscula && tiene_minuscula && tiene_digito) a = true;
    
    char caracteres_prohibidos[20] = ".,+- ";
    if (!strpbrk(contraseña, caracteres_prohibidos))  b=true; 

    if (longitud >= 6 && longitud <= 32) c=true;

    int digitos = 0;
    
    for(int i = 0; i < longitud; i++)
    {
        if(isdigit(contraseña[i])) digitos++;
    }

    if(digitos <= 3) d = true;       
    
    e = true;
    for(int i = 0; i < longitud - 1; i++)
    {
        char actual = contraseña[i];
        char siguiente = contraseña[i + 1];
        
        if(isalpha(actual) && isalpha(siguiente))
        {
            char actual_lower = tolower(actual);
            char siguiente_lower = tolower(siguiente);
            
            if(actual_lower + 1 == siguiente_lower )
            {
                e = false;
                break;
            }
        }
    }

    if(a && b && c && d && e) return true;
    else return false;
}

bool usuario_valido(char usuario[15], FILE *arch_usuarios, Usuario u)
{
     //= fopen("usuarios.dat", "ab+"); Usuario u;
    bool a=false ,b = false, c = false, d = false; //consignas
    int longitud = strlen(usuario);

    if(longitud >= 6 && longitud <= 10) a = true;

    if(islower(usuario[0])) b = true;
    
    int mayusculas=0, digitos=0; 
    for(int i=0; i<longitud; i++)
    {
        if(isupper(usuario[i])) mayusculas++;
        if(isdigit(usuario[i])) digitos++;
    }

    if(mayusculas >= 2) c = true;
    if(digitos <= 3) d = true;
    
    rewind(arch_usuarios);
    while(fread(&u, sizeof(Usuario), 1, arch_usuarios))
    {
        if(strcmp(u.nombre_usuario, usuario) == 0)
        {
            fclose(arch_usuarios);
            printf("El nombre de usuario ya existe, ingrese uno diferente.\n"); system("pause");
            return false;
        }
    }
    
    if(a && b && c && d) return true;
    else
    {
        printf("Usuario invalido. \n"); system("pause");
        return false;
    } 
}

void cargar_usuario(FILE *arch_usuarios, Usuario u)
{
    fflush(stdin);
    int op;
    while(op != 0)
    {
        printf("Ingrese un nombre de usuario: "); gets(u.nombre_usuario);
        if(!usuario_valido(u.nombre_usuario, arch_usuarios, u))
        {
            printf("Nombre de usuario invalido"); system("cls");
            continue;  
        } 
        fflush(stdin);

        printf("Ingrese una contrasena: "); gets(u.contrasena);
        if(!contraseña_valida(u.contrasena))
        {
            system("pause");
            continue;
        }

        fwrite(&u, sizeof(Usuario), 1, arch_usuarios);
        fflush(stdin);
        printf("Desea ingresar otro usuario (1-SI / 0-NO): "); scanf("%d", &op); while(getchar() != '\n');
        
        if(op == 0) break;
        fflush(stdin);
    }
    
}

//--------------------------------------------------------------------------------------------
//Gestion de usuarios