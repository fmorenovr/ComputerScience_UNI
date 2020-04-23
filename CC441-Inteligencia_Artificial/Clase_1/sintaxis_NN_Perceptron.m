

pinput=randn(101,2); 
winput=[-1 1]; binput=[1];
tinput=winput*pinput'+binput >0;
p=pinput; t=tinput;t=double(t);

dw=zeros(100,2); db=zeros(100,1);
a=zeros(100,1); e=zeros(100,1);
%net = newp([-2 2;-2 2],[0 1]);
%net = newp(p(2:101,:)',t(2:101)');

for i=2:100
    %a(i,1)=sim(net,p(i,:)');
    %a(i,1)=hardlim(dw(i,:)*p(i,:)'+db(i,1));
    a(i-1,1)=dw(i-1,:)*p(i-1,:)'+db(i-1,1)>0;
    e(i-1,1)=t(i-1)-a(i-1,1);
    dw(i,:)=dw(i-1,:)+e(i-1,1)*p(i-1,:);
    db(i,1)=db(i-1,1)+e(i-1,1);
end    


