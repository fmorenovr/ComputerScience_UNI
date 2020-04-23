#!/usr/bin/octave -qf

%function [u0y]=f3(y)
%  u0y = y+3;
%endfunction

function [u0y] = f3(y)
  n=length(y);
  if n>1
    str = [];
    for i=1:n
      str=[str,y(i)+3];
    endfor
    u0y = str;
  else
    u0y = y+3;
  endif
end
