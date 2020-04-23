function [t,x,y] =rungeKutta_SEDO1(f,g,a,b,x0,y0,n)
      h=(b-a)/n;
      t=a:h:b;
      x=zeros(1,n+1); %reserva memoria para n+1 element(i)os del vect(i)or x(i)
      y=zeros(1,n+1);
      x(1)=x0; y(1)=y0;
      
      for i=1:n
        k1=h*f(t(i),x(i),y(i));
        l1=h*g(t(i),x(i),y(i));
        k2=h*f(t(i)+h/2,x(i)+k1/2,y(i)+l1/2);
        l2=h*g(t(i)+h/2,x(i)+k1/2,y(i)+l1/2);
        k3=h*f(t(i)+h/2,x(i)+k2/2,y(i)+l2/2);
        l3=h*g(t(i)+h/2,x(i)+k2/2,y(i)+l2/2);
        k4=h*f(t(i)+h,x(i)+k3,y(i)+l3);
        l4=h*g(t(i)+h,x(i)+k3,y(i)+l3);

        
        x(i+1)=x(i)+(k1+2*k2+2*k3+k4)/6;
        y(i+1)=y(i)+(l1+2*l2+2*l3+l4)/6;        
      endfor
endfunction

% f = @(t,y1,y2)  t*y1*y2;
% g = @(t,y1,y2)  3*y1 - 2*y2;
% [t,x,y]=rungeKutta_SEDO1(f,g,3,3.04,-1.312258,-0.414524,1)
