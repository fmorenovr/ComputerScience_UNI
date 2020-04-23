#!/usr/bin/env python
from numpy import *
from random import *
from cmath import *
from auxFuncRoots import *
from hornerRuffini import *

# ------------------------------------------------------------
# 1.6 METODO JENKINS-TRAUB
# probar P = [1,-9.01,27.08,-41.19,32.22,-10.1]
def jenkinsTraub(Q,printText=1,tol=1.e-12,nmaxiter = 100):
  n = len(Q)
  # inicio
  # =========================================================
  powers = [i for i in range(n-1,-1,-1)]
  P = [i for i in Q]
  # Normalizamos
  if P[0]!=1:
    P = [P[i]/(P[0]*1.0) for i in range(n)]
  if n == 2:
    x = (-1)*P[-1]/P[0]
    return x
  # H^0 es P'x0
  H_poly = [powers[i]*P[i] for i in range(n)]
  H_poly = H_poly[:-1]
  # =========================================================
  # stage 1
  # =========================================================
  M = 5 # para polinomios <50
  s = 0
  for i in range(M):
    const = -(evalPoly(H_poly,s)[0])/(evalPoly(P,s)[0])
    Pz_poly = [const*P[i] for i in range(len(P))]
    adjust_h = sumPoly(Pz_poly,H_poly)
    H_poly, _ = ruffini(adjust_h,0)
  print "Stage 1 Complete successfully"
  # =========================================================
  # stage 2
  # =========================================================
  LIMIT = 100
  initial_h_poly = [i for i in H_poly]
  t_curr = t_prev = t_next = None
  stage_two_success = False
  root_found = False
  while not root_found:
    while not stage_two_success:
      H_poly = [i for i in initial_h_poly]
      s = s_initial(P)
      for j in xrange(LIMIT):
        const = -(evalPoly(H_poly,s)[0])/(1.0*evalPoly(P,s)[0])
        Pz_poly = [const*P[i] for i in range(len(P))]
        adjust_h = sumPoly(Pz_poly,H_poly)
        next_h_poly, _ = ruffini(adjust_h,s)
        # calculamos los Ts
        h_bar_poly = [H_poly[i]/(H_poly[0]*1.) for i in range(len(H_poly))]
        next_h_bar_poly = [next_h_poly[i]/(next_h_poly[0]*1.) for i in range(len(next_h_poly))]
        # los actuales
        t_curr = s - evalPoly(P,s)[0]/(1.0*evalPoly(h_bar_poly,s)[0])
        t_next = s - evalPoly(P,s)[0]/(1.0*evalPoly(next_h_bar_poly,s)[0])
        # fin de la prueba
        if j > 0 and abs(t_curr - t_prev) <= 0.5 * abs(t_prev) and abs(t_next - t_curr) <= 0.5 * abs(t_curr):
          stage_two_success = True
          print "Stage 2 Complete successfully"
          break
        t_prev = t_curr
        H_poly[:] = next_h_poly[:]
      if not stage_two_success:
        print "Stage 2 fallo, Reiniciando ..."
    # =========================================================
    # stage 3
    # =========================================================
    num_successive_failures = 0
    prev_err = evalPoly(P,s)[0]
    curr_err = 1
    # el algoritmo converge tan rapido como el de newton
    LIMIT = 10000
    h_bar_poly = [H_poly[i]/(H_poly[0]*1.) for i in range(len(H_poly))]
    s = s - evalPoly(P,s)[0]/(1.0*evalPoly(h_bar_poly,s)[0])
    prev_s = 0
    stage_three_success=False
    for j in range(LIMIT):
      if abs(evalPoly(P,s)[0])<tol:
        stage_three_success = True
        break
      const = -(evalPoly(H_poly,s)[0])/(evalPoly(P,s)[0])
      Pz_poly = [const*P[i] for i in range(len(P))]
      adjust_h = sumPoly(Pz_poly,H_poly)
      next_h_poly, _ = ruffini(adjust_h,s)
      next_h_bar_poly = [next_h_poly[i]/(next_h_poly[0]*1.) for i in range(len(next_h_poly))]
      # actualizamos s
      prev_s = s
      prev_err = evalPoly(P,prev_s)[0]
      s = s - evalPoly(P,s)[0]/(1.0*evalPoly(next_h_bar_poly,s)[0])
      curr_err = evalPoly(P,s)[0]
      if printText:
        print "x0=%s x1=%s Px0=%s Px1=%s"%(prev_s,s,prev_err,curr_err)
      # actualizamos H poly
      H_poly[:] = next_h_poly[:]
      # probamos errores
      if isnan(s.imag) and isnan(s.real):
        stage_three_success=False
        break
    if stage_three_success:
      print "Stage 3 Complete successfully"
      root_found = True
    else: # reinicia desde el paso 2
      stage_two_success = False
      print "Stage 3 fallo, Reiniciando ..."
  return s

# ------------------------------------------------------------
# Crea un valor inicial para evaluar basado en el polinomio de Cauchy
def s_initial(P):
  cauchy_poly = cauchyPol(P)
  err = 1.e-6
  x0 = uniform(0,1)
  beta = hornerRuffini(cauchy_poly,x0,printText=0,tol = err)
  rand = uniform(0,1)*2*pi
  return abs(beta) * exp(1j*rand)

# ------------------------------------------------------------
