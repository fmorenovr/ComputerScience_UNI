y=rand(1000,1);
n=1:length(y);
n=n';
int_aprox=4*(cumsum(exp(2)*(1./exp(12*y)).*exp(16.*y.^(2))))./n;
plot(n,int_aprox);
int_aprox(length(y))
