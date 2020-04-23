#!/usr/bin/octave

# Solucion ideal

alpha = 0.5;
AI=[ 0  0  0 -1 -1 -1;
    0  0  0 -1  -1  -1;
    0  0  0 -1  -1 -1;
    alpha  alpha  alpha 0  0   0;
    alpha  alpha  alpha 0  0   0;
    alpha  alpha  alpha 0  0   0];

r=[1,1,1,-1,-1,-1];
lenu = length(r);
iters=5000;
x0 = [1,2,3,4,5,6]';
xt = zeros(lenu,iters); # lenu columnas y iters filas
xt(:,1)=x0;

# Metodo de Euler para la aproximacion de las poblaciones
dt=0.01;
for i=2:iters
  for j=1:lenu
    xt(j,i)= xt(j,i-1) + xt(j,i-1)*(r(j)+AI(j,:)*xt(:,i-1))*dt;
  end
end

figure(1)
plot(1:iters,xt(1,:),1:iters,xt(2,:),1:iters,xt(3,:),1:iters,xt(4,:),1:iters,xt(5,:),1:iters,xt(6,:));
hold on
figure(2)
plot(xt(1,:),xt(4,:));
hold on
figure(3)
plot(xt(1,:),xt(5,:));
hold on
figure(4)
plot(xt(1,:),xt(6,:));
hold on
figure(5)
plot(xt(2,:),xt(4,:));
hold on
figure(6)
plot(xt(2,:),xt(5,:));
hold on
figure(7)
plot(xt(2,:),xt(6,:));
hold on
figure(8)
plot(xt(3,:),xt(4,:));
hold on
figure(9)
plot(xt(3,:),xt(5,:));
hold on
figure(10)
plot(xt(3,:),xt(6,:));
hold on
