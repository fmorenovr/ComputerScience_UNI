#!/usr/bin/octave -qf

%   METODO DE CUADRATURA ADAPTATIVA

%   usa metodos de simpson y trapecio para reducir errores.
%   donde se da por parametro numero de intervalos de simpson(nivel), que son el refinamiento

% -----------------------------------------------
function [INTf,nodes,err] = adaptativeSimpson(fx,a,b,INTf,tol)
  f=fx;
  %adaptive recursive Simpson method
  c = (a+b)/2;
  INTf1 = simpson1_3Rule(f,a,c,100);
  INTf2 = simpson1_3Rule(f,c,b,100);
  INTf12 = INTf1 + INTf2;
  err = abs(INTf12 - INTf)/15; % Error estimate by Eq.(5.5.13)
  if isnan(err) | err < tol | tol<eps % NaN? Satisfying error? Too deep level?
    INTf = INTf12;
    points = [a c b];
  else
    [INTf1,nodes1,err1] = adaptativeSimpson(f,a,c,INTf1,tol/2);
    [INTf2,nodes2,err2] = adaptativeSimpson(f,c,b,INTf2,tol/2);
    INTf = INTf1 + INTf2;
    nodes = [nodes1 nodes2(2:length(nodes2))];
    err = err1 + err2;
  endif
endfunction

% --------------------------------------------------
function [INTf] = adaptativeQuadrature(fx,a,b,tol)
  f=fx;
  %apply adaptive recursive Simpson method
  INTf = simpson1_3Rule(f,a,b,100);
  [INTf,nodes,err] = adaptativeSimpson(f,a,b,INTf,tol);
  fprintf("El error es %5.18f\n",err);
  fprintf("El numero de nodos\n",nodes);
endfunction

% ---------------------------------------------------
