#!/usr/bin/octave -qf

%  3. METODO DE NEWTON

%  Se contruye el polinomio gradualmente partiendo de la coordenada (x0,y0) 
%  y se va anadiendo progresivamente

%  p0 interpola a {x0}
%  p1 interpola a {x0,x1} ...
%  p0(x) = y0 interpola a x0

%  p1(x) interpola a {x0,x1}, q1 = p1 - p0
%  q1(x) = A1(x-x0) ==> p1(x1) = p0(x) + q1(x1) = y1
%  ==> A1 = (y1 - p0(x1))/(x1-x0)

%  p2 = p1 + q2 interpola a x0, x1, x2 y se anula en x0 y x1
%  q2(x)=A2(x-x0)(x-x1) con A2 adecuado
%  p2(x2) = p1(x2) + q2(x2) = y2 ==> A2 = (y2-p1(x2))/((x2-x0)(x2-x1))

%  p(x) = A0 + A1(x-x0) + A2(x-x0)(x-x1) + ...
% x = [-1 0 1 3]
% y = [0 1 -2 4]
% --------------------------------------------------
function [Npol,DD] = newtonInterpol(x,y)
  n = length(x) - 1;
  DD = zeros(n+1,n+1);
  DD(1:n+1,1) = y(:);
  for k=2:n+1
    for m=1:n+2-k
      DD(m,k) = (DD(m+1,k-1) - DD(m,k-1))/(x(m+k-1)-x(m)); % diferencias dividas
    end
  end
  a = DD(1,:);
  Npol = a(n+1);
  for k=n:-1:1
    Npol = [Npol a(k)] - [0 Npol*x(k)]; % n(x)*(x-x(k-1)) + a_k-1
  end
end

% --------------------------------------------------
