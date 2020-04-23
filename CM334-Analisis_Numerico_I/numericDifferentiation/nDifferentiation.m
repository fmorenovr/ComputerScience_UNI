#!/usr/bin/octave -qf

%  obtiene la aproximacion de la n-esima derivada mediante la extrapolacion de Richardson
%  mediante un listado de puntos (x,f(x))
%  donde la n-esima derivada depende de n+1 puntos evaluados

%  donde: 
%  Df,n+1(x, h) = ( 2^n.Df,n(x, h) − Df,n(x, 2h) )/ (2^n − 1)

%  Db,n+1(x, h) = ( 2^n.Db,n(x, h) − Db,n(x, 2h) )/(2n − 1)
%  Dc,2(n+1)(x, h) = ( 2^2n.Dc,2n(x, h) − Dc,2n(x, 2h) )/(2^2n − 1)

%  Df,n = n diferencia hacia adelante.
%  Db,n = n diferencia hacia atras.
%  Dc,2n = n diferencia central.

%  se busca resolver el sistema A.c = b
%  donde A son los coeficientes de las funciones y b es el numerador de la derivada.

%  por ejemplo tomemos la segunda derivada en c4 ( derivada central de orden 2)

% -------------------------------------------------
function [c] = nDifferentiation(N,points)
  format rat;
  %difapx.m to get the difference approximation for the Nth derivative
  l = max(points);
  L = abs(points(1)-points(2))+ 1;
  if L < N + 1
    error('More points are needed!');
  endif
  for n = 1:L
    A(1,n) = 1;
    for m = 2:L + 2
      A(m,n) = A(m - 1,n)*l/(m - 1);
    endfor %Eq.(5.3.5)
    l = l-1;
  endfor
  b = zeros(L,1); b(N + 1) = 1;
  c =(A(1:L,:)\b)'; % coefficients of difference approximation formula
  err = A(L + 1,:)*c'; eoh = L-N; %coefficient & order of error term
  if abs(err) < eps
    err = A(L + 2,:)*c';
    eoh = L - N + 1;
  endif
  if points(1) < points(2)
    c = fliplr(c);
  endif
  disp('La matriz de coeficientes de aproximacion de taylor es: ');
  disp(A);
  disp('El vector que contiene 1 en la n-sima derivada: ');
  disp(b);
  fprintf("El error es %5.18f\n",err);
  fprintf("El orden de error es %5.18f\n",eoh);
endfunction

% -------------------------------------------------
