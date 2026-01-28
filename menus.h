#include "structs.h"
#include <stdio.h>
#ifndef MENUS_H
#define MENUS_H

void menu_principal();
void menu_gestion_org_flia(FILE *arch_org_flia, Org_flia of);
void gestionar_donaciones(FILE *arch_donaciones, Donacion d);

#endif