#!/usr/bin/octave -qf

% se diferencian de los problemas de valor inicial pues, los de valor inicial solo

% tienen un punto fijo, ya sea el inicial o el final.

% este metodo es para solucion de sistemas con 2 puntos extremos y de segundo orden

% y'' = f(x,y,y')  a<=x<=b
% y(a) = alpha. y(b) = beta.

% D={ a<=x<=b, -inf< y,y' < inf  }
% y ademas se tiene que f_y y f_y' son continuas:

% i) f_y(x,y,y')>0 Para Todo (x,y,y') pertenece a D
% ii) existe una constante M
%    |f_y'(x,y,y')<=M para toda (x,y,y') pertenece a D.

% tiene solucion unica.

% ejemplo:

% y'' + exp(-xy) + sen(y') = 0, 1<=x<=2  y(1)=y(2)=0

% con f(x,y,y') = -exp(-xy) - sen(y')

% f_y(x,y,y') = x exp(-xy) > 0, |f_y'(x,y,y')|=|-cos(y')|<=1.

% si tiene la forma de 

% y'' = p(x)y' + q(x)y + r(x)  a<=x<=b. y(a) = alpha. y(b) = beta.

% satiface:

% i) p(x),q(x) y r(x) son continuas en [a,b]
% ii) q(x)>0 en [a,b]

% entonces el problema tiene solucion unica.
% w1 = y(x) y w2 = y'(x)

% y''1 = p(x) y'1 + q(x) y1 + r(x)

% u1 = y1, u2 = u''2

% y''2 = p(x) y'2 + q(x) y2

% v1 = y2, v2 = y''2

% donde: y(x) = y1(x) + (y(b) - y1(b))/y2(b)*y2(x);

% --------------------------------------------------

function [x1,w1,w2] = disparoLineal(a,b,px,qx,rx,ya,yb,n)
  h=(b-a)*1.0/n;
  p=px;
  q=qx;
  r=rx;
  u1=zeros(1,n+1);
  u2=zeros(1,n+1);
  v1=zeros(1,n+1);
  v2=zeros(1,n+1);
  u1(1)=ya;
  u2(1)=0.;
  v1(1)=0.;
  v2(1)=1.;
  
  for i=1:n
    x=a+(i-1)*h;

    k1(1)=h*u2(i);
    k1(2)=h*(p(x)*u2(i) + q(x)*u1(i) + r(x));

    k2(1)=h*(u2(i) + 0.5*k1(2));
    k2(2)=h*(p(x+h/2)*(u2(i)+0.5*k1(2)) + q(x+h/2)*(u1(i)+0.5*k1(1))+r(x+h/2));

    k3(1)=h*(u2(i) + 0.5*k2(2));
    k3(2)=h*(p(x+0.5*h)*(u2(i)+0.5*k2(2)) + q(x+0.5*h)*(u1(i)+0.5*k2(1))+r(x+0.5*h));

    k4(1)=h*(u2(i) + k3(2));
    k4(2)=h*(p(x+h)*(u2(i)+k3(2)) + q(x+h)*(u1(i)+k3(1))+r(x+h));
    
    u1(i+1)=u1(i) + (k1(1) + 2*k2(1) + 2*k3(1) + k4(1))/6;
    u2(i+1)=u2(i) + (k1(2) + 2*k2(2) + 2*k3(2) + k4(2))/6;
    
    k_1(1)=h*v2(i);
    k_1(2)=h*(p(x)*v2(i) + q(x)*v1(i));
    
    k_2(1)=h*(v2(i)+0.5*k_1(2));
    k_2(2)=h*(p(x+0.5*h)*(v2(i)+0.5*k_1(2)) + q(x+0.5*h)*(v1(i)+0.5*k_1(1)) );
    
    k_3(1)=h*(v2(i)+0.5*k_2(2));
    k_3(2)=h*(p(x+0.5*h)*(v2(i)+0.5*k_2(2)) + q(x+0.5*h)*(v1(i)+0.5*k_2(1)) );
    
    k_4(1)=h*(v2(i) + k_3(2));
    k_4(2)=h*(p(x+h)*(v2(i)+k_3(2)) + q(x+h)*(v1(i)+k_3(1)));
    
    v1(i+1)=v1(i) + (k_1(1) + 2*k_2(1) + 2*k_3(1) + k_4(1))/6;
    v2(i+1)=v2(i) + (k_1(2) + 2*k_2(2) + 2*k_3(2) + k_4(2))/6;
    
    %fprintf("u1: %0.18f u2: %0.18f v1: %0.18f v2: %0.18f\n",u1(i),u2(i),v1(i),v2(i));
  endfor
  
  w1(1)=ya;
  w2(1)=(yb-u1(n+1))/v1(n+1);
  fprintf("\nx:%0.8f u:%0.8f v:%0.8f y(x):%0.8f y'(x):%0.8f\n",a,u1(1),v1(1),w1(1),w2(1));
  
  for i=2:n+1
    w1(i) = u1(i) + w2(1)*v1(i);
    w2(i) = u2(i) + w2(1)*v2(i);
    x1(i)=a+(i-1)*h;
    fprintf("\nx:%0.8f u:%0.8f v:%0.8f y(x):%0.8f y'(x):%0.8f\n",x1(i),u1(i),v1(i),w1(i),w2(i));
  endfor
endfunction

% px=@(x) -2/x;qx=@(x) 2/x/x;rx=@(x) sin(log(x))/x/x;a=1;b=2;ya=1;yb=2;
