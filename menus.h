#include "structs.h"
#include <stdio.h>
#ifndef MENUS_H
#define MENUS_H


void menu_principal();
void menu_gestion_org_flia(FILE *arch_org_flia, Org_flia of);
void gestionar_donaciones(FILE *arch_donaciones, Donacion d);
void cargar_usuario(FILE *arch_usuarios, Usuario u);
void login(FILE *arch_usuarios, Usuario u);

#endif
