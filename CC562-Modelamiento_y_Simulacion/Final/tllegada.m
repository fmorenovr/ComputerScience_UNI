function t=tllegada(s,lamda) % proceso de llegada de poisson no homogeneo
hora=5;
t=s;
t=t-log(rand)/lamda;
u1=rand;
while u1>vlamda(t,hora)/lamda
    t=t-log(rand)/lamda;
    u1=rand;
end
