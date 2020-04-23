function [weight_hidden_output, weight_input_hidden,sigma_out,mu_out] = Perceptron_Multicapa(p,t,epochs)

	%user specified values
	hidden_neurons = 5;
	train_inp=p;
	train_out=t;


	% check same number of patterns in each
	if size(train_inp,1) ~= size(train_out,1)
		  disp('ERROR: data mismatch')
		 return 
	end    

	%standardise the data to mean=0 and standard deviation=1
	%inputs
	mu_inp = mean(train_inp);
	sigma_inp = std(train_inp);
	for i=1:2
		train_inp(:,i) = (train_inp(:,i) - mu_inp(1,i)) / sigma_inp(1,i);
	end
	%outputs
	train_out = train_out';
	mu_out = mean(train_out);
	sigma_out = std(train_out);
	train_out = (train_out(:,:) - mu_out(:,1)) / sigma_out(:,1);
	train_out = train_out';

	%read how many patterns
	patterns = size(train_inp,1);

	%add a bias as an input
	bias = ones(patterns,1);
	train_inp = [train_inp bias];

	%read how many inputs
	inputs = size(train_inp,2);

	%---------- data loaded ------------


	%--------- add some control buttons ---------

	%add button for early stopping
	hstop = uicontrol('Style','PushButton','String','Stop', 'Position', [5 5 70 20],'callback','earlystop = 1;'); 
	earlystop = 0;

	%add button for resetting weights
	hreset = uicontrol('Style','PushButton','String','Reset Wts', 'Position', get(hstop,'position')+[75 0 0 0],'callback','reset = 1;'); 
	reset = 0;

	%add slider to adjust the learning rate
	hlr = uicontrol('Style','slider','value',.1,'Min',.01,'Max',1,'SliderStep',[0.01 0.1],'Position', get(hreset,'position')+[75 0 100 0]);


	% ---------- set weights -----------------
	%set initial random weights
	weight_input_hidden = (randn(inputs,hidden_neurons) - 0.5)/10;
	weight_hidden_output = (randn(1,hidden_neurons) - 0.5)/10;



	%-----------------------------------
	%--- Learning Starts Here! ---------
	%-----------------------------------

	%do a number of epochs
	for iter = 1:epochs
		  
		  %get the learning rate from the slider
		  alr = get(hlr,'value');
		  blr = alr / 10;
		  
		  %loop through the patterns, selecting randomly
		  for j = 1:patterns
		      
		      %select a random pattern
		      patnum = round((rand * patterns) + 0.5);
		      if patnum > patterns
		          patnum = patterns;
		      elseif patnum < 1
		          patnum = 1;    
		      end
		     
		      %set the current pattern
		      this_pat = train_inp(j,:);
		      act = train_out(j,1);
		      
		      %calculate the current error for this pattern
		      hval = (tanh(this_pat*weight_input_hidden))';
		      pred = hval'*weight_hidden_output';
		      error = pred - act;

		      % adjust weight hidden - output
		      delta_HO = error.*blr .*hval;
		      weight_hidden_output = weight_hidden_output - delta_HO';

		      % adjust the weights input - hidden
		      delta_IH= alr.*error.*weight_hidden_output'.*(1-(hval.^2))*this_pat;
		      weight_input_hidden = weight_input_hidden - delta_IH';
		      
		  end
		  % -- another epoch finished
		  
		  %plot overall network error at end of each epoch
		  pred = weight_hidden_output*tanh(train_inp*weight_input_hidden)';
		  error = pred' - train_out;
		  err(iter) =  (sum(error.^2))^0.5;
		  
		  figure(1);
		  plot(err)
		  
		  
		  %reset weights if requested
		  if reset
		      weight_input_hidden = (randn(inputs,hidden_neurons) - 0.5)/10;
		      weight_hidden_output = (randn(1,hidden_neurons) - 0.5)/10;
		      fprintf('weights reaset after %d epochs\n',iter);
		      reset = 0;
		  end
		  
		  %stop if requested
		  if earlystop
		      fprintf('stopped at epoch: %d\n',iter); 
		      break 
		  end 

		  %stop if error is small
		  if err(iter) < 0.001
		      fprintf('converged at epoch: %d\n',iter);
		      break 
		  end
		     
	end

end
