import os, sys
import Image

img = Image.open(sys.argv[1])
pix = img.load()
width, height = img.size
#colors = im.getcolors(width*height)
colors = img.convert('RGB').getcolors(width*height)

for x in range(1,width):
  for y in range(1,height):
    print pix[x,y]

print "width: ",width
print "Height: ", height
print "Colores: ", colors
s=[]
for i in colors:
  if i not in s:
    s.append(i)
