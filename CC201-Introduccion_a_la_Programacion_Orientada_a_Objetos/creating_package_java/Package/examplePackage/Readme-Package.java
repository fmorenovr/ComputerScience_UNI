/*

Compilar package

Desde nuestro directorio padre, de donde se crean los subdirectorios

javac Display/DisplayDeck.java Classes-Deck/Card.java Classes_Deck/Deck.java

y para ejecutar en donde se encuentre el main

java fuente
java paquete.fuente
java paquete.subpaquete.fuente

en este caso:

java Display.DisplayDeck

---------------------------------------------
CREACION DE UN JAR

jar -cf DisplayDeck.jar Display/DisplayDeck.class Classes_Deck/Card.class Classes_Deck/Deck.class

La opción "c" indica que queremos crear un fichero.jar nuevo. Si ya existía, se machacará, así que hay que tener cuidado. La opción "f" sirve para indicar el nombre del fichero, que va inmediatamente detrás. 
genera un fichero Displaydeck.jar que contiene todos los .class y una carpeta Manifest, que es de la misma estructura que nuestros package


Si queremos agregar otros .class de otros packages, usamos de manera similar
Para cambiar un fichero dentro de un jar o añadirle uno nuevo, la opción del comando jar es "u". Si el fichero existe dentro del jar, lo reemplaza. Si no existe, lo añade.


java -uf DisplayDeck.jar otroPackage/archivo.class


Para ver que hay dentro de un package JAR:

jar tf DisplayDeck.jar

**************
CONOCIENDO EL MAIN
Y para ejecutar, de manera similar:

java -cp ./DisplayDeck.jar  Display.DisplayDeck

donde primero va la direccion del .jar y luego la ruta del main

**************
Sin conocer el MAIN

Pero que pasaria si no supieramos donde se encuentra el main, y tengamos muchos package ??
Creamos un fichero de nombre manifest.txt
y ese fichero contendra donde se ubica la clase main

Main-Class: Display.DisplayDeck

Y luego lo anadimos al .jar

jar cmf manifest.txt DisplayDeck.jar Display/DisplayDeck.class Classes_Deck/Card.class Classes_Deck/Deck.class

si es cmf, el manifest.txt va primero que .jar
si es cfm, el .ar va primero anets del manifest.txt

y finalmente compilamos con fichero:

java -jar DisplayDeck.jar

*/
