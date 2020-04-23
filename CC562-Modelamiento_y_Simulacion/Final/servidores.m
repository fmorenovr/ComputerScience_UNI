cont = 100;
data = zeros(cont,1); % tiempo de servicio promedio
%np1_ = [];            % numero de peticiones atendidas por servicio 1
%np2_ = [];            % numero de peticiones atendidas por servicio 2
%np3_ = [];            % numero de peticiones atendidas por servicio 3
%npprom1_ = [];        % porcentaje de peticiones atendidas por servicio 1
%npprom2_ = [];        % porcentaje de peticiones atendidas por servicio 2
%npprom3_ = [];        % porcentaje de peticiones atendidas por servicio 3

for i=1:cont
  [data(i),np,npprom] = SLSeries_3(10);
  %np1_ = [np1_ np(1)];
  %np2_ = [np2_ np(2)];
  %np3_ = [np3_ np(3)];
  %npprom1_ = [npprom1_ npprom(1)];
  %npprom2_ = [npprom2_ npprom(2)];
  %npprom3_ = [npprom3_ npprom(3)];
end
promedio = mean(data);
display('Tiempo Promedio:');
display(promedio);

%display('Numero promedio de peticiones para servidor 1:');
%display(mean(np1_));
%display('Numero promedio de peticiones para servidor 2:');
%display(mean(np2_));
%display('Numero promedio de peticiones para servidor 3:');
%display(mean(np3_));

%display('Proporcion promedio de peticiones para servidor 1:');
%display(mean(npprom1_));
%display('Proporcion promedio de peticiones para servidor 2:');
%display(mean(npprom2_));
%display('Proporcion promedio de peticiones para servidor 3:');
%display(mean(npprom3_));

figure(1);
subplot(2,1,1)
plot(1:cont,data);
title('Tiempo promedio de atencion de servicios');
subplot(2,1,2)
hist(data);
title('Atención de servicios');

%figure(2);
%subplot(3,3,1);
%plot(1:cont,np1_);
%title('Numero de peticiones en servicio 1');
%subplot(3,3,2);
%hist(np1_);
%title('Numero de peticiones en servicio 1');
%subplot(3,3,3);
%plot(1:cont,npprom1_);
%title('Proporcion de peticiones en servicio 1');
%subplot(3,3,4)
%plot(1:cont,np2_);
%title('Numero de peticiones en servicio 2');
%subplot(3,3,5);
%hist(np2_);
%title('Numero de peticiones en servicio 2');
%subplot(3,3,6);
%plot(1:cont,npprom2_);
%title('Proporcion de peticiones en servicio 2');
%subplot(3,3,7);
%plot(1:cont,np3_);
%title('Numero de peticiones en servicio 3');
%subplot(3,3,8);
%hist(np3_);
%title('Numero de peticiones en servicio 3');
%subplot(3,3,9);
%plot(1:cont,npprom3_);
%title('Proporcion de peticiones en servicio 3');

