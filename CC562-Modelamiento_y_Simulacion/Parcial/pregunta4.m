clc
clear
fprintf('##########################################\n');
fprintf('             Pregunta 4\n');
numvar=1000;

% simulando con nbinrnd()
varbinor=zeros(numvar,1); % vector de variables usando nbinrnd
p=0.2;  %constantes fijos para el test
r=1;    %constantes fijos para el test
for m = 1:numvar
  varbinor(m)=nbinrnd(r,p);
end
E2=sum(varbinor)/numvar;
fprintf('\nUsando Octave pra la simulacion:\n');
fprintf('E[X]= %d \n',E2);

% simulando con el algoritmo
varalgorithm=zeros(numvar,1);
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
  varalgorithm(m)=K+r-1; %numero de numvar necesarios para obtener r exitos
end
E=sum(varalgorithm)/numvar;
fprintf('\nUsando el algoritmo descrito pra la simulacion:\n');
fprintf('E[X]= %d \n',E);

% simulando con la recursiva
fprintf('\nComprobando p(j) recursivo: ');
varrecur=zeros(numvar,1);
pp=p;
for m=1:numvar
  i=r;
  U=rand();
  p=pp^r;
  F=p;
  while(U > F)
    p=(i*(1-pp))*p/(i+1-r);%recursivo
    F=F+p;
    i=i+1;
    U=rand();
  end
  X=i;
  varrecur(m)=X+1;
end

E3=sum(varrecur)/numvar;
fprintf('\nUsando Recursividad para la simulacion:\n');
fprintf('E[X]= %d \n\n',E3);
fprintf('##########################################\n');

