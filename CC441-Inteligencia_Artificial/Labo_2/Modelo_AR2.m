function Modelo_AR2(epochs,nu)
  clc
  %%%%%%%%%%% Simulacion de un Modelo AR(2)%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  phi_1 = 0.5;phi_2 = 0.5; n=102;
  p=zeros(n,1);
  for i=3:n
      p(i,1) = phi_1*p(i-1,1) + phi_2 * p(i-2,1) + randn();
  end
  %%%%%%%%%% Filtro Adadptativo Lineal %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  %-------Aprendizaje utilizando de los primeros (n-10) valores------------
  subplot(2,1,1);
  plot(p(3:n-10,1),'b');   % Grafico de los (n-10) datos de entrada
  hold on
  p_fit = [p(3:n-10,1),p(4:n-9,1)]; t = p(5:n-8,1);
  %>> 1./(eig(p_fit'*p_fit))
  % ans =
  %
  %     0.0214
  %     0.0011
  % nu debe ser menor que el reciproco del mayor autovalor de (p_fit'*p_fit)
  %epochs = 10; nu = 0.010; 
  [m_p_fit n_p_fit]=size(p_fit);
  [dwf, dbf] = Filtro_Adaptativo_Lineal(p_fit,t,nu,epochs);
  p_fitting=p_fit*dwf'+ones(m_p_fit,1)*dbf; % Valores estimados de los (n-10) datos de entrada
  plot(p_fitting,'r')    
  hold off
  %--------Pronostico de los ultimos 10 valores-----------------------------
  subplot(2,1,2);
  plot(p(n-7:n,1),'m--');
  hold on
  p_new = [p(n-9:n-2,1),p(n-8:n-1,1)]; [m_p_new n_p_new]=size(p_new); 
  p_forecasting=zeros(((n-2)-(n-9)+1),1);
  for i=1:((n-2)-(n-9)+1)
      if i==1
           p_forecasting(1,1) = dwf(1)*p(n-8,1) + dwf(2) * p(n-9,1) + dbf;
      elseif i==2
           p_forecasting(2,1) = dwf(2)*p(n-8,1) + dwf(1) * p_forecasting(1,1) + dbf;    
      else
           p_forecasting(i,1) = dwf(2)*p_forecasting(1,1) + dwf(1) * p_forecasting(2,1) + dbf;
      end
  end
  plot(p_forecasting,'g--')
  hold off
  disp([epochs  nu  sum(Mse(p_fitting,p_fit))]);
endfunction