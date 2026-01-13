#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "structs.h"
#include <string.h>
#include <ctype.h>

bool telefono_invalido(char telefono[20]);
bool id_repetido_org_flia(FILE *arch_Org_flia, char id[20]);
bool id_invalido(char id[20]);
void carga_org_flia(FILE *arch_Org_flia, Org_flia of);
void listar_org_flia(FILE *arch_Org_flia, Org_flia of);
void eliminar_org_flia(FILE *arch_Org_flia, Org_flia of);

#endif

