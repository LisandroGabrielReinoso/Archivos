#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "structs.h"
#include <string.h>
#include <ctype.h>

void carga_org_flia(FILE *arch_Org_flia, Org_flia of);
void listar_org_flia(FILE *arch_Org_flia, Org_flia of);
void eliminar_org_flia(FILE *arch_Org_flia, Org_flia of);
void actualizar_org_flia(FILE *arch_Org_flia, Org_flia of);
void donaciones_x_org_flia(FILE *arch_Org_flia, Org_flia of);

void carga_donacion(FILE *arch_donaciones, Donacion d); 
void listar_donaciones(FILE *arch_donaciones, Donacion d);
void eliminar_donacion(FILE *arch_donaciones, Donacion d);
void actualizar_donacion(FILE *arch_donaciones, Donacion d);
void cargar_usuario(FILE *arch_usuarios, Usuario u);


#endif

