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
% polinomios de chebyshev Tn(x)
function [Tn] = chebyshevPoly(N)
  % Tn+1(x) = 2xTn(x)-Tn-1(x) polinomio de hermite de grado n
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
% polinomio interpolante de chebyshev
function [Cpol,ti] = chebyshevInterpol(x1,y)
  n=length(x1)-1;
  a=x1(1);
  b=x1(n+1);
  x=2*x1/(b-a) - 1; % yendo al intervalo [-1,1]
  % regresando:
  % x1 = (b-a)/2*x + (a+b)/2 ;
  Cpol = 0;
  % calculo de los polinomios
  ti = zeros(n+1,n+1);
  T_0=1;
  T_1=[1 0];
  ti(1,:) = [zeros(1,length(ti)-length(T_0)) T_0];
  ti(2,:) = [zeros(1,length(ti)-length(T_1)) T_1];
  lti = length(ti);
  for j=3:n+1 %Tn
    T_2 = 2*[T_1 0];
    T_0 = [0 0 T_0];
    T_2 = T_2 - T_0;
    T_n = T_2;
    ti(j,:) = [zeros(1,lti-length(T_n)) T_n];
    T_0 = T_1;
    T_1 = T_2;
  endfor
  % calculo de los coeficientes cj
  tval=zeros(n+1,n+1);
  for i=1:n+1
    for j=1:n+1
      tval(i,j) = polyval(ti(i,:),x(j));
    endfor
  endfor
  c=zeros(1,n+1);
  c(:) = c(:) + 2/(n+1);
  c(1) = c(1)/2;
  for j=1:n+1
    suma = 0;
    for k=1:n+1
      suma = suma + y(k)*tval(j,k);
    endfor
    c(j)=c(j)*suma;
  endfor
  for m = 1:n+1
    Cpol = Cpol + c(m)*ti(m,:); % c0t0 + c1t1 + ... Polinom Interpolante
  endfor
endfunction

% --------------------------------------------------
