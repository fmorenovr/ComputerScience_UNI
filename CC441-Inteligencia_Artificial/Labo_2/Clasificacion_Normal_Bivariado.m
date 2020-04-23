function Clasificacion_Normal_Bivariado(epochs,nu)
  clc
  %epochs = 10; nu = 0.012;
  mu_1 = [1 2]; mu_2 = [10 3];n=10;
  Sigma = [1 .5; .5 2]; R = chol(Sigma);
  z_1 = repmat(mu_1,n,1) + randn(n,2)*R; [mz_1 n_z1]=size(z_1);
  z_2 = repmat(mu_2,n,1) + randn(n,2)*R; [mz_2 n_z2]=size(z_2);
  plot(z_1,z_2,'o');
  %%%%%%%%%%% Learning del Perceptron %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  p_fit = [z_1(1:n-3,:);z_2(1:n-3,:)]; t = [ones(n-3,1);zeros(n-3,1)]; 
  [m_p_fit n_p_fit]=size(p_fit);
  [dwf, dbf] = Perceptron(p_fit,t,nu,epochs);
  p_fitting=p_fit*dwf'+ones(m_p_fit,1)*dbf>0; % Valores Clasificados de los (n-3) datos de entrada
  %%%%%%%%%% Generalized del Perceptron %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  p_gen=[z_1(n-2:n,:);z_2(n-2:n,:)];[m_gen n_gen]=size(p_gen);
  p_generalized=p_gen*dwf'+ones(m_gen,1)*dbf>0; % Valores Clasificados de los 2*(n-(n-3)) datos no utilizados
  real = [ones(n-(n-3),1);zeros(n-(n-3),1)];      % Valores REALES de los 2*(n-(n-3)) datos no utilizados
  %disp([p_generalized real]);
  disp([epochs  nu  sum(Mse(p_generalized,real))]);
endfunction