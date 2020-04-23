#!/usr/bin/octave -qf

%  4. METODO DE CHEBYSHEV

%   Construye el polinomio, basandose en la funcion y sus puntos
%   equidistanciados mediante la forma xk = cos((2n+1-2k)/(2(n+1))*pi)
%   que son las raices de sus polinomios
%   Nodos de chebyshev
%   Tn+1(x) = 2xTn(x) - Tn-1(x), T0(x)=cos(0)=1 y T1(x) = cos(cos-1(x)) = x
%   Tn(x) = cos(ncos-1(x)) , x [-1,1]

%  probar: f = @(x) 1./(1+25*x.^2)

% --------------------------------------------------
function [Chebpol,x] = chebyshevInterpol(fn,n)
  x = cos((2*(1:n)'-1)*pi/2/n); % puntos de chebyshev ( nodos )
  y = feval(fn,x);
  T = [zeros(n,1) ones(n,1)];
  Chebpol = [sum(y)/n zeros(1,n-1)];
  a = 1;
  for k = 2:n
    T = [T(:,2) a*x.*T(:,2)-T(:,1)];
    Chebpol(k) = sum(T(:,2).* y)*2 / n;
    a = 2;
  end
end

% --------------------------------------------------

%  forma del polinomio de chebyshev p(x) = Sum anTn(x)
%  q tienen la forma = u0 - xu1, un = cn, un-1 = cn-1 + 2xun
%  uj = cj + 2xuj+1 - uj+2
%  nos retorna el valor de P(x0)

% --------------------------------------------------
function u = chebpolEvalClenshaw(Chebpol,x)
  n = length(Chebpol);
  u = Chebpol(n)*ones(size(x));
  if n > 1
    ujp1 = u;
    u = Chebpol(n-1) + 2*x*Chebpol(n);
    for j = n-2:-1:1
      ujp2 = ujp1;
      ujp1 = u;
      u = Chebpol(j)+2*x.*ujp1-ujp2;
    end
  u = u-x.*ujp1;
  end
end

% --------------------------------------------------
% 
%  f = @(x) 1./(1+25*x.^2);
%  [c,x] = chebpol_int(f,11);
%  t = -1:.01:1;
%  plot(t,f(t),'b',t,chebpolEvalClenshaw(c,t),'r',x,f(x),'ok')

