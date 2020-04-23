clc
clear all
esclerosis=xlsread('esclerosis.xlsx');
d = [esclerosis(1:20,:); esclerosis(70:77,:)];
[m n]=size(d); 
for i=1:m
    d(i,1:5)=d(i,1:5)/norm(d(i,1:5));
end
t=d(:,6);p=d(:,1:5);
epochs=500;





