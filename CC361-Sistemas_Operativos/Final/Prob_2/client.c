#include<stdio.h> 
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
 
int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Error creando el socket");
    }
    puts("Socket creado");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Conexion con el servidor remoto
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("fallo la coneccion. Error");
        return 1;
    }
     
    puts("Conectado\n");
     
    //comunicacion con el servidor remoto
    while(1)
    {
        printf("Ingresar mensaje : ");
        scanf("%s" , message);
         
        //Enviamos datos
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("fallo envio");
            return 1;
        }
         
        //Recibimos respuesta del servidor
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv fallo");
            break;
        }
         
        puts("Servidor repondio :");
        puts(server_reply);
    }
     
    close(sock);
    return 0;
}
