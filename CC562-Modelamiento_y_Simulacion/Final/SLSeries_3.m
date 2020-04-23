function [Tp,np,npprom]=SLSeries_1(T)
  %Proceso de llegada con dos servidores en serie
  %L1:razon a la que son atendidos los clientes en el servicio 1
  %L2:razon a la que son atendidos los clientes en el servicio 2
  %L3:razon a la que son atendidos los clientes en el servicio 3
  %lambda tasa de llegada al sistema

  L1=1;
  L2=2;
  L3=3;
  lambda=6; 
  %inicializacion de Variables
  t=0;
  Na=0;%numero de llegadas hasta el instante t
  Nd=0;%numero de salidas hasta el instante t
  n1=0;%numero de personas que se encuentran en el servidor 1
  n2=0;%numero de personas que se encuentran en el servidor 2
  n3=0;%numero de personas que se encuentran en el servidor 3
  np1=0;%numero de servicio realizados por el servidor 1
  np2=0;%numero de servicio realizados por el servidor 2
  np3=0;%numero de servicio realizados por el servidor 3
  ta=tllegada(t,lambda);
  t1=inf;
  t2=inf;
  t3=inf;
  posterior=1;
  A1 = zeros(1000,1);
  D = zeros(1000,1);
  contador = 0;

  while posterior==1
    contador = contador+1;
    if ta==min(ta,min(min(t1,t2),t3)) && ta<T % CASO 1
      t=ta;
      Na=Na+1;
      n1=n1+1;
      np1=np1+1;
      ta=tllegada(t,lambda);
      if (n1==1)
         t1=t+g(L1); %Genera el tiempo de servicio del cliente actual
      end
      A1(Na)=t; %hora de llegada al servidor 1 del n-esimo cliene
      
    elseif t1<ta && t1<=t2 && t1<=t3 && ta<T      %CASO 2
      t=t1;
      n1=n1-1;
      n2=n2+1;
      np2=np2+1;
      n3=n3+1;
      if (n1==0)
         t1=inf;
      else
         t1=t+g(L1);
      end
      if (n2==1)
         t2=t+g(L2);
      end
      if (n3==1)
         t3=t+g(L3);
      end
      A2(Na-n1)=t;      

    elseif t2<ta && t2<t1 && t2<=t3  && ta<T %CASO 3
      t=t2;
      Nd=Nd+1;
      n2=n2-1;
      n1=n1-1;
      if (n2==0)
         t2=inf;
      end
      if (n2>0)
         t2=t+g(L2);
      end
      A3(Na-n2)=t;
      %D(Nd-n2)=t;

    elseif t3<ta && t3<t1 && t3<t2   %Caso 4
      t=t3;
      Nd=Nd+1;
      n3=n3-1;
      if (n3==0)
       t3=inf;
      end
      if (n3>0)
       t3=t+g(L3);
      end
      D(Nd-n3+1)=t;
      
    elseif ta>T 
      if n1==0 && n2==0 && n3==0
          Tp=max([t-T],0);
      else
        while n1~=0 || n2~=0 || n3~=0
          if t1<=t2 && t1<=t3
              t=t1;
              n1=n1-1;
              n2=n2+1;
              n3=n3+1;
              np3=np3+1;
              if (n1==0)
             t1=inf;
              else
             t1=t+g(L1);
              end
              if (n2==1)
             t2=t+g(L2);
              end
              
              if (n3==1)
             t3=t+g(L3);
              end
              A2(Na-n1)=t;      
          elseif t2<=t3 && t2<=t3
              t=t2;
              Nd=Nd+1;
              n2=n2-1;
              if (n2==0)
                 t2=inf;
              end
              if (n2>0)
                 t2=t+g(L2);
              end
              D(Nd)=t;
              Tp=max([t-T],0);
          else
            t=t3;
              Nd=Nd+1;
              n3=n3-1;
              if (n3==0)
                 t3=inf;
              end
              if (n3>0)
                 t3=t+g(L3);
              end
              D(Nd)=t;
              Tp=max([t-T],0);
          end
        end
      end
      posterior=-posterior;
    end
  end  
  %D_A=mean(D-A1); %Vector de tiempo de servicio
  np = [np1 np2 np3]
  npprom = [np1 np2 np3]/(np1+np2+np3)
end
