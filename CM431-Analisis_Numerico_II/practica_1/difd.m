#!/usr/bin/octave -qf

function [y,p] = difd(y,x,t)
  n=length(x);
  for j=2:n
    for k=n:-1:j
      y(k)=(y(k)-y(k-1))/(x(k)-x(k-j+1));
    end
  end
  b=zeros(size(y));
  m=length(t);
  for j=1:m
    b(n)=y(n);
    for k=n-1:-1:1
      b(k)=y(k)+(t(j)-x(k))*b(k+1);
    end
    p(j)=b(1);
  end
end
