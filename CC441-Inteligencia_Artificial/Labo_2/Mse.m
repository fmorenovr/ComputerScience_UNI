function [mse] = Mse(nn,real)
  resta = (nn-real);
  len = length(resta);
  mse=zeros(len,1);
  for i=1:len
    mse(i,1)=resta(i)*resta(i);
  endfor
endfunction