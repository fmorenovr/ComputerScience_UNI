pkg load control;
clear;
clc;
close all;
pi = 3.141592;

m = 0.050;
M = 1.5;
L = 0.35;
g = 9.8182;

a21 = g*(M+m)/(L*M);
a41 = -m*g/M;
b1 = -1/(M*L);
b2 = 1/M;

A = [  0   1   0   0
      a21  0   0   0
       0   0   0   1
      a41  0   0   0 ];

B = [ 0
      b1
      0
      b2 ];

%q1 = input('Peso phi   : ');
%q2 = input('Peso phi_p : ');
%q3 = input('Peso x     : ');
%q4 = input('Peso xp    : ');
q1 = 1e3;
q2 = 1e1;
q3 = 1e4;
q4 = 1e1;

Q = [ q1  0   0   0
       0   q2  0   0
       0   0   q3  0
       0   0   0   q4 ];

R = [ 1 ];

#BRB = B*inv(R)*B';

[P,l,K] = care(A,B,Q,R);
K
ti = 0;
dt = 0.001;
tf = 4.0;

phi_ini = input('Introducir angulo inicial [grados] : ');

x(1,1) = phi_ini*pi/180;
x(2,1) = 0;
x(3,1) = 0;
x(4,1) = 0;

k = 1;
for t = ti:dt:tf
  ang(k,1) = x(1,1);
  pos(k,1) = x(3,1);
  tim(k,1) = t;
  phi  = x(1,1);
  phip = x(2,1); # derivada de phi
  F = -K*x;
  FF(k,1) = F;
  a = F - m*g*sin(phi)*cos(phi) + m*L*phip*phip*sin(phi);
  b = M + m*sin(phi)*sin(phi);
  x2p = a/b;
  phi2p = (g*sin(phi) - x2p*cos(phi)) / L;
  x(1,1) = x(1,1) + x(2,1)*dt; # actualiza el tetha
  x(2,1) = x(2,1) + phi2p*dt; # actualiza la derivada tetha
  x(3,1) = x(3,1) + x(4,1)*dt; # actualiza el x
  x(4,1) = x(4,1) + x2p*dt; # actualiza la derivada de x
  k = k + 1;
end
kf = k - 1;

figure(1);
subplot(3,1,1);
plot(tim,ang);
xlabel('Tiempo')
ylabel('Angulo');
subplot(3,1,2);
plot(tim,pos);
xlabel('Tiempo')
ylabel('Posicion');
subplot(3,1,3);
plot(tim,FF);
xlabel('Tiempo');
ylabel('Fuerza');

disp('   ');
disp('   ');
disp('Presione cualquier tecla ' );
pause;

AA = 0.3;
BB = 0.05;

figure(2);
axisxmin = -1.0;
axisxmax =  1.0;
axisymin = -0.1;
axisymax =  1.0;

axis([axisxmin  axisxmax  axisymin  axisymax]);
% axis([ -0.5  0.5  -0.1  0.5 ]); 

for k = 1:10:kf
  x1 = pos(k,1) + AA/2;
  y1 = BB;
  x2 = pos(k,1) - AA/2;
  y2 = BB;
  x3 = pos(k,1) - AA/2;
  y3 = 0;
  x4 = pos(k,1) + AA/2;
  y4 = 0;
  x0 = pos(k,1);
  y0 = BB;
  xm = x0 + L*sin(ang(k,1));
  ym = y0 + L*cos(ang(k,1));
  xx = [ x1  x2  x3  x4  x1 ];
  yy = [ y1  y2  y3  y4  y1 ];
  xp1 = axisxmin;
  yp1 = 0;
  xp2 = axisxmax;
  yp2 = 0;
  xp = [ xp1  xp2 ];
  yp = [ yp1  yp2 ];
  mx = [ x0  xm ];
  my = [ y0  ym ]; 
  clf;
%  plot(xp,yp,'r',xx,yy,'g',mx,my,'g');
  plot(xp,yp,'r');
  hold on;
  plot(xx,yy,'Linewidth',2);
  hold on;
  plot(mx,my,'Linewidth',2);
  axis([axisxmin  axisxmax  axisymin  axisymax]);
%  axis([ -0.5  0.5  -0.1  0.5 ]); 
%  hold on;
 pause(1/8);
end
