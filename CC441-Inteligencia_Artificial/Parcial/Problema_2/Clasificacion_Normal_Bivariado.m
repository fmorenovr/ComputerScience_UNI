function  Clasificacion_Normal_Bivariado(mu_1,mu_2)
	n=100;
	Sigma = [1 .5; .5 2]; 
	R = chol(Sigma);
	z_1 = repmat(mu_1,n,1) + randn(n,2)*R;
	[mz_1 n_z1]=size(z_1);
	z_2 = repmat(mu_2,n,1) + randn(n,2)*R;
	[mz_2 n_z2]=size(z_2);
  figure;
	plot(z_1,z_2,'o');
	%%%%%%%%%%% Learning del Perceptron %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	%Genero datos de analisis
	p_fit = [z_1(1:80,:);z_2(1:80,:)];
	t = [ones(80,1); zeros(80,1)];
	%lambda=1/(eig(p_fit'*p_fit))
	%p_no_usado=[z_1(n-2:n,:);z_2(n-2:n,:)]; t_no_usado=[ones(2,1);zeros(2,1)];
	epochs = 50; 
	[m_p_fit n_p_fit]=size(p_fit);
	[weight_hidden_output,weight_input_hidden,sigma_out,mu_out] = Perceptron_Multicapa(p_fit,t,epochs);
	
	
  %add a bias as an input
  p_fit = [z_1(81:100,:) ; z_2(81:100,:)];
  mu_inp = mean(p_fit);
  sigma_inp = std(p_fit);
	for i=1:2
		p_fit(:,i) = (p_fit(:,i) - mu_inp(1,i)) / sigma_inp(1,i);
	end
  
  bias = ones(40,1);
  p_fit=[p_fit bias];
  pred = weight_hidden_output*tanh(p_fit*weight_input_hidden)';
  pred = (pred'* sigma_out(:,1)) + mu_out(:,1);
	real=[ones(20,1) ; zeros(20,1)];
	%%%%%%%%%% Generalized del Perceptron %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	error=pred-real;
	mse=error'*error
	%hold off
end
