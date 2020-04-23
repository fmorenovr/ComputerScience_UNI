minNum=zeros(1000,1);
n=1:length(minNum);
n=n';
sumatoria=zeros(length(minNum),1);

for m = 1:length(minNum)
    sum=0.0;
    i=0;
    x=rand();
    while (sum+x)<1
        i=i+1;
        sum=sum+x;
        x=rand();
    end
    sumatoria(m)=sum;
    minNum(m)=i;
end

E_N=cumsum(minNum)./n;
disp('-----------------------');
disp('Determinar E[N]:');
fprintf('E[N]= %f \n',E_N(length(E_N)));
plot(n,E_N);
disp('-----------------------');
