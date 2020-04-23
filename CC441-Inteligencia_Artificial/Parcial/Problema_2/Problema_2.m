disp("Problema 2, Perceptron Multicapa");
disp('Clasificacion en mu_1 = [1 2] mu_2 = [10 3]');
disp('Se obtiene un Minimal Square Error (MSE) de:');
Clasificacion_Normal_Bivariado([1 2], [10 3]);

disp('Clasificacion en mu_1 = [1 2] mu_2 = [1 3]');
disp('Se obtiene un Minimal Square Error (MSE) de:');
Clasificacion_Normal_Bivariado([1 2], [1 3])	

disp('Clasificacion en mu_1 = [1 2] mu_2 = [0 1.5]');
disp('Se obtiene un Minimal Square Error (MSE) de:');
Clasificacion_Normal_Bivariado([1 2], [0 1.5]);
