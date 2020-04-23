#!/usr/bin/octave -qf

%  4. METODO DE CHEBYSHEV

%   Construye el polinomio, basandose en la funcion y sus puntos
%   equidistanciados mediante la forma xk = cos((2n+1-2k)/(2(n+1))*pi)
%   que son las raices de sus polinomios
%   Nodos de chebyshev

%   POLINOMIOS DE CHEBYSHEV
%   T0(x)=cos(0)=1 y T1(x) = cos(cos-1(x)) = x
%   Tn+1(x) = 2xTn(x) - Tn-1(x)

%   Tn(x) = n.Sum(k=0,n) [(-2)^k.(n+k-1)!(1-x)^k/((n-k)!.(2k)!)]
%   Tn(cos(x)) = cos(nx)
%   x [-1,1]


%   POLINOMIO DE INTERPOLACION DE CHEBYSHEV
%   una funcion es interpolada por chebyshev es de la forma:

%   f(x) = 1/2*d0 + Sum(m=1,N) dm.Tm(x),

%   donde:
%     Expancion contigua:
%      dm = 2/pi*Int(-1,1) [ 1/sqrt(1-x*x) .f(x).Tn(x) ] dx

%     Expansion discreta:
%      dm = 2/(N) Sum(k=0,N) f(xk).Tm(xk)

%   d0 = 1/(N) Sum(k=0,N) f(xk).cos(0)
%   dm = 2/(N) Sum(k=0,N) f(xk).cos(m(2N+1-2k)/(2N+2)*pi) , para m = 1,2,...,N

% --------------------------------------------------
% polinomio chebyshev Tn(x)
function [Tn] = chebyshevPoly(N)
  %Tn+1(x) = 2xTn(x)-Tn-1(x) polinomio de hermite de grado n
  if N <= 0, Tn = 1;
  elseif N==1,  Tn = [1 0];
  else,
    T_0 = 1;
    T_1 = [1 0];
    for j=2:N
      T_2 = 2*[T_1 0];
      T_0 = [0 0 T_0];
      T_2 = T_2 - T_0;
      Tn = T_2;
      %disp(Tn);
      T_0 = T_1;
      T_1 = T_2;
    endfor
  endif
end

% --------------------------------------------------
% polinomio de interoplacion de chebyshev
function [Chebpol,x] = chebyshevInterpol(fn,n)
  x = cos((2*(1:n)'-1)*pi/2/n); % puntos de chebyshev ( nodos )
  y = feval(fn,x);
  T = [zeros(n,1) ones(n,1)];
  Chebpol = [sum(y)/n zeros(1,n-1)];
  a = 1;
  for k = 2:n
    T = [T(:,2) a*x.*T(:,2)-T(:,1)]; % POLINOMIOS DE CHEBYSHEV
    Chebpol(k) = sum(T(:,2).* y)*2/n; % coeficientes del polinomio
    a = 2;
  endfor
endfunction

% --------------------------------------------------
%  forma del polinomio de chebyshev p(x) = Sum anTn(x)
%  que tienen la forma = u0 - xu1, un = cn, un-1 = cn-1 + 2xun
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
  f = @(x) 1./(1+25*x.^2);
  [c,x] = chebyshevInterpol(f,11);
  t = -1:.01:1;
  plot(t,f(t),'b-','Linewidth',2,t,chebpolEvalClenshaw(c,t),'r-','Linewidth',2,x,f(x),'ok');
