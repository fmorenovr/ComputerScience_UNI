#!/usr/bin/octave -qf

%function [uxb]=f2(x)
%  uxb = 3*x;
%endfunction

function [uxb] = f2(x)
  n=length(x);
  if n>1
    str = [];
    for i=1:n
      str=[str,3*x(i)];
    endfor
    uxb = str;
  else
    uxb = 3*x;
  endif
end
