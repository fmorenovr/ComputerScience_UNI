function [X] = pregunta3TI(n,p,num=100)
  clc;
  fprintf('##########################################\n');
  fprintf('             Pregunta 3\n');
  fprintf('             Transformada Inversa\n');
  x=1:num;
  X = zeros(1,num);
  % simulando con nbinrnd()
  varbinor=zeros(num,1);
  for m = 1:num
    x(m)=binornd(n,p);
  end
  prob=sort(rand(1,num));
  for j=1:num
    U = rand();
    if (U < prob(1))
        X(1,j) = x(1);
    elseif (U>sum(prob(1:num-1)))
      X(1,num) = x(num);
    else
      for i=1:num-1
        if (U < sum(prob(1:i+1)))
          X(1,j) = x(i);
          break;
      end
    end
  end
end
