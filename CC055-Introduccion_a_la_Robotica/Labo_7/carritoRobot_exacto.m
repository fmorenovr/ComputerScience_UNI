% Control of car by method exact
pkg load control;
clear;
clc;
close all;

v = 3;
L = 3.5;
dt = 0.005;

%x0 = input('Introducir coordenada inicial x : ');
x0 = 20;
y0 = input('Introducir coordenada inicial y : ');
phi0 = input('Introducir angulo inicial phi (grados) :');
phi0 = phi0*pi/180;

A = [ 0 1
      0 0 ];
B = [ 0
      1 ];

q1 = 0.1;%input('q1: ');
q2 = 0.1;%input('q2: ');  
% q1 = 0.15;
% q2 = 0.10;
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

%x_ = input('Introducir xast : ');

x   = x0;
y   = y0;
y_ = y0;
phi_ = 45*pi/180;
phi = phi0;

k = 1;
while( (x < 100) && (x > 0) )
   posx(k,1) = x;
   posy(k,1) = y;
   posphi(k,1) = phi;
   t(k,1) = (k-1)*dt;
   tandel = L*(k1*(y-(x+y)/2) + k2*v*(sin(phi)-sin(phi_)))/(v*v*cos(phi));
   del = atan(tandel);
   if(del > pi/4)
      del = pi/4;
   elseif (del < -pi/4)
      del = -pi/4;
   end
   delta(k,1) = del*180/pi;
   xp = v*cos(phi);
   x = x + xp*dt;
   yp = v*sin(phi);
   y = y + yp*dt;
   phip = -v/L*tan(del);
   phi = phi + phip*dt;
   k++;
end
posphi = 180/pi*posphi;

figure(1);
subplot(3,1,1); plot(t,posx);    grid;
title('Posicion X');
subplot(3,1,2); plot(t,posy);    grid;
title('Posicion Y');
subplot(3,1,3); plot(t,posphi);  grid;
title('Angulo Phi');

%figure(2);
%plot(t,delta);
%title('Angulo');  grid;

figure(3);
plot(posx,posy);
title('Trayectoria');
axis([0 100 0 100]);   grid;

