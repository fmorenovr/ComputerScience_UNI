#!/usr/bin/octave

# Analizando ahora solo por pares:
alpha =0.5;
AR=[ 0    -1;
     alpha 0];
x0 = [1,2,3,4,5,6]';
lenu = length(x0);
iters=1000;
r = [1,-1];
xt1 = zeros(lenu,iters);
xt1(:,1)=x0;
iters=1000;
dt = 0.01;
# funcion de interaccion entre poblaciones
function [xt,dt] = loktaVolterr(xt1,p,d,iter,r,AR,dt)
  xt = zeros(2,iter);
  xt(1,1) = xt1(p,1);
  xt(2,1) = xt1(d,1);
  for i=2:iter
    for j=1:2
      xt(j,i)= xt(j,i-1) + xt(j,i-1)*(r(j)+AR(j,:)*xt(:,i-1))*dt;
    end
  end
end

[Xt1,dt] = loktaVolterr(xt1,1,4,iters,r,AR,dt);
figure(1)
plot(Xt1(1,:),Xt1(2,:))
hold on
figure(2)
plot(1:iters,Xt1(1,:),1:iters,Xt1(2,:))
hold on
[Xt1,dt] = loktaVolterr(xt1,1,5,iters,r,AR,dt);
figure(3)
plot(Xt1(1,:),Xt1(2,:))
hold on
figure(4)
plot(1:iters,Xt1(1,:),1:iters,Xt1(2,:))
hold on
[Xt1,dt] = loktaVolterr(xt1,1,6,iters,r,AR,dt);
figure(5)
plot(Xt1(1,:),Xt1(2,:))
hold on
figure(6)
plot(1:iters,Xt1(1,:),1:iters,Xt1(2,:))
hold on
[Xt1,dt] = loktaVolterr(xt1,2,4,iters,r,AR,dt);
figure(7)
plot(Xt1(1,:),Xt1(2,:))
hold on
figure(8)
plot(1:iters,Xt1(1,:),1:iters,Xt1(2,:))
hold on
[Xt1,dt] = loktaVolterr(xt1,2,5,iters,r,AR,dt);
figure(9)
plot(Xt1(1,:),Xt1(2,:))
hold on
figure(10)
plot(1:iters,Xt1(1,:),1:iters,Xt1(2,:))
hold on
[Xt1,dt] = loktaVolterr(xt1,2,6,iters,r,AR,dt);
figure(11)
plot(Xt1(1,:),Xt1(2,:))
hold on
figure(12)
plot(1:iters,Xt1(1,:),1:iters,Xt1(2,:))
hold on
[Xt1,dt] = loktaVolterr(xt1,3,4,iters,r,AR,dt);
figure(13)
plot(Xt1(1,:),Xt1(2,:))
hold on
figure(14)
plot(1:iters,Xt1(1,:),1:iters,Xt1(2,:))
hold on
[Xt1,dt] = loktaVolterr(xt1,3,5,iters,r,AR,dt);
figure(15)
plot(Xt1(1,:),Xt1(2,:))
hold on
figure(16)
plot(1:iters,Xt1(1,:),1:iters,Xt1(2,:))
hold on
[Xt1,dt] = loktaVolterr(xt1,3,6,iters,r,AR,dt);
figure(17)
plot(Xt1(1,:),Xt1(2,:))
hold on
figure(18)
plot(1:iters,Xt1(1,:),1:iters,Xt1(2,:))
hold on
