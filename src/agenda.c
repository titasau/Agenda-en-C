#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definición de la estructura persona
typedef struct _Persona
{
	struct  _Persona *siguiente;
	struct  _Persona *anterior;
	char	nombre[25];
	char 	apellidoP[25];
	char 	apellidoM[25];
	char    fecha_n[15];
	char    direccion[50];
	char 	telefono[25];
} Persona;

//inicialización para los punteros de la lista
Persona *primera_persona = NULL;
Persona *ultima_persona = NULL;

//enumeración para los estados de salida del programa
enum {
	EXIT_NO,
	EXIT_OK
};

//enumeración para los estados de regreso de las funciones
enum {
	FALSE,
	TRUE
};

//función para agregar una persona a la agenda
int alta()
{
	Persona *nuevaPersona;
	char temp_nombre[25];
	char temp_apellidoP[25];
	//reservo espacio de memoria con malloc
	nuevaPersona = (Persona *) malloc (sizeof (Persona));
	printf("\n------Agregando persona-----");

	printf("\nIngrese nombre:");
    	scanf( "%s", &nuevaPersona->nombre);
	printf("\nIngrese apellido paterno:");
		scanf( "%s", &nuevaPersona->apellidoP); 
	printf("\nIngrese apellido materno:");
		scanf( "%s", &nuevaPersona->apellidoM ); 
	printf("\nIngrese fecha de nacimiento (dd/mm/aa):");
		scanf( "%s", &nuevaPersona->fecha_n ); 
	printf("\nIngrese teléfono (00-11-22-33):");
		scanf( "%s", &nuevaPersona->telefono ); 
	printf("\nIngrese dirección:");
		scanf( "%s", &nuevaPersona->direccion ); 

    // limpio buffer de saltos de linea
    while(getchar() != '\n');

	if(ultima_persona == NULL){
			primera_persona = ultima_persona = nuevaPersona;
		} else {
			ultima_persona->siguiente = nuevaPersona;
			nuevaPersona->anterior = ultima_persona;
			ultima_persona = nuevaPersona;
		}

	return TRUE;
}

//función para borrar una persona de la agenda
int baja()
{
	Persona *tempPersona = primera_persona;
	char palabara_clave[25];
    printf("\n----Borrando persona de agenda----");
    printf("\n Dame el apellido paterno de la persona a borrar de la agenda:");
    scanf("%s",&palabara_clave);

    //do para recorrer la agenda
    do
    {
    	//si la palabra clave a buscar coincide con el apellido paterno de la persona
    	if(strcmp(palabara_clave,tempPersona->apellidoP) == 0)
    	{
    	//si la persona a borrar es la primera de la lista
    		if (tempPersona == primera_persona)
    		{	
    			//si la primera persona no tiene ninguna en siguiente
    			if(tempPersona->siguiente == NULL)
    			{
    				primera_persona = NULL;
    				ultima_persona = NULL;
    			}else{
    				//asigno a la siguiente persona de la lista como primera si está existe
    				primera_persona = tempPersona->siguiente;
    				primera_persona->anterior = NULL;
    			}

    			return TRUE;
    		}
    	// si la persona a borrar es la ultima de la lista
    		if(tempPersona == ultima_persona)
    		{
    			   ultima_persona = tempPersona->anterior;
    			   ultima_persona->siguiente = NULL;
    			//libero espacio en memoria del registro borrado
    			free(tempPersona);
    			return TRUE;
    		}
    	tempPersona->anterior->siguiente = tempPersona->siguiente;
    	tempPersona->siguiente->anterior = tempPersona->anterior;
    	//libero espacio en memoria del registro borrado
    	free(tempPersona);
    	return TRUE;
    	}

      //avanzo al siguiente en la lista
     tempPersona = tempPersona->siguiente;
	}while(tempPersona != NULL);

	return FALSE;
}

//función para modificar los datos de una persona que ya exista en la agenda
int modificar()
{
	Persona *tempPersona = primera_persona;
	char palabara_clave[25];
	char nombre_nuevo[25],apellidoP_nuevo[25],apellidoM_nuevo[25],fecha_nueva[15],direccion_nueva[50],telefono_nuevo[25];
	
	printf("\n----Modificando datos----");
	printf("*Tenga en cuenta que si existen más registros con el mismo apellido, serán modificados en el orden de la lista");
	printf("\nIngrese el apellido paterno para modificar el registro en la agenda:");
	scanf("%s",&palabara_clave);
	// limpio buffer de saltos de linea
	while(getchar() != '\n');
    //do para recorrer la agenda
    do
    {
       //si la cadena es igual a la buscada
       if(strcmp(palabara_clave,tempPersona->apellidoP) == 0)
    	{
   		printf("\nRegistros encontrados que coinciden con %s:",palabara_clave);
	    printf("\n Apellido paterno:%s\n Apellido materno:%s\n Nombre:%s\n Fecha nacimiento:%s\n Dirección:%s\n Teléfono:%s\n",tempPersona->apellidoP,tempPersona->apellidoM,tempPersona->nombre,tempPersona->fecha_n,tempPersona->direccion,tempPersona->telefono);  
    	//pido los nuevos datos para el registro
    	printf("Ingrese el nuevo Nombre:");
    	scanf( "%s", &nombre_nuevo);
    	printf("Ingrese el nuevo Apellido paterno:");
    	scanf( "%s", &apellidoP_nuevo);
    	printf("Ingrese el nuevo Apellido materno:");
    	scanf( "%s", &apellidoM_nuevo);
    	printf("Ingrese la nueva fecha de nacimiento:");
    	scanf( "%s", &fecha_nueva);
    	printf("Ingrese la nueva dirección:");
    	scanf( "%s", &direccion_nueva);
    	printf("Ingrese el nuevo teléfono");
    	scanf( "%s", &telefono_nuevo);
    	// limpio buffer de saltos de linea
		while(getchar() != '\n');

		//asigno los nuevos valores al registro de la agenda copiando la cadena con strcpy
		 strcpy(tempPersona->nombre, nombre_nuevo);
		 strcpy(tempPersona->apellidoP, apellidoP_nuevo);
		 strcpy(tempPersona->apellidoM, apellidoM_nuevo);
		 strcpy(tempPersona->fecha_n, fecha_nueva);
		 strcpy(tempPersona->direccion, direccion_nueva);
		 strcpy(tempPersona->telefono, telefono_nuevo);
    	}

      //avanzo al siguiente en la lista
     tempPersona = tempPersona->siguiente;
	}while(tempPersona != NULL);

	return TRUE;
}

//función para consultar (ver todos los datos de una persona en la agenda)
int consulta()
{
	Persona *tempPersona = primera_persona;
	char palabara_clave[25];
	printf("\n----Consultando agenda----");
	printf("\nIngrese el apellido paterno a buscar en la agenda:");
	scanf("%s",&palabara_clave);
    printf("\nRegistros encontrados que coinciden con %s:",palabara_clave);
    //do para recorrer la agenda
    do
    {
    	//si la cadena es igual a la buscada
       if(strcmp(palabara_clave,tempPersona->apellidoP) == 0)
    	{
	    printf("\n Apellido paterno:%s\n Apellido materno:%s\n Nombre:%s\n Fecha nacimiento:%s\n Dirección:%s\n Teléfono:%s\n",tempPersona->apellidoP,tempPersona->apellidoM,tempPersona->nombre,tempPersona->fecha_n,tempPersona->direccion,tempPersona->telefono);  
    	}

      //avanzo al siguiente en la lista
     tempPersona = tempPersona->siguiente;
	}while(tempPersona != NULL);

	return TRUE;
}

//función que valida la opción ingresada por el usuario desde el menú de opciones
int valida_opcion(int opcion)
{
   if (opcion >= 1 && opcion <=6 )
   {
   	return TRUE;
   }else{
   	return FALSE;
   }
}

//función para comprobar si la lista está vacia 
int lista_vacia()
{
	//Si no hay personas que mostrar
	if(primera_persona == NULL)
	{
		printf("\n\nNo hay registros en la agenda.");
		return TRUE;
	}else{	
		return FALSE;
	}
}

//función que recorre toda la agenda completa mostrando todos los registros en pantalla
int ver_agenda_completa()
{
	Persona *tempPersona=primera_persona;

	printf("\n----Mostrando agenda completa----");
	do{
		//muestro datos de la persona
		printf("\n\nNombre:%s",tempPersona->nombre);
		printf("\nApellido paterno:%s",tempPersona->apellidoP);
		printf("\nApellido materno:%s",tempPersona->apellidoM);
		printf("\nFecha de nacimiento:%s",tempPersona->fecha_n);
		printf("\nDirección:%s",tempPersona->direccion);
		printf("\nTeléfono:%s",tempPersona->telefono);
		//avanzo al siguiente en la lista
		tempPersona=tempPersona->siguiente;
	}while(tempPersona != NULL);

	return TRUE;
}

//función para mostrar el menú principal de opciones de la agenda
int mostrar_menu()
{
	int opcion;
	printf("\n\n\t\t\t\t\t\t----Menú principal----");
	printf("\n\t\t\tSeleccione una opción:");
	printf("\n\t\t\t\t1-Dar de alta una persona");
	printf("\n\t\t\t\t2-Dar de baja a una persona");
	printf("\n\t\t\t\t3-Modificar datos de una persona existente en la agenda");
	printf("\n\t\t\t\t4-Consultar datos de una persona");
	printf("\n\t\t\t\t5-Ver toda la agenda");
	printf("\n\t\t\t\t6-Salir del programa");
	printf("\n\t\t\topcion:");
	scanf("%i",&opcion);
	// limpio buffer de saltos de linea
	while(getchar() != '\n');

		if(valida_opcion(opcion))
		{
	
			switch(opcion)
			{
				case 1:
				if(!alta())
				{
					printf("\nError en al agregar persona.");
				}

				break;

				case 2:
				if(lista_vacia()){break;}
				if(!baja())
				{
					printf("\nNo existe registro con ese apellido paterno.");
				}
				break;

				case 3:
				if(lista_vacia()){break;}
				if(!modificar())
				{
					printf("\nError al modificar persona.");
				}
				break;

				case 4:
				if(lista_vacia()){break;}
				if(!consulta())
				{
					printf("\nError al consultar datos del usuario.");
				}
				break;

				case 5:
				if(lista_vacia()){break;}
				ver_agenda_completa();
				break;

				case 6:
				printf("\nCerrando la agenda...");
				return FALSE;
				break;

				default:
				printf("Error en el menú");
			}

		}else{
			printf("\n Opción introducida incorrecta. Ingrese una opción correcta, presione ENTER para continuar");
			// limpio buffer de saltos de linea
			while(getchar() != '\n');
		}
}

//función principal del programa
int main()
{
//asigno la bandera de salida para terminar el programa
int exit = EXIT_NO;

	while(exit == EXIT_NO)
	{
		if(!mostrar_menu())
		{
			exit = EXIT_OK;
		}
	}

  	printf("\nPrograma finalizado.\n");

	return FALSE;
}