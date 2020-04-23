function [X] = pregunta3AR(k, lambda=6,num=100)
  clc;
  X = zeros(1,num);
  for i = 1:num
    u_1=rand();
    x=poisson(u_1,lambda);
    iter=0;
    while x>k
      iter=iter+1;
      x=poisson(u_1,lambda);
    end
    X(1,i)=x;
  end
end
