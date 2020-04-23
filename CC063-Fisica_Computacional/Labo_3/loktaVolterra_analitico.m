#!/usr/bin/octave

A=[ 0  0  0 -20 -30 -5;
    0  0  0 -1  -3  -7;
    0  0  0 -4  -10 -20;
    20 30 35 0  0   0;
    3  3  3  0  0   0;
    7  8  20 0  0   0];

[autovectores,v]=eig(A);
# devuelve los autovectores de manera vertical, y los autovalores en matriz diagonal
#autovectores
autovalores = [];
k=1;
len1 = length(v);
len2 = length(v(1,:));
for i=1:len1
  for j=1:len2
    if i==j
      autovalores(k) = v(i,j);
      k++;
    end
  end
end

autovalores=autovalores';

# Valores Iniciales

lenu = length(autovectores);
lamb = [3,3,1,1,5,0.1];
iters=1000;

# Solucion Analitica

Xt=zeros(lenu,100);
k=1;
for t=0:1/iters:1
  x0=0;
  for i=1:lenu
    x0 = x0 + lamb(i)*exp(autovalores(i)*t)*autovectores(:,i);
  end
  Xt(:,k) = x0;
  k++;
end
figure(1)
plot(0:iters,Xt(1,:),0:iters,Xt(2,:),0:iters,Xt(3,:),0:iters,Xt(4,:),0:iters,Xt(5,:),0:iters,Xt(6,:));
hold on
figure(2)
plot(Xt(1,:),Xt(4,:));
hold on

figure(3)
plot(Xt(1,:),Xt(5,:));
hold on

figure(4)
plot(Xt(1,:),Xt(6,:));
hold on

figure(5)
plot(Xt(2,:),Xt(4,:));
hold on

figure(6)
plot(Xt(2,:),Xt(5,:));
hold on

figure(7)
plot(Xt(2,:),Xt(6,:));
hold on

figure(8)
plot(Xt(3,:),Xt(4,:));
hold on

figure(9)
plot(Xt(3,:),Xt(5,:));
hold on

figure(2)
plot(Xt(3,:),Xt(6,:));
hold on
