maxNum=zeros(1000,1);
n=1:length(maxNum);
n=n';
productoria=zeros(1000,1);

for m = 1:1000
    prod=1.0;
    i=0;
    x=rand();
    while (prod*x)>=exp(-3)
        i=i+1;
        prod=prod*x;
        x=rand();
    end
    productoria(m)=prod;
    maxNum(m)=i;
end

E_N=cumsum(maxNum)./n;
P_0=cumsum(maxNum==0)./n;
P_1=cumsum(maxNum==1)./n;
P_2=cumsum(maxNum==2)./n;
P_3=cumsum(maxNum==3)./n;
P_4=cumsum(maxNum==4)./n;
P_5=cumsum(maxNum==5)./n;
P_6=cumsum(maxNum==6)./n;
disp('-----------------------');
disp('4.1 Determinar E[N]:');
fprintf('E[N]= %f \n',E_N(length(E_N)));
plot(n,E_N);
disp('-----------------------');
disp('4.2 Determinar P[N] para i = 0,1, ..., 6:');
fprintf('P[0]= %f \n',P_0(length(P_0)));
plot(n,P_0);
fprintf('P[1]= %f \n',P_1(length(P_1)));
plot(n,P_1);
fprintf('P[2]= %f \n',P_2(length(P_2)));
plot(n,P_2);
fprintf('P[3]= %f \n',P_3(length(P_3)));
plot(n,P_3);
fprintf('P[4]= %f \n',P_4(length(P_4)));
plot(n,P_4);
fprintf('P[5]= %f \n',P_5(length(P_5)));
plot(n,P_5);
fprintf('P[6]= %f \n',P_6(length(P_6)));
plot(n,P_6);
disp('-----------------------');
