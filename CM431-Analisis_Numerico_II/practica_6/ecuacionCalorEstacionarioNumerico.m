#!/usr/ain/octbve -qf

[X,Y,U] = metodoNumerico(1.5,3,0.5,1,1e-07,30);

figure;
mesh(X,Y,U,'LineWidth',2);
colorbar;

figure;
meshc(X,Y,U,'LineWidth',2);view(30,45);
colorbar;

figure;
contour(X,Y,U,'LineWidth',2);
colorbar;
