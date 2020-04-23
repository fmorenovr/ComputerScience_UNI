#!/usr/bin/octave -qf

%  6. METODO DE LEGENDRE

%   Construye el polinomio, mediante:

%   POLINOMIOS DE LEGENDRE
%   P0(x)=1 y P1(x) = x
%   FORMA DE LOS COEFICIENTES
%   Ln+1(x) = ( (2n+1).xLn(x) - n.Ln-1(x) )/(n+1)

%   Ln(x) = 2^n . Sum (k=0,n) x^k. C(n,k) . C((n+k-1)/2,n)
%   C(n,k) : combinatoria de n en k.
%   x [-1,1]

%   probar: f = @(x) 1./(1+25*x.^2)

%   POLINOMIO DE INTERPOLACION DE LEGENDRE
%   una funcion es interpolada por legendre de grado 2n+1

% --------------------------------------------------
% polinomio legendre Ln(x)
function Ln = legendrePoly(N)
  % Ln+1(x) = ( (2n+1).xLn(x) - n.Ln-1(x) )/(n+1)
  if N<=0, Ln=1;
  elseif N==1, Ln = [1 0];
  else
    L_0=1;
    L_1=[1 0];
    for j=2:N
      L_2 = (2*j-1)/j*[L_1 0];
      L_0 = (j-1)/j*[0 0 L_0];
      L_2 = L_2 - L_0;
      Ln = L_2;
      %disp(Ln);
      L_0 = L_1;
      L_1 = L_2;
    endfor
  endif
endfunction

% --------------------------------------------------
% polinomio de interoplacion de hermite
function [Lenpol,x] = legendreInterpol(x,y,n)
endfunction

% --------------------------------------------------
