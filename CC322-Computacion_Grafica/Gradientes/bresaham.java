import java.lang.*;

public void bresaham(Graphic g,int x1,int y1,int x2,int y2){
	int dx,dy,x,y,x_end,p,const1,const2;
	dx = Math.abs(x1-x2);
	dy = Math.abs(x1-x2);
	p = 2*dy - dx;
	const1 = 2*dy;
	const2 = 2*(dy-dx);
	if(x1>x2){
		x=x2;y=y2;
		x_end = x1;
	}
	else{
		x = x1;y=y1;
		x_end = x2;
	}
	g.drawLine(x,y,x,y);
	while(x<x_end){
		x=x+1;
		if(p<0)	p=p+const1;
		else{
			y=y+1;
			p=p+const2;
		}
		g.drawLine(x,y,x,y);
	}
}
