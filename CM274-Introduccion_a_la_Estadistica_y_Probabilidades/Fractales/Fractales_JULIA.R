
Fractales de JULIA:



a=-0.7;b=-0.4 # Complex parameter, connected to coordinate of the Mandelbrot set in a complex plane. Constants here.
Limits=c(-2,2)
MaxIter=60
cl=colours()
S=floor(length(cl)/MaxIter)
Step=seq(Limits[1],Limits[2],by=0.01)
PointsMatrix=array(0,dim=c(length(Step)*length(Step),3))# hace una matriz de len^2 * 3
a1=0
DIST=0
plot(0,0,xlim=Limits,ylim=Limits,col="white")# crea la plantilla XD

for(x in Step)
{
	for(y in Step)
	{
		n=0
		x1=x;y1=y # Original x and y are saved.
		while(n<MaxIter & DIST<4)
		{
			newx=x1^2-y1^2+a
			newy=2*x1*y1+b
			DIST=newx^2+newy^2
			x1=newx;y1=newy
			n=n+1
		}
		if(DIST<4) colour=24 else colour=n*S
		#points(x,y, pch=".", col=cl[colour])
		a1=a1+1
		PointsMatrix[a1,]=c(x,y,colour)
	}
}

X11()
plot(PointsMatrix[,1], PointsMatrix[,2], xlim=Limits, ylim=Limits, col=cl[PointsMatrix[,3]], pch=".",main="JULIA")