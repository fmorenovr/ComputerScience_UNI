#!/usr/bin/octave -qf

function [ux0] = f1(x)
  n=length(x);
  if n>1
    str = [];
    for i=1:n
      str=[str,x(i)*x(i) + 1];
    endfor
    ux0 = str;
  else
    ux0 = x^2 + 1;
  endif
end


%function [ux0]=f1(x)
%  ux0 = x^2 + 1;
%endfunction
