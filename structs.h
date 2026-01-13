#ifndef STRUCTS_H
#define STRUCTS_H


struct fecha {
	int dia;
	int mes;
	int anio;
};

struct Org_flia {
	char id_org_flia[20];
	char nombre[50];
	char direccion[100];
	char telefono[20];
	char correo[40];
};

struct Donacion {
	int id_donacion;
	char nombre[100];
	char tipo_donacion[20];
	fecha fecha_donacion;
	char descripcion[350];
};

#endif
