clc
clear
winput=[-1 1]; binput=[1];

pinput=randn(101,2); 
tinput=winput*pinput'+binput >0;
p=pinput; t=tinput;
dw=zeros(80,2); db=zeros(80,1);
a=zeros(80,1); e=zeros(80,1);
    
for j=1:100
    for i=2:80
        a(i-1,1)=dw(i-1,:)*p(i-1,:)'+db(i-1,1)>0;
        e(i-1,1)=t(i-1)-a(i-1,1);
        dw(i,:)=dw(i-1,:)+e(i-1,1)*p(i-1,:);
        db(i,1)=db(i-1,1)+e(i-1,1);
    end
    dw(1,:)=dw(80,:);
    db(1,1)=db(80,1);
    
    a=randperm(81);
    for i=1:81
        p(i,:)=p(a(i),:);
        t(i)=t(a(i));
    end   
    
end

aa=zeros(20,1);
for i=81:100
    aa(20-(100-i),1)=dw(80,:)*p(i,:)'+db(80,1)>0;
end

t(81:100)
aa





