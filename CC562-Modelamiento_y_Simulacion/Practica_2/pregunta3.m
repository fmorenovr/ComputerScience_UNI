function  y = pregunta3()
  alpha = 2;
  beta = 3;
 u1 = rand();
 y=-(1/alpha)*log(u1);
 u2=rand();
 c=beta/alpha;
 while (u2>(exp(alpha*y)/beta))
  u1 = rand();
  y=-(1/alpha)*log(u1);
  u2=rand();
 end
end
