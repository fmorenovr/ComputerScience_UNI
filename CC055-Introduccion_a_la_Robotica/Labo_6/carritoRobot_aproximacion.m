% Control of car by lineal approximation
pkg load control;
clear;
clc;
close all;

v = 2;
L = 3;
dt = 0.001;
ti = 0;
tf = 20;

A = [ 0  v
      0  0 ];
B = [ 0
      -v/L ];

q1 = input('Peso q1: ');
q2 = input('Peso q2: ');
Q = diag([ q1 q2 ]);
R = [1];

# ecuacion de ricatti
# A'*X + X*A - X*B*G + Q = 0
# A'*X + X*A - X*B*inv(R)*B'*X + Q = 0
# G = inv(R)*B'*X = K
# A - B*K = A - B*inv(R)*B'*X
# X = A'*X*A - (A'*X*B)*inv(R+B'*X*B)*(B'*X*A) + Q
[X,leig,K]  = care(A,B,Q,R);
K = B'*X
k1 = K(1,1);
k2 = K(1,2);
#x = input('Introducir coordenada inicial x [20]: ');
x = 30;
y = input('Introducir coordenada inicial -30<= y <= 30: ');
phi = input('Introducir angulo inicial -180 <= phi <= 180]: ');
phi = phi*pi/180;
y_ = 0;
phi_ = 0;
k = 1;
tanpi4 = tan(pi/4);
while((x>0) & (x<50))
  posx(k,1) = x;
  posy(k,1) = y;
  posphi(k,1) = phi;
  t(k,1) = (k-1)*dt;
  tandel = -k1*(y-y_) - k2*(phi-phi_);
  if(tandel > tanpi4)
    tandel = tanpi4;
  elseif(tandel < -tanpi4)
    tandel = -tanpi4;
  end
  del = atan(tandel);
  delta(k,1) = 180/pi*del;
  xp = v*cos(phi);
  yp = v*sin(phi);
  phip = -v/L*tan(del);
  x = x + xp*dt;
  y = y + yp*dt;
  phi = phi + phip*dt;
  k = k + 1;
end

figure(1);
subplot(2,1,1);
plot(posx,posy);    grid;
title('Trayectoria');
subplot(2,1,2);
plot(t,delta);     grid;
title('Direccion del angulo');


