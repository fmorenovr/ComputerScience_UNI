% Control de brazo robot de dos grados de libertad.
% Linealización por aproximación alrededor del punto
% de operación  phi1=0,  phi2=0.

pkg load control;
clear;
clc;
close all;

% Ecuacion del brazo:
%  M0'' = C + Gg + ST

%  X' = AX + Bu

%  0' = A0 + BT
% donde T es torque

% barra 1 
m1 = 0.15;
L1 = 0.35;
l1 = 0.16;     %  Longitud
I1 = 4.1e-3;   % Inercia

% barra 2
m2 = 0.12;
L2 = 0.30;
l2 = 0.12;     % Longitud
I2 = 3.2e-3;   % Inercia

M11 = I1 + m1*l1*l1 + m2*L1*L1 + m2*L1*l2;
M12 = m2*L1*l2;
M21 = I2 + m2*l2*l2 + m2*L1*l2;
M22 = I2 + m2*l2*l2;

M = [ M11  M12
      M21  M22 ];

S = [ 1  -1
      0   1 ];

ceros = zeros(2,2);

iden = eye(2);

A = [ ceros  iden
      ceros  ceros ];

B = [ ceros
      inv(M)*S ];

q1 = 15;%input('Peso q1 [100] : ');
q2 = 15;%input('Peso q2 [100]: ');  
q3 = 0;%input('Peso q3 [5]: ');
q4 = 0;%input('Peso q4 [5]: ');  
% El peso q3 y q4 reduce la mala respuesta inicial.

Q = diag([ q1 q2 q3 q4 ]);
R = eye(2);

# ecuacion de ricatti
# A'*X + X*A - X*B*G + Q = 0
# A'*X + X*A - X*B*inv(R)*B'*X + Q = 0
# G = inv(R)*B'*X = K
# A - B*K = A - B*inv(R)*B'*X
# X = A'*X*A - (A'*X*B)*inv(R+B'*X*B)*(B'*X*A) + Q
[X,leig,K] = care(A,B,Q,R);
K = B'*X
k1 = K(1,1);
k2 = K(1,2);

% ti = 0;   tf = 4;    dt = 0.001;
% t = ti:dt:tf;
% t = t';
% phi1_ = 80*pi/180;   % Angulo deseado phi1_
% phi2_ = 80*pi/180;   % Angulo deseado phi2_

% Trayectoria triangular. Inicio (0.65,0)
% Triangulo vertices: (0.40,0.00)(0.525,0.10)(0.65,0)
v = 5*0.01;   % Velocidad de desplazamiento en X
ti = 0;       % tiempo inicial
dt = 0.001;   % diferencial de tiempo
t1 = 0.125/v; % tiempo en el eje X
t2 = 0.250/v;
tt1 = ti:dt:t1;
tt1 = tt1';
tt2 = (t1+dt):dt:t2;
tt2 = tt2';
tf = t2;       % tiempo final

x1 = -0.125/t1*tt1 + 0.65;
x2 = 0.125/(t1-t2)*(tt2-t2) + 0.40;
xr = [ x1; x2 ];

y1 = 0.10/t1*tt1;
y2 = 0.10/(t1-t2)*(tt2-t2);
yr = [ y1; y2];

x2y2 = xr.*xr + yr.*yr;

AA = xr./sqrt(x2y2);
BB = (x2y2+L1*L1-L2*L2)./(2*L1*sqrt(x2y2));

r1A = acos(AA);
r1B = acos(BB);

phi1_ = r1A - r1B;
ZZ = (x2y2-(L1*L1+L2*L2))./(2*L1*L2);
phi2_ = acos(ZZ);
% phi1_ = r1A + r1B; % Calculo de phi1_ - Posicion simetrica
% phi2_ = -phi2_;    % Calculo de phi2_ - Posicion simetrica

phi1_ = real(phi1_);
phi2_ = real(phi2_);
nr12 = length(phi1_);
% phi1_ = pi/2*ones(nr12,1);
% phi2_ = pi/3*ones(nr12,1);

xx = L1*cos(phi1_) + L2*cos(phi1_+phi2_);
yy = L1*sin(phi1_) + L2*sin(phi1_+phi2_);

phi1  = 0;
phi2  = 0;
phi1p = 0;
phi2p = 0;
ang = [ phi1   phi2 ]';
vel = [ phi1p  phi2p ]';
k = 1;

for tt = ti:dt:tf
 ang1(k,1) = phi1;
 ang2(k,1) = phi2;
 t(k,1) = tt;
 x = [phi1-phi1_(k,1); phi2-phi2_(k,1); phi1p; phi2p ];
 % calculo de los torque
 T = -K*x;
 T1(k,1) = T(1);
 T2(k,1) = T(2);
 % creacion de la matriz M
 M11_ = I1 + m1*l1*l1 + m2*L1*L1 + m2*L1*l2 * cos(phi2);
 M12_ = m2*L1*l2*cos(phi2);
 M21_ = I2 + m2*l2*l2 + m2*L1*l2*cos(phi2);
 M22_ = I2 + m2*l2*l2;
 M = [ M11_  M12_
       M21_  M22_ ];
 % creacion de la matriz C
 C1 = m2*L1*l2*(phi1p+phi2p)^2*sin(phi2);
 C2 = -m2*L1*l2*phi1p*phi1p*sin(phi2);
 C = [ C1
       C2 ];
 accel = inv(M)*(C + S*T);
 ang = ang + vel*dt;
 vel = vel + accel*dt;
 phi1 = ang(1,1);
 phi2 = ang(2,1);
 phi1p = vel(1,1);
 phi2p = vel(2,1);
 k = k + 1;
end
%ang1 = ang1*180/pi;
%ang2 = ang2*180/pi;
%figure(1);
%plot(t,ang1);
%figure(2);
%plot(t,ang2);


xra = L1*cos(ang1) + L2*cos(ang1+ang2);
yra = L1*sin(ang1) + L2*sin(ang1+ang2);

figure(1);
subplot(2,1,1);
plot(t,T1);
title('Torque 1');
subplot(2,1,2);
plot(t,T2);
title('Torque 2');

figure(2);
subplot(3,1,1);
plot(t,ang1*180/pi,t,phi1_*180/pi);
title('phi 1');
subplot(3,1,2);
plot(t,ang2*180/pi,t,phi2_*180/pi);
title('phi 2');
subplot(3,1,3);
plot(xra,yra,xx,yy);
title('grafico trazado vs grafico a dibujar');

disp('Pause');
pause;

% animacion de la grafica
figure(3);
grid;
title('Animacion de movimiento del brazo');
axis([ 0 0.8 -0.4 0.4]);
hold on;
nk = length(ang1);
dk = 15;    % Saltos para la animación
xra = [ xra
        xra(nr12,1)*ones(dk,1) ];
yra = [ yra
        yra(nr12,1)*ones(dk,1) ];     
% xra(nr12+1:nr12+dk-1,1) = xra(nr12,1)*ones(dk,1);
% yra(nr12+1:nr12+dk-1,1) = yra(nr12,1)*ones(dk,1);

for k = 1:dk:nk
  x1A = 0;
  y1A = 0;
  x1B = x1A + L1*cos(ang1(k,1));
  y1B = y1A + L1*sin(ang1(k,1));
  x2A = x1B;
  y2A = y1B;
  ang12 = ang1(k,1) + ang2(k,1);
  x2B = x2A + L2*cos(ang12);
  y2B = y2A + L2*sin(ang12);
  xxx = [ x1A   x2A   x2B ];
  yyy = [ y1A   y2A  y2B ];
  plot(xxx,yyy,'-b','Linewidth',2);
  pause(0.001);
  plot(xxx,yyy,'-w','Linewidth',2);
  xxx1 = xra(k,1);
  xxx2 = xra(k+dk-1,1);
  yyy1 = yra(k,1);
  yyy2 = yra(k+dk-1,1);
  xxra = [ xxx1  xxx2 ];
  yyra = [ yyy1 yyy2];
  plot(xxra,yyra,'-r','Linewidth',2); 
end
figure(4);
title('Grafica dibujada por el brazo');
plot(xx,yy,'-b');
grid;
