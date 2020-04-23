function [F,P] = pregunta2(n)
  clc;
  F = zeros(n,1);
  P = zeros(n,1);
  P(1) = (1/2)^(2) + (1/2)/(3);
  F(1) = P(1)*1;
  for j = 2:n
    Pj = (1/2)^(j+1) + ((1/2)*2^(j-1))/(3^j);
    F(j) = F(j-1) + Pj*j;
    P(j) = P(j-1) + Pj;
  end
  figure(1)
  plot(1:n,F);
  hold on
  figure (2)
  plot(1:n,P);
  hold on
end
