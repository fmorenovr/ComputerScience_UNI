#!/usr/bin/octave -qf

% 2. METODO DE LAGRANGE

% Calcula el polinomio de interpolación de Lagrange
% x e y vectores de datos; L coeficientes polinomio resultante,
% li matriz de polinomio base, donde cada polinomio se ve horizontalmente.
% x = [-1 0 1 3]
% y = [0 1 -2 4]
% --------------------------------------------------
function [li,Lpol] = lagrangeInterpol(x,y)
  n = length(x) - 1;
  Lpol = 0;
  li = zeros(n+1,n+1);
  for m = 1:n+1
    P = 1;
    for k = 1:n+1
      if k~=m, % distinto
        P = conv(P,poly(x(k))) / (x(m)-x(k));
      end
    end
    li(m,:)=P; % Polinomios base de Lagrange (x - xi)/(xj - xi)
    Lpol = Lpol + y(m)*P; % y0l0 + y1l1 + ... Polinom Interpolante
  end
end

% --------------------------------------------------
