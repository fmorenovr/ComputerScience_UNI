function paradasg2=paradasgg2(T,d)
%% D_A_medio:Tiempo medio que pasa un cliente en el sistema
%% T: Intervalo de tiempo despues del cual no se permite que otros clientes entren al sistema
%% N: Numero de iteraciones
%d:valor aceptable para la desviacion estandar del estimador
for i=1:30
       Tp=SLSeries_1(T);
        Tp_(i,1)=Tp;
    
    end
    Tp_;%Vector con los 30datos iniciales
    mediaTp=mean(Tp_);
    varianzaTp=var(Tp_);
    
k=30;j=1;
F=[];
while (sqrt(varianzaTp/k))>d
    adicional=SLSeries_1(T);
    T_P(j,1)=adicional;
    u=mediaTp;
    mediaTp=mediaTp+(adicional-mediaTp)/(k+1);
    varianzaTp=(1-1/k)*varianzaTp+(k+1)*((mediaTp-u)^2);
    k=k+1;
j=j+1;
end
paradasg2=k;
mediaTp; %media del vector F.Tiempo medio en que el ultimo cliente sale del sistema
T_P;%Vector de los valores adicionales 
F=[Tp_;T_P];%Vector con 30 valores y los adicionales en total k elementos
varianzaTp;%varianza del vector F