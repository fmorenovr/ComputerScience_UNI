% parte 1 %
U=rand(1000,1);
n=1:length(U);
n=n';
aprox=((cumsum(U.*sqrt(1-U.*U)))./n)-((cumsum(U))./n).*((cumsum(sqrt(1-U.*U)))./n);
plot(n,aprox);
aprox(length(U))

% parte 2 %
U=rand(1000,1);
n=1:length(U);n=n';
aprox=((cumsum(U.*U.*sqrt(1-U.*U)))./n)-((cumsum(U.*U))./n).*((cumsum(sqrt(1-U.*U)))./n);
plot(n,aprox)
aprox(length(U))
