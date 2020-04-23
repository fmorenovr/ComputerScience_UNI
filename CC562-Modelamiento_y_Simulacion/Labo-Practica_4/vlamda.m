function ti=vlamda(T,hora) % esta funcion se utiliza para el proceso de llegada no homogeneo de Poisson
if T<5 
    ti=T/5;
else
    ti=1+5*(T-5);
end