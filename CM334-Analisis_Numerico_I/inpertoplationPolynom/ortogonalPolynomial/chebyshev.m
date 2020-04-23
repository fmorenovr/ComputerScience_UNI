function [Chebpol,x,y] = chebyshevInter(fx,N,a,b)
  % f = funcion a inerpolar en [a,b] de grado N con N+1 puntos
  % Chebpol = coeficientes del polinomio de newton
  % (x,y) nodos de chebyshev
  if nargin ==2; a=-1;a=1; endif
  % creando N+1 puntos
  f=fx;
  k = 1:N+1;
  theta = (2*k-1)*pi/(2*N+2);
  xn = cos(theta); % nodos de cheby en [-1, 1]
  yn = f(xn);
  x = (b-a)/2*xn + (a+b)/2; % lo lleva al intervalo [a , b]
  y = f(x);
  % construccion de los dm ( coeficientes de la combinacion lineal de f(x) = dm.Tm(x) )
  d = [];
  d0 = sum(yn)/(N+1);
  d = [d, d0];
  d1 = sum(yn.*xn)*2/(N+1);
  d = [d, d1];
  for m=2:N
    T_m = cos(m*theta);
    fxT = yn.*T_m;
    dm = sum(fxT)*2/(N+1);
    d = [d, dm];
  endfor
  xn = (2*x -(a+b))/(b-a);
  % construccion de los polinomios de chebyshev y sumarlos
  T_0 = 1; T_1 = [1 0];
  c = d(1)*[0 T_0] + d(1)*T_1;
  for m=2:N
    T_2 = 2*[T_1 0];
    n = length(T_2) - length(T_0);
    T_0 = [zeros(1,n) T_0];
    T_2 = T_2 - T_0;
    c = [0 c] + d(m)*T_2;
    T_0 = T_1;
    T_1 = T_2;
  endfor
  Chebpol = c;
endfunction

[c,x,y]=chebyshevInter(@fexp,10,-1,1);
t=-1:.01:1;
ft=fexp(t);
cx=polyval(c,x);
ct=chebpolEvalClenshaw(c,x);
hold on
grid on
plot(t,ft,'b-','Linewidth',2); % funcion original
hold on
plot(x,y,'m-','Linewidth',2); % nodos chebyshev
hold on
plot(x,cx,'g-','Linewidth',2); % funcion interpolada por chebyshev
hold on
plot(x,ct,'y-','Linewidth',2); % funcion interpolada por chebyshev
hold on

function [result] = fexp(x)
  n=length(x);
  if n>1
    str = [];
    for i=1:n
      str=[str,1/(x(i)^8+1)];
    endfor
    result=str;
  else
    result = 1/(x^8+1);
  endif
end
