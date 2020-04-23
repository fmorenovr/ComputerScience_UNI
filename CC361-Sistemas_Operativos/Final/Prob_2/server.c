#include<stdio.h>
#include<string.h> 
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
     
    // Creamos un socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Error creando socket");
    }
    puts("Socket creado");
     
    // Definimos la estructura sockaddr_in
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind - enlazamos
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        // si hay error imprimimos
        perror("bind fallo. Error");
        return 1;
    }
    puts("bind creado");
     
    //Listen - Escuchamos sobre el socket
    listen(socket_desc , 3);
     
    //Aceptando conecciones entrantes
    puts("Esperando conecciones entrantes...");
    c = sizeof(struct sockaddr_in);
     
    //aceptamos coneccion de un cliente
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("coneccion entrate fallo");
        return 1;
    }
    puts("Coneccion aceptada");
     
    //Recibimos mensaje del cliente
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Devolvemos mensaje al cliente
        write(client_sock , client_message , strlen(client_message));
    }
     
    if(read_size == 0)
    {
        puts("El cliente se desconecto");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv fallo");
    }
     
    return 0;
}
