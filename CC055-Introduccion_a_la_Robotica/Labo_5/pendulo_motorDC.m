pkg load control;
clear;
clc;
close all;

# Ecuacion de Ricatti

pi = 3.141592;

# sistema motor DC

R = 1.2;
J = 4.3*1e-5;
b = 40;
r = 0.15;
Kt = 0.057;
Kb = 0.056;
L = 1;%e-3;

# sistema carrito

m = 0.050;
M = 1.5;
l = 0.35;
g = 9.8182;

MrJ = M*r*r+J;

a21 = -g*((M+m)*r*r+J)/(MrJ*l);
a24 = -(b/(MrJ*l));
a25 = r*Kt/(MrJ*l);
a41 = -(m*g*r*r/MrJ);
a44 = -(b/MrJ);
a45 = r*Kt/MrJ;
a54 = -(Kb/(r*L));
a55 = -(R/L);
b5 = 1/L;

# Matriz de estado
A = [  0   1   0   0   0
      a21  0   0  a24  a25
       0   0   0   1   0
      a41  0   0  a44  a45
      0    0   0  a54  a55];

# Ley de control
B = [ 0
      0
      0
      0
      b5 ];

% a mayor q1 menor phi, mayor q3 menor x
% a mayor q2 menor phi', mayor q4 menor x'

%q1 = input('Peso phi   : ');
%q2 = input('Peso phi_p : ');
%q3 = input('Peso x     : ');
%q4 = input('Peso xp    : ');
% a partir de 24 grados muere con q1=q3=1e10;q2=q4=0;
% a partir de 44 grados muere con q1=q3=1e9;q2=q4=0;
% a partir de 44 grados muere con q1 = 1e9;q2 = 1e3;q3 = 1e9;q4 = 0;
% a partir de 39 grados muere con q1 = 1e9;q2 = 1e5;q3 = 1e9;q4 = 0;
q1 = 1e2;
q2 = 1e3;
q3 = 1e2;
q4 = 0;
q5 = 1e3;

Q = [ q1   0   0   0   0
       0   q2  0   0   0
       0   0   q3  0   0
       0   0   0   q4  0
       0   0   0   0   q5];

R = [ 1 ];

# ecuacion de ricatti
# A'*X + X*A - X*B*G + Q = 0
# A'*X + X*A - X*B*inv(R)*B'*X + Q = 0
# G = inv(R)*B'*X = K
# A - B*K = A - B*inv(R)*B'*X
# X = A'*X*A - (A'*X*B)*inv(R+B'*X*B)*(B'*X*A) + Q
[X,leig,K] = care(A,B,Q,R);
K
ti = 0;
dt = 0.001;
tf = 4.0;

%phi_ini = input('Introducir angulo inicial [grados] : ');
phi_ini=12;

x(1,1) = phi_ini*pi/180;
x(2,1) = 0;
x(3,1) = 0;
x(4,1) = 0;
x(5,1) = 0;

k = 1;
for t = ti:dt:tf
  ang(k,1) = x(1,1); # angulo inicial
  tim(k,1) = t;
  phi  = x(1,1); # valor de phi
  phip = x(2,1); # derivada de phi
  pos(k,1) = x(3,1); # posicion inicial
  xp = x(4,1); # derivada de x
  i = x(5,1); # valor de la intensidad de corriente
  V = -K*x; # actualiza V
  VV(k,1) = V;
  a = r*Kt*i - b*xp - m*g*r*r*sin(phi)*cos(phi) + m*l*r*r*phip*phip*sin(phi);
  b = MrJ + m*r*r*sin(phi)*sin(phi);
  x2p = a/b; # segunda derivada de x
  phi2p = (x2p*cos(phi)-g*sin(phi))/l; # segunda derivada de phi
  ip = (V - Kb/r*xp-R*i)/L; # derivada de i
  x(1,1) = x(1,1) + x(2,1)*dt; # actualiza el phi
  x(2,1) = x(2,1) + phi2p*dt; # actualiza la derivada phi
  x(3,1) = x(3,1) + xp*dt; # actualiza el x
  x(4,1) = x(4,1) + x2p*dt; # actualiza la derivada de x
  x(5,1) = x(5,1) + ip*dt; # actualiza la corriente i
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
plot(tim,VV);
xlabel('Tiempo');
ylabel('Voltaje');

disp('   ');
disp('   ');
disp('Presione cualquier tecla ' );
pause;

# Simulacion del movimiento

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
  xm = x0 + l*sin(ang(k,1));
  ym = y0 + l*cos(ang(k,1));
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
