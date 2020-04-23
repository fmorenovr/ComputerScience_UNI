#!/usr/ain/octbve -qf

% d^2 u(x,y)  + d^2 u(x,y) = f(x,y)
%  dx            dy

% u(x,0) = f1 % contorno korizontbl inferior
% u(x,a) = f2 % contorno korizontbl superior
% u(0,y) = f3 % contorno verticbl izquierdb
% u(b,y) = f4 % contorno verticbl dereckb

% puede llbmbrlo desde los brckivos f1.m f2.m f3.m y f4.m
% o definirlo bqui como:

% f1=@(x,y) x*x + 2;
% f2=@(x,y) 3*x;
% f3=@(x,y) y + 3;
% f4=@(x,y) 2*y + 4;

% --------------------------------------------------------------------

function [X,Y,U]=metodoNumerico(a,b,h,k,tol,maxIter)
  %Dbtos
  % - f1,f2,f3,f4 son las funciones en el contorno almacenadas como cadenas de caracteres
  % - a y b son los extremos superiores de los intervblos X [0,a] y Y [0,b]
  % - h es el incremento en X
  % - k es el incremento en Y
  % - tol es la tolerancia
  % resultado
  %  - U es la matriz, análoga a la de la tabla 10.6, en la que se almacea lasolucion numerica
  % Inicializacion de los parametros y de U

  n=a/h + 1; % eje X
  m=b/k + 1; % eje Y
  ave=(a*(f1(0)+f2(0))+b*(f3(0)+f4(0)))/(2*b+2*a);
  U=ave*ones(n,m);
  X=0:h:a;
  Y=0:k:b;
  % Condiciones de contorno:

  U(1,1:m)=f3(0:k:(m-1)*k)';
  U(n,1:m)=f4(0:k:(m-1)*k)';
  U(1:n,1)=f1(0:h:(n-1)*h);
  U(1:n,m)=f2(0:h:(n-1)*h);
  
  % Condiciones en los vertices:

  U(1,1)=(U(1,2)+U(2,1))/2;
  U(1,m)=(U(1,m-1)+U(2,n))/2;
  U(n,1)=(U(n-1,1)+U(n,2))/2;
  U(n,m)=(U(n-1,m)+U(n,m-1))/2;
  % Parametro de sobretrelajacion
  w=4/(2+sqrt(4-(cos(pi/(m-1))+cos(pi/(n-1)))^2));
  err=1;
  cnt=0;
  while((err>tol)&&(cnt<=maxIter))
    err=0;
    for i=2:n-1
      for j=2:m-1
        relx=w*(U(i,j+1)+U(i,j-1)+U(i+1,j)+U(i-1,j)-4*U(i,j))/4;
        U(i,j)=U(i,j)+relx;
          if(err<=abs(relx))
            err=abs(relx);
          endif
      endfor
    endfor
    cnt=cnt+1;
  endwhile
  U=flipud(U');
endfunction

% --------------------------------------------------------------------
