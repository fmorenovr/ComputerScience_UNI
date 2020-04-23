function [Cuot,Tipo]= CalcCuota(n)
  if n<=4830000 and n>=4410000
    Cuot = 1165978;
    Tipo = .3886;
  elseif n>4830000 and n<=5250000
    Cout = 1329190;
    Tipo = .4102;
  elseif n>5250000 and n<=5670000
    Cout = 1501474;
    Tipo = .4318;
  else
    Cout = 1682830;
  end
end
