#!/usr/bin/Rscript
library(nnet);
attach(rock);
area1 <- area/10000; 
peri1 <- peri/10000;
rock1 <- data.frame(perm, area=area1, peri=peri1, shape);
rock.nn <- nnet(log(perm)~area+peri+shape, rock1, size=3, decay=1e-3, linout=T, skip=T, maxit=1000, Hess=T);
summary(rock.nn);
