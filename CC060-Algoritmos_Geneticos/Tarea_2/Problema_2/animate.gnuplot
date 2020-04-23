do for [i=0:n-1] {
  splot ''.i.'.txt' w p lt 2,(1 - sin(sqrt(x*x+y*y))*sin(sqrt(x*x+y*y)))/(1 + 0.001*(x*x+y*y))  w l lt 5 lw 0.10 title sprintf("Generacion: %i",i)
}
