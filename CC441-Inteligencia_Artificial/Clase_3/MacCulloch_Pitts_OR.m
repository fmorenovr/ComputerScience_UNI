function [dwf] = MacCulloch_Pitts_OR(p,t,epochs)
%  MACCULLOCH-PITTS 
%  p: Matriz de entradas (vectores fila)
%  t: Vector Columna de Salida deseado
%  a: Vector Columna de salida del modelo
%  dwf: vcetor de pesos

[m n]=size(p);
dw=zeros(m+1,n); 
a=zeros(m,1); e=zeros(m,1);
dw(1,:)=0.5*(ones(1,2)); % Factor no debe superar a 2
for j=1:epochs
    for i=1:m
        dw(i,:)=floor((dw(i,:)));
        a(i,1)=(dw(i,:)*p(i,:)')>=2; % Tabla de verdad, OR
        e(i,1)=t(i)-a(i,1);
        dw(i+1,:)=dw(i,:)+e(i)*p(i,:);
    end
    dw(1,:)=dw(m+1,:); pp=[p,t]; 
    pp=pp(randperm(m),:);
    t=pp(:,n+1);  p=pp(:,1:n);
end
dwf=dw(m+1,:); 