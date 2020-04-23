#!/usr/bin/octave -qf

phi_1=0;
phi_2=0;
y=zeros(1000,1);

for j=3:1000
  y(j)=phi_1*y(j-1) + phi_2*y(j-2) + randn();
endfor

disp(y);
plot(y);
