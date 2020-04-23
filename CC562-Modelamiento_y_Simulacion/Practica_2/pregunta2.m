function Fx = pregunta2(n)
% usando le metodo de la compisicion %
  clc;
  % usamos el metodo exponencial %
  % P(x) = lambda*exp (-1*lambda*x)
  x = rand(n);
  fx = zeros(n,1);
  lambda = 1; % en este caso de integral
  
  for i = 1:n
    Y = lambda*exp (-1*lambda*i);
    fx(i) = fx(i) + x(i)^Y * Y;
  end
  Fx = cumsum(fx)./n;
  % funcion de densidad
  figure(1);
  plot(1:n,fx);
  % funcion de distribucion
  figure(2);
  plot(1:n,Fx);
end