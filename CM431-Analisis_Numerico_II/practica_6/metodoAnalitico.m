x=0:0.05:1.5;
y=0:0.1:3;
n=1/pi;
[x,y]=meshgrid(x,y);
T= 2*(cos(n*x) + (2*csc(1.5*n) - cot(1.5*n))*sin(n*x)).*( cosh(n*y)+( (3-2*x*cosh(3*n)) / (2*x*sinh(3*n)) ) * sinh(n*y) );

figure;
mesh(x,y,T);
colorbar;

figure;
surfc(x,y,T,'LineWidth',0.08);view(30,45);
colorbar;

figure;
contour(x,y,T,'LineWidth',2);
colorbar;
