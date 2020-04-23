# Criptografia Clasica

Algoritmos que se crearon a traves de la historia pero que ahora no se usan.

## Transposicion

Es un tipo de cifrado en el que unidades de texto plano se cambian de posición siguiendo un esquema bien definido

### Escitala

Consiste en agrupar el mensaje en bloques de un número X, generando una matriz X-(l/X), donde l es la longuitud del mensaje original.  
Transponemos la matriz y obtenemos un nuevo mensaje, es decir:

- mensaje: Hola soy Felipe
- tabla:   3

* Encrypt:

    * Agrupamos el mensaje en bloques de 3, se genera una matriz:
      
        Hol
        a s
        oy 
        Fel
        ipe
      
    * Haciendo una transpuesta, obtenemos una nueva matriz:
      
        HaoFi
        o yep
        ls le
      
    * Y leyendo fila a fila las letras obtenemos un nuevo mensaje:
      
        HaoFio yepls le

* Decrypt: Es el método invertido, el numero de tabla es el # de columnas.

## Sustitucion

Es un tipo de cifrado donde las letras se cambian por otras

### Mono-alfabetica

Utilizan un unico alfabeto

#### Monogramicos

Utilizan una letra a la vez.

##### Simple substitution

Sustituye de manera simple las letras del alfabeto.

Ej:

    a->x
    b->r
    c->f
    ...

##### Cesar

Metodo clasico de encriptamiento con desplazamineto, es decir:

- Alfabeto:       26 letras          (L)
- mensaje:        Hola soy Felipe    (X)
- desplazamiento: 3                  (n)
- cifrado:        Krod vrb Iholsh    (C)

* Encrypt:
  
    E(Xi) = (Xi + n) mod L = Ci

* Decrypt:

    D(Ci) = (Ci - n) mod L = Xi

* Donde:

    X: array de mensaje
    Xi: letra i-esima
    C: array cifrado
    Ci: letra cifrada i-esima
    n: desplazamiento
    L: longuitud del alfabeto.

##### Afin

Sustituye una letra de un alfabeto original por un alfabeto cifrado.

#### Poligramico

Sustituye varias letras a la vez.

##### PlayFair

Encripta cada bloque de 2 letras.

##### Hill

Encripta cada bloque de n letras.

#### Poli-alfabetica

Utilizan cualquier alfabeto

##### Periodica

Utiliza una clave de manera repetitiva hasta copar el tamaño del mensaje original

###### Vigenere

Consiste en realizar un ponderado entre cada una de las letras de un mensaje (sin contar espacios) con una palabra "clave", es decir:

- Alfabeto: 26 letras         (L)
- palabra:  Golang            (K)
- mensaje:  Hola soy Felipe   (X)
- clave:    Gola ngG olangG   
- cifrado:  Nbwa fue tplvvk   (C)

* Encrypt:
  
    E(xi) = (Xi + Ki) mod L = Ci

* Decrypt:

    * si (Ci - Ki) >= 0:
      
        D(Ci) = (Ci - Ki) mod L = Xi
  
    * sino:
    
        D(Ci) = (Ci - Ki + L) mod L = Xi

* Donde:
  
    X:  array de mensaje
    Xi: letra i-esima
    K:  palabra clave
    Ki: letra clave i-esima
    C:  array cifrado
    Ci: letra cifrada i-esima
    L:  longuitud del alfabeto

##### No Periodica

No utiliza una clave unica, puede generarse de manera dinamica partiendo de una semilla

###### Vernam

Consiste en un algoritmo basado en la encriptación XOR, puede generar una palabra clave a partir de una semilla (hasta conseguir el mismo tamaño del mensaje) los cuales realizan XOR para obtener un nuevo mensaje.

* Encrypt

     -------
     message: 0 0 1 0 1 1 0 1 0 1 1 1 ...
     pad:     1 0 0 1 1 1 0 0 1 0 1 1 ...
     XOR      ---------------------------
     cipher:  1 0 1 1 0 0 0 1 1 1 0 0 ...

* Decrypt

     ---------
     cipher:  1 0 1 1 0 0 0 1 1 1 0 0 ...
     pad:     1 0 0 1 1 1 0 0 1 0 1 1 ...
     XOR      ---------------------------
     message: 0 0 1 0 1 1 0 1 0 1 1 1 ...

