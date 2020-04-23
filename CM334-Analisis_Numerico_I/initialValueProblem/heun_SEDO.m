function [t,x,y] =heun_SEDO1(f,g,a,b,x0,y0,n)
      h=(b-a)/n;
      t=a:h:b;
      x=zeros(1,n+1); %reserva memoria para n+1 element(i)os del vect(i)or x(i)
      y=zeros(1,n+1);
      x(1)=x0; y(1)=y0;
      
      for i=1:n
        k1=h*f(t(i),x(i),y(i));
        l1=h*g(t(i),x(i),y(i));
        k2=h*f(t(i+1),x(i)+k1,y(i)+l1);
        l2=h*g(t(i+1),x(i)+k1,y(i)+l1);
        
        x(i+1)=x(i)+(k1+k2)/2;
        y(i+1)=y(i)+(l1+l2)/2;        
      endfor
endfunction
