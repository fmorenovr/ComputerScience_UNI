%---------------------------------------------------------
% MATLAB neural network backprop code
% by Phil Brierley
% www.philbrierley.com
% 29 March 2006
%
% This code implements the basic backpropagation of
% error learning algorithm. The network has tanh hidden  
% neurons and a linear output neuron.
%
% adjust the learning rate with the slider
%
% feel free to improve!
%
%--------------------------------------------------------



%user specified values
hidden_neurons = 5;
epochs = 10000;
p=csvread('esclerosis.csv');
negativo=randperm(69);
positivo=randperm(29)+69;
train_inp=[p(negativo(1:20),1:5);p(positivo(1:8),1:5) ];
train_out=[p(negativo(1:20),6);p(positivo(1:8),6) ];
%train_inp=[p(negativo(1:69),1:5);p(positivo(1:29),1:5) ];
%train_out=[p(negativo(1:69),6);p(positivo(1:29),6) ];

% ------- load in the data -------


% check same number of patterns in each
if size(train_inp,1) ~= size(train_out,1)
    disp('ERROR: data mismatch')
   return 
end    

%standardise the data to mean=0 and standard deviation=1
%inputs
mu_inp = mean(train_inp);
sigma_inp = std(train_inp);
for i=1:5
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

   %-----FINISHED--------- 
   %display actual,predicted & error
   fprintf('state after %d epochs\n',iter);
   a = (train_out* sigma_out(:,1)) + mu_out(:,1);
   b = (pred'* sigma_out(:,1)) + mu_out(:,1);
   fprintf('Datos analizados\n',iter);
   act_pred_err = [a b b-a]
   
   %-----------ANALIZANDO-----------
   %valores que no entraron al analisis
   entradas=[p(negativo(21:69),1:5);p(positivo(9:29),1:5) ];
   salidas=[p(negativo(21:69),6);p(positivo(9:29),6) ];
   %inputs
   mu_inp = mean(entradas);
   sigma_inp = std(entradas);
	 for i=1:5
			entradas(:,i) = (entradas(:,i) - mu_inp(1,i)) / sigma_inp(1,i);
	 end

   mu_out=mean(salidas);
	 sigma_out=std(salidas);
   patterns = size(entradas,1);

   %add a bias as an input
   bias = ones(patterns,1);
   entradas = [entradas bias];

   
   pred = weight_hidden_output*tanh(entradas*weight_input_hidden)';
   pred = (pred'* sigma_out(:,1)) + mu_out(:,1);
   
   %-----FINISHED--------- 
   %mostrar valores no analizados y error
   
   fprintf('Prediccion de datos no analizados\n');
   pred_err = [salidas pred pred-salidas]
   error=pred-salidas;
   mse =  (sum(error.^2))^0.5;
   fprintf('El error es %f\n',mse);
   
