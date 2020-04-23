function [X] = pregunta3TI(k,num=100)
  clc;
  x=1:k;
  X = zeros(1,k);
  p=sort(rand(1,num));
  for j=1:k
    U = rand();
    if (U < p(1))
        X(1,j) = x(1);
    elseif (U>sum(p(1:num-1)))
      X(1,k) = x(num);
    else
      for i=1:num-1
        if (U < sum(p(1:i+1)))
          X(1,j) = x(i);
          break;
        end
      end
    end
end
