function [I, S] = pregunta_2(T)
% Generación de la primeras T unidades de tiempo de N* (intensidad 
% (lambda(t) )
%             lambda : tasa del proceso N
%                  t : tiempo
%                  I : número de eventos contados que ocurren 
%                      hasta el instante T
% S(1), S(2),...,S(I): I tiempos de evento contado en orden creciente
 
%lambda_t=inline('3+(4/(t+1))'); 
lambda=30;                      % lambda_t <= lambda
t=0; I=0; S=zeros(1);
while (t<T)
    t=t-(1/lambda)*log(rand());
    if(t<5)
      lambda_t = inline('t/5');
    else
      lambda_t = inline('1+5*(t-5)');
end
    u=rand(); 
    if (u<=(lambda_t(t)/lambda))
       I=I+1;
       S=[S t];
    end
end
S=S(2:I-1);I=I-1;