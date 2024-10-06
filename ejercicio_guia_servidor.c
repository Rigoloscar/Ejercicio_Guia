#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
	
	// INICIALIZACIONES
	// ----------------
	// Abrimos el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error creant socket");
	}
		
	// Hacemos bind al puerto
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	
	// Asocia el socket a cualquiera de las IP de la maquina. 
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// Escucharemos en el port 9050
	serv_adr.sin_port = htons(9050);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0){
		printf("Error al bind");
	}
		
	// La cola de peticiones pendientes no podr? ser superior a 4
	if (listen(sock_listen, 4) < 0){
		printf("Error en el Listen");
	}
	
	// ESCUCHA Y PROCESADO
	// -------------------
	// Bucle infinito
	while (1){
		printf("Escuchando\n");
		
		// Creamos el socket de connexion
		sock_conn = accept(sock_listen, NULL, NULL);
		printf("He recibido conexion\n");
		
		int terminar = 0;
		while (terminar == 0){
		
			// Recibimos la peticion del cliente
			ret = read(sock_conn,peticion, sizeof(peticion));
			printf("Recibida una peticion\n");
			
			// Tenemos que añadirle la marca de fin de string 
			// para que no escriba lo que hay despues en el buffer
			peticion[ret]='\0';
			
			// Escribimos la peticion en la consola
			printf("La peticion es: %s\n", peticion);
			char *p = strtok(peticion, "/");
			int codigo =  atoi (p);
			char nombre[20];
			
			// En caso que el codigo no sea de desconnexion
			if (codigo != 0){
				p = strtok( NULL, "/");
				strcpy (nombre, p);
				printf("Codigo: %d, Nombre: %s\n", codigo, nombre);
			}
			// Piden la longitud del nombre
			if (codigo == 1){ 
				sprintf(respuesta,"La longitud del nombre %s es %d de letras", nombre, strlen(nombre));
			}
			// Piden saber si el nombre es bonito
			else if (codigo == 2){
				
				if ((nombre[0]=='M') || (nombre[0]=='S')){
					sprintf(respuesta,"%s es un nombre bonito", nombre);
				}
				else{
					sprintf(respuesta,"%s es un nombre feo", nombre);
				}
			}
			// Piden saber si es alto
			else if (codigo == 3){
				p = strtok(NULL, "/");
				float altura =  atof (p);
				
				if (altura >= 1.80){
					sprintf(respuesta, "%s es una persona alta", nombre);
				}
				else{
					sprintf(respuesta, "%s es una persona bajita", nombre);
				}
			}
			// Piden devolver el nombre en mayusculas
			else if (codigo == 4){
				char nombre_mayus[20];
				
				for (int i = 0; i < (strlen(nombre)); i++){
					nombre_mayus[i] = toupper(nombre[i]);
				}
				strcpy(respuesta, nombre_mayus);
			}
			// Piden saber si el nombre es palindromo
			else if (codigo == 5){
				int palindromo = 1;
				int ultimo = strlen(nombre) - 1;
				
				for (int i = 0; i < (strlen(nombre)/2); i++){
					if(tolower(nombre[i]) != tolower(nombre[ultimo - i])){
						palindromo = 0;
					}
				}
				
				if(palindromo == 1){
					sprintf(respuesta, "%s es un nombre palindromo", nombre);
				}
				else{
					sprintf(respuesta, "%s no es un nombre palindromo", nombre);
				}
			}
			// Desconnexion con el cliente
			else if (codigo == 0){
				printf("Connexion finalizada\n");
				terminar = 1;
			}
			
			// Enviamos la respuesta
			if (codigo != 0){
				printf("Respuesta: %s\n", respuesta);
				write (sock_conn,respuesta, strlen(respuesta));
			}
		}
		// Se acabo el servicio para este cliente
		close(sock_conn); 
	}
}
