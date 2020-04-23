function Fx = pregunta1(n)
% usando le metodo de la compisicion %
  clc;
  % usamos el metodo exponencial %
  % P(x) = lambda*exp (-1*lambda*x)
  x = rand(n);
  fx = zeros(n,1);
  Fx = zeros(n+1,1);
  p = 0;
  for i = 1:n
    aux = rand();
    p = p + aux;
    if p < 1 && p >0
      Y = (3-exp(-2*p)+2*p)/3.0
    else
      if p > 1
        Y = (3-exp(-2*p))/3.0
      end
    end
    fx(i) = fx(i) + x(i)* Y;
    Fx(i+1) = Fx(i) + fx(i);
  end
  % funcion de densidad
  figure(1);
  plot(1:n,fx);
  % funcion de distribucion
  figure(2);
  plot(1:(n+1),Fx);
end