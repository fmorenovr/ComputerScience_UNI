cont = 1000;
data = zeros(cont,1);

for i=1:cont
  data(i) = SLSeries_1(6);
end
promedio = mean(data);
display(promedio);
figure(1);
subplot(2,1,1)
plot(1:cont,data)
subplot(2,1,2)
hist(data);
title('Atención de servicios');
