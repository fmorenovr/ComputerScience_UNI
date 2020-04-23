load Data_TSReg6

betaHat0 = M0.Coefficients.Estimate;
yHat0 = [1,X2005]*betaHat0;

D = dates(end);
Xm = min([X0(:);X2005']);
XM = max([X0(:);X2005']);

figure
hold on
plot(dates,X0,'LineWidth',2)
plot(D:D+1,[X0(end,:);X2005],'*-.','LineWidth',2)
fill([D D D+1 D+1],[Xm XM XM Xm],'b','FaceAlpha',0.1)
hold off
legend(predNames0,'Location','NW')
xlabel('Año')
ylabel('Prediccion de nivel')
title('{\bf Nueva data de Prediccion}')
axis tight
grid on

Ym = min([y0;yHat0]);
YM = max([y0;yHat0]);

figure
hold on
plot(dates,y0,'k','LineWidth',2);
plot(D:D+1,[y0(end);yHat0],'*-.k','LineWidth',2)
fill([D D D+1 D+1],[Ym YM YM Ym],'b','FaceAlpha',0.1)
hold off
legend(respName0,'Location','NW')
xlabel('año')
ylabel('nivel de respuesta')
title('{\bf Forecast}')
axis tight
grid on
