NUMERIC=xlsread('esclerosis.xlsx');
random1=randperm(69);
random1=random1(1:20);
random2=randperm(29)+69;
random2=random2(1:8);
p=NUMERIC(cat(2,random1,random2),1:5);


winput=[0 0 0 0 0 0]; 
binput=[1];
t=NUMERIC(cat(2,random1,random2),6) >0;

n=28;
t=double(t);

dw=zeros(n,5); db=zeros(n,5);
a=zeros(n,5); e=zeros(n,5);

    for i=2:29
        a(i-1,1)=dw(i-1,:)*p(i-1,:)'+db(i-1,1)>0;
        e(i-1,1)=t(i-1)-a(i-1,1);
        dw(i,:)=dw(i-1,:)+e(i-1,1)*p(i-1,:);
        db(i,1)=db(i-1,1)+e(i-1,1);
    end
