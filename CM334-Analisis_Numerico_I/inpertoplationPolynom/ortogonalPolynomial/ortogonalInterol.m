% -------------------------------------------------

%   INTERPOLACION POR POLINOMIOS ORTOGONALES

%   Int(a,b) [ f(x) - Pn(x)]^2 dx

%   donde Pn(x) = an.x^n + ... + a1.x + a0 = Sum(k=0,n) ak.x^k

%   E = Int(a,b) (f(x) - Pn(x))^2 dx
%   E = Int(a,b) f(x)^2 dx - 2.Sum(k=0,n) ak.Int(a,b) [x^k.f(xk)] dx + Int(a,b) (Pn(x))^2 dx

%   entonces tenemos que resolver las (n+1) ecuaciones:
%   Sum(k=0,n) ak. Int(a,b) x^(j+k) = Int(a,b) x^j f(x) dx, j = 0,1,..,n

% -------------------------------------------------

%                      peso             intervalo
%   Hermite            e^(-x*x)         [-Inf,Inf]
%   Chebyshev     1/(1-x*x)^(1/2)        [-1,1]
%   Laguerre           e^(-x)           [0,Inf]
%   Legendre             1               [-1,1]

% -------------------------------------------------

%  intervalo [a,b] se transforma de [-1,1]: x1 = 1/2*[( b - a )x + (a + b)/2]
