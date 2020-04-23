% -------------------------------------------------

%     Cuadraturas

% -------------------------------------------------

%                      peso             intervalo
%   Hermite            e^(-x*x)         [-Inf,Inf]
%   Chebyshev     1/(1-x*x)^(1/2)        [-1,1]
%   Laguerre           e^(-x)           [0,Inf]
%   Legendre             1               [-1,1]

% -------------------------------------------------

%  Int( a,b ) w(x).f(x) dx = Sum(k=1,n) ck.f(xk)

%   donde ck = Int(a,b) w(x).Ln(x) dx son los pesos de las sumas

%   donde Ln(x), son los polinomios interpolantes ( laguerre, legendre, chebyshev, hermite y lagrange )

%    METODOS DE SOLUCION:

%   1. Calculo de los pesos.(cuando los datos son discretos)
%     se tiene de datos los xk.
%     se puede interpolar por lagrange y calcular ck.


%   2. cuando tienes la funcion.
%     usas los datos de pesos y raices por cada polinomio.
%     donde las raices xk, son las raices del polinomio interpolante de grado 2n - 1


%   3. cuando tienes que calcular pesos y raices.
%     Creas un sistema de ecuaciones con n*n variables y n*n incognitas
%     n puntos y n pesos.
%     de la siguiente manera:

%     Int (a,b) w(x).Pn(x) = Sum(k=0,n-1) ck.Pn(xk) , donde n va de 0 hasta 2n-1
%     y los xk calculados son las raices de los polinomios, y los ck son los pesos.

%     o de otras formas, en vez de usar los polinomios interpolantes, usar funciones 1,x,x^2,x^3, ...
