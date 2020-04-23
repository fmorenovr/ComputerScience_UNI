function [I,S] = pregunta_1(T, lambda)
% Generación de la primeras T unidades de tiempo de N (razón lambda)
%               t : tiempo
%               I : número de eventos que ocurren hasta el instante T
% S(1), S(2),...,S(I): I tiempos de evento en orden creciente
 
t=0; I=0;S=zeros(1);
n_pasajeros = 0;
while (t<T)
    t=t-(1/lambda)*log(rand());
    I=I+1;
    n_pasajeros = n_pasajeros + floor(rand()*21)+20;
    S=[S t];
end 
S=S(2:I-1);I=I-1;display(n_pasajeros);