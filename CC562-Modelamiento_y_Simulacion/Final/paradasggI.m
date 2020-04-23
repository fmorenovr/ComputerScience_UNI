function [paradasg2I,ICI,ICS]=paradasggI(T,l,Z)

%% T: Intervalo de tiempo despues del cual no se permite que otros clientes entren al sistema
%% N: Numero de iteraciones
%Z:variable aleatoria normal unitaria que al 95% de confianza es 1.96
%l:longitud aceptable del intervalo.

    for i=1:30
       Tp=SLSeries_1(T);
        Tp_(i,1)=Tp;
    end
    Tp_;%Vector con los 30datos iniciales de Tiempos del ultimo cliente en el sistema
    mediaTp=mean(Tp_);
    varianzaTp=var(Tp_);
    
k=30;j=1;
F=[];
while (2*Z*sqrt(varianzaTp/k))>l
    adicional=SLSeries_1(T);
    T_P(j,1)=adicional;
    u=mediaTp;
    mediaTp=mediaTp+(adicional-mediaTp)/(k+1);
    varianzaTp=(1-1/k)*varianzaTp+(k+1)*((mediaTp-u)^2);
    k=k+1;
j=j+1;
end
paradasg2I=k;
mediaTp %media del vector F
ICI=mediaTp-Z*(sqrt(varianzaTp/k));
ICS=mediaTp+Z*(sqrt(varianzaTp/k));
T_P;%Vector de los valores adicionales 
F=[Tp_;T_P];%Vector con 30 valores y los adicionales en total k elementos
varianzaTp;%varianza del vector F