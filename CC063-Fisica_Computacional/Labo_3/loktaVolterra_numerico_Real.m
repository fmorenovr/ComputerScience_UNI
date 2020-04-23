#!/usr/bin/octave

A=[ 0  0  0 -20 -30 -5;
    0  0  0 -1  -3  -7;
    0  0  0 -4  -10 -20;
    20 30 35 0  0   0;
    3  3  3  0  0   0;
    7  8  20 0  0   0];

b = [-20 -30 -5;
      -1  -3 -7;
      -4 -10 -20];

c = [20 30 35;
     3  3  3;
     7  8  20];

[autovectores,v]=eig(A);
# devuelve los autovectores de manera vertical, y los autovalores en matriz diagonal
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
iters=5000;

# Solucion Numerica

x0 = zeros(lenu,1);
t=0;
for i=1:lenu
  x0 = x0 + lamb(i)*exp(autovalores(i)*t)*autovectores(:,i);
endfor

a = b*x0(1:lenu/2);
d = -1*c*x0(lenu/2+1:lenu);
r = a;
r(lenu/2+1:lenu)=d;
xt = zeros(lenu,iters); # lenu columnas y iters filas
xt(:,1)=x0;

# Metodo de Euler para la aproximacion de las poblaciones
dt=0.001;
for i=2:iters
  for j=1:lenu
    xt(j,i)= xt(j,i-1) + xt(j,i-1)*(r(j)+A(j,:)*xt(:,i-1))*dt;
  end
end

rango=1500;

figure(1)
plot(xt(1,1:rango),xt(4,1:rango));
hold on
figure(2)
plot(xt(1,1:rango),xt(5,1:rango));
hold on
figure(3)
plot(xt(1,1:rango),xt(6,1:rango));
hold on
figure(4)
plot(xt(2,1:rango),xt(4,1:rango));
hold on
figure(5)
plot(xt(2,1:rango),xt(5,1:rango));
hold on
figure(6)
plot(xt(2,1:rango),xt(6,1:rango));
hold on
figure(7)
plot(xt(3,1:rango),xt(4,1:rango));
hold on
figure(8)
plot(xt(3,1:rango),xt(5,1:rango));
hold on
figure(9)
plot(xt(3,1:rango),xt(6,1:rango));
hold on
figure(10)
plot(1:rango,xt(1,1:rango),1:rango,xt(2,1:rango),1:rango,xt(3,1:rango),1:rango,xt(4,1:rango),1:rango,xt(5,1:rango),1:rango,xt(6,1:rango));
hold on
