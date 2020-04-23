function [dwf, dbf] = Filtro_Adaptativo_Lineal(p,t,nu,epochs)
  %  FILTRO ADAPTATIVO LINEAL
  %  p: Matriz de entradas (vectores fila)
  %  t: Vector Columna de Salida
  %  dwf, dbf: vcetor de pesos, sesgo
  [m n]=size(p);
  dw=zeros(m,n); db=zeros(m,1);
  a=zeros(m,1); e=zeros(m,1);
  dw(1,:)=0.5*ones(1,n); db(1,1)=0.5*ones(1,1);
  for j=1:epochs
    for i=2:m
      a(i-1,1)=(dw(i-1,:)*p(i-1,:)'+db(i-1,1)); 
      e(i-1,1)=t(i-1)-a(i-1,1);
      dw(i,:)=dw(i-1,:)+nu*e(i-1)*p(i-1,:);
      db(i,1)=db(i-1,1)+nu*e(i-1,1);
    endfor
    dw(1,:)=dw(m,:);
    db(1,1)=db(m,1);
    pp=[p,t]; pp=pp(randperm(m),:);
    t=pp(:,n+1); p=pp(:,1:n);
  endfor
  dwf=dw(m,:); dbf=db(m,1);
endfunction