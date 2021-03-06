% funcion exponencial a la -x^2
function [result] = fexp(x)
  n=length(x);
  fun = @(x) exp(x*x);
  if n>1
    str = [];
    for i=1:n
      str=[str, (exp(-x(i)*x(i))*quad(fun,0,x(i)))];
    endfor
    result=str;
  else
    result = exp(-x*x)*quad(fun,0,x);
  endif
end

% fexp = @(x) cos(x)-x;

%16*x(i)^4*exp(-x(i)^2) – 48*x(i)^2*exp(-x(i)^2) + 12*exp(-x(i)^2);
%-32*x^5*exp(-x^2) + 160*x^3*exp(-x^2) - 120*x*exp(-x^2)
%x=0:0.001:1;

%16*x^4*exp(-x^2) – 48*x^2*exp(-x^2) + 12*exp(-x^2)

%q = quad(fun,-Inf,Inf);
