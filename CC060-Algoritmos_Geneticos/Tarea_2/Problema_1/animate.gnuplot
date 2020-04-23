do for [i=0:n-1] {
  splot ''.i.'.txt' w p lt 1,(1 - sin(sqrt(x*x+y*y))*sin(sqrt(x*x+y*y)))/(1 + 0.001*(x*x+y*y))  w l lt 4 lw 0.15 title sprintf("Generacion: %i",i)
}
