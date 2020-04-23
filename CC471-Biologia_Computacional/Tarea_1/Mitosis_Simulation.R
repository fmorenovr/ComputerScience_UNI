#!/usr/bin/Rscript

# anadimos librerias
library(base);
library(methods);
library(graphics);
# sirve para S4 ( clases )

# obtiene los argumentos pasados por consola para la matriz de bits.
argv<-commandArgs(TRUE);

# verifica los argumentos
parameterInput<-function(args){
  if("--help" %in% args || "0" %in% args || as.numeric(args[1])<0 || as.numeric(args[2])<0) {
    cat("
      El programa necesita de 2 parametros de entrada
      para construir la matriz de bits de simulacion.
      El mapa de bits se construye de la siguiente manera:
      
      tejido es el mapa de bit {
        -1: celula cancerosa
         0: proteinas (alimento)
         1: celula buena
      }

      Argumentos:
      row         - numeric > 0
      col         - numeric > 0
      --help      - imprime este texto
 
      Example:
	Rscript 10 10 \n\n");
    q(save="no");
  }
}

# crea el mapa de bits
createBitMapCells<-function(args){
  rows<-as.numeric(args[1]); # eje Y = filas = horizontal
  cols<-as.numeric(args[2]); # eje X = columnas = vertical
  matrixCells<-matrix(0,rows,cols);
  #tejido<-apply(matrixCells, c(1,2), function(x){ sample(c(-1,0,1),1);});
  #return (tejido);
  for(i in 1:rows){
    for(j in 1:cols){
      matrixCells[i, j] <- sample(c(0,1),1);
      #matrixCells[i, j] <- 0;
    }
  }
  matrixCells[rows/2,cols/2]<-(-1);
  " for(i in (rows/2):(rows/2+1)){
    for(j in (cols/2):(cols/2+1)){
      matrixCells[i, j] <- (-1);
    }
  }"
  #xInit<-sample(1:rows,1);
  #yInit<-sample(1:cols,1);
  xInit<-1;
  yInit<-1;
  #matrixCells[xInit,yInit]<-(-1);
  return (list(m=matrixCells,x=xInit,y=yInit));
}

# funcion para dormir sistema
sleepSys <- function(time)
{
    p1 <- proc.time()
    Sys.sleep(time)
    proc.time() - p1 # The cpu usage should be negligible
}

# funcion que busca proteinas en los vecinos
searchFood<-function(matrixCells,x,y){
  pos<-c();
  orientation<-sample(1:2,1);
  direccion<-sample(1:2,1);
  # 1: horizontal
  # 2: vertical
  # 1: derecha / arriba
  # 2: izquierda / abajo
  # vertical
#  print(orientation);
  if(orientation==1){
    if(x>1 && x<10){
      if(matrixCells[x-1,y]==0 && direccion==1){
        #pos<-c(x-1,y);
        matrixCells[x-1,y]<-(-1);
      }
      if(matrixCells[x+1,y]==0 && direccion==2){
        #pos<-c(x+1,y);
        matrixCells[x+1,y]<-(-1);
      }
    } else{
      if(x==1){
        if(matrixCells[x+1,y]==0){
          #pos<-c(x+1,y);
          matrixCells[x+1,y]<-(-1);
        }
      } else{
        if(x==10){
          if(matrixCells[x-1,y]==0){
            #pos<-c(x-1,y);
            matrixCells[x-1,y]<-(-1);
          }
        }
      }
    }
  } else {
    if(y>1 && y<10){
      if(matrixCells[x,y-1]==0 && direccion==2){
        #pos<-c(x,y-1);
        matrixCells[x,y-1]<-(-1);
      }
      if(matrixCells[x,y+1]==0 && direccion==1){
        #pos<-c(x,y+1);
        matrixCells[x,y+1]<-(-1);
      }
    } else{
      if(y==1){
        if(matrixCells[x,y+1]==0){
          #pos<-c(x,y+1);
          matrixCells[x,y+1]<-(-1);
        }
      } else{
        if(y==10){
          if(matrixCells[x,y-1]==0){
            #pos<-c(x,y-1);
            matrixCells[x,y-1]<-(-1);
          }
        }
      }
    }
  }
  return (matrixCells);
}

# funcion que detecta los vecinos y si es 1 lo come
lookingForFood<-function(matrixCells){
  k<-0;
  for(i in 1:argv[1]){
    for(j in 1:argv[2]){
      if(matrixCells[i,j]==0){
        matrixCells[i, j] <-(-1);
        cat("generacion",k,"\n");
        print(matrixCells);
        k<-k+1;
      }
    }
  }
}

# funcion random a comer
chooseFood<-function(){
  "
  1: derecha   3: arriba
  2: izquierda 4: abajo
  "
  return (sample(1:4,1));
}

# clase Celula
createClassCell<-function(){
  setClass("Celula",representation(name="character",area="numeric",posx="numeric",posy="numeric"),prototype(name="Celula",area=1,posx=as.numeric(argv[1])/2,posy=as.numeric(argv[2])/2),validity=cellCheck);
  #setClass("Celula",representation(name="character",area="numeric",pos="double"),contains="Tejido");
}

# verifica si es correcta la celula
cellCheck<-function(object){
  errors <- character();
  area_value <- length(object@area);
  if(area_value<1){
    msg<-paste("Area es ",area_value,". no puede ser negativa",sep="");
    errors<-c(erros,msg);
  }
  if(length(erros)==0){ TRUE;} else{ errors;}
}

# objeto celula (instancia)
newCell<-function(nombre,x,y){
  # se usa contains dentro de setClass para decir que hereda
  cell<-new("Celula",name=nombre,area=1,posx=x,posy=y);
}

# funcion que representa las celulas
graphicCells<-function(matrixCells){
  x<-1:nrow(matrixCells);
  y<-1:ncol(matrixCells);
  image(x, y, matrixCells, col = heat.colors(10), axes = FALSE);
 # contour(x, y, matrixCells, levels = seq(90, 200, by = 5), add = TRUE, col = "peru")
 # axis(1, at = seq(100, 800, by = 100))
 # axis(2, at = seq(100, 600, by = 100))
 # box()
  title(main="Mitosis Celular",font.main=4);
}

# funcion main
main<-function(){
  system('clear');
  cat("
    Programa para simular la mitosis celular en R.\n
  ");

  if(length(argv) < 2) {
    argv <- c("--help")
  }
  createClassCell();
  parameterInput(argv);
  dataResult<-createBitMapCells(argv);
# recolectando data
  mapCells<-dataResult$m;
  xInicial<-dataResult$x;
  yInicial<-dataResult$y;

# verificando imprimiendo
  print(mapCells);
  cells<-1;
  while(cells<4){
    sleepSys(1);
    print(mapCells);
    graphicCells(mapCells);
    cells<-cells+1;
  }
#  mapCells<-searchFood(mapCells,xInicial,yInicial);
  #print(foodResult);
#  print(mapCells);
#  lookingForFood(mapCells);
}

main();
