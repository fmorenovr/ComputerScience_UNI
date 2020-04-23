#!/usr/bin/octave -qf

% 1. METODO DE MATRIZ DE VANDERMONDE

%  crea un sistema de ecuaciones cuyos coeficientes son el polinomio evaluado en x, y sus incognitas son los coeficientes del polinimio
%  Devuelve la matriz de Vandermonde y los coeficientes del polinimio
%  x = 10:2:14
%  y = [12 18 21]
% --------------------------------------------------
function [Van,Vanpol] = vandermondeInterpol(x,y)
  Van = vander(x); % matriz de vandermonde
  T = y';
  vanpol = Van\T % es lo mismo que V^-1.y;
  vanpol = vanpol';
end

% --------------------------------------------------
