function [P] = pregunta2(num=100)
  clc;
  fprintf('##########################################\n');
  fprintf('             Pregunta 2\n');
  P = zeros(1,num);
  PA = zeros(1,num);
  F = zeros(1,num);

  u1 = unifrnd(0,1);
  u2 = unifrnd(0,1);
  if u2<0.9
    P(1) = floor(10*u1)+5;
  else
    P(1) = floor(5*u1)+6;
  end
  F(1) = P(1);
  
  for i=2:num
    u1 = unifrnd(0,1);
    u2 = unifrnd(0,1);
    if u2<0.9
      P(i) = floor(10*u1)+5;
    else
      P(i) = floor(5*u1)+6;
    end
    F(i) = F(i-1)+P(i)*i;
  end
  figure(1)
  plot(1:num,F);
  hold on
  figure (2)
  plot(1:num,cumsum(P)./num);
  hold on
end
