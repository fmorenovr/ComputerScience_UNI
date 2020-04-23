function X = pregunta3AR(r,p,numvar=100)
  clc;
  fprintf('##########################################\n');
  fprintf('             Pregunta 3\n');
  fprintf('             Aceptacion-Rechazo\n');
  % simulando con el algoritmo
  X=zeros(1,numvar);
  for m = 1:numvar
    K=1;
    success=0;
    random=rand();
  %Generamos r veces variables Geometricas Aleatorias(p) para obtener una variable Negativa Binomial(r,p)
  %como la suma de r variables Geometricas Aleatorias(p) independientes. 
    while(success<r)
      if random>p
        K=K+1;             %print=0; %Failure
      else  
        success=success+1; %print=1; %Success
      end
      random=rand();
    end
    X(m)=K+r-1; %numero de numvar necesarios para obtener r exitos
  end
end
