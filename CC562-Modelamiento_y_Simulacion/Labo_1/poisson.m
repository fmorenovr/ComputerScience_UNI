function x=poisson(u,lambda)
  i=0; p=exp(-lambda);F=p;
  while u >= F
    p=((lambda*p)/(i+1));
    F=F+p;
    i=i+1;
  end
  x=i;
end
