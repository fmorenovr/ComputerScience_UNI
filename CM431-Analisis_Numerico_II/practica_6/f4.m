#!/usr/bin/octave -qf

%function [uay]=f4(y)
%  uay = 2*y + 4;
%endfunction

function [uay] = f4(y)
  n=length(y);
  if n>1
    str = [];
    for i=1:n
      str=[str,2*y(i)+4];
    endfor
    uay = str;
  else
    uay = 2*y+4;
  endif
end
