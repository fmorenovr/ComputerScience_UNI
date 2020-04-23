import pygame, sys
from pygame.locals import *
from math import sin,cos,pi
import threading
import time
from random import *
from datetime import datetime

pygame.init()
# set up the window
DISPLAYSURF = pygame.display.set_mode((1000, 500), 0, 32)
pygame.display.set_caption('Multi Coaster')
# set up the colors)
BLACK = ( 0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = ( 0, 255, 0)
BLUE = ( 0, 0, 255)
BROWN = (165, 42, 42)
#setting clock rate(limits the frame persecond)
FPS = 30
fpsClock = pygame.time.Clock()
radius=200
center = (500,250)
#max capacity of each car
MAX_CAPACITY=2
PASSENGER_THREADS = 6
CAR_THREADS = 2
i=0
#for storing faces of threads
platform = []
cars = []
waitingCars = []
mousex = 0
mousey = 0

#changing the name of semaphore fields acquire and release to wait and signal respectively
class Semaphore(threading._Semaphore):
	wait = threading._Semaphore.acquire
	signal = threading._Semaphore.release

#creating threads such that they are immediately
class Thread(threading.Thread):
	def __init__(self, t, *args):
		threading.Thread.__init__(self, target=t, args=args)
		self.start()
faces = []

#loading images of faces in a list
for i in range(1,5):
	faces.append(pygame.image.load('face{0}.png'.format(i)))

#scaling images of faces to 30X30 pixel images and adding them to the platform list
for i in range(len(faces)):
	faces[i] = pygame.transform.scale(faces[i], (30, 30))

carImg = pygame.image.load('car.png')
carHorizontalOffset = carImg.get_width()/2
faceHorizontalOffset = faces[1].get_width()/2
lineStartX = center[0]-radius-faces[0].get_width()

def increment():
	global i
	i=i+1
	return i

class Passenger:	
	def __init__(self):
		self.face = None
		self.passengerPosition = ()
		self.passengerCar = None	
	def board(self,car):
		car.loading.wait()
		self.passengerCar = car
		car.seats.append(self)
		#platform.pop(platform.index(self))
		platform.pop(0)
	def unboard(self):
		self.passengerCar.unloading.wait()
		self.passengerCar.seats.pop(self.passengerCar.seats.index(self))

# RollerCoaster class
class RollerCoaster:
	def __init__(self):
		self.angle = -pi
		self.position = (center[0]+radius*cos(self.angle) -carHorizontalOffset,center[1]+radius*sin(self.angle)-carHorizontalOffset)
		#list containing the names of people on the roller coaster
		self.seats = []  
		#initializing a car image
		self.carPrintPosition=()
		self.loading = Semaphore(0)
		self.unloading = Semaphore(0)
	def load(self):
		self.loading.signal()
		self.loading.signal()
	def unload(self):
		self.unloading.signal()
		self.unloading.signal()

#climbOn = Semaphore()
platformFree = Semaphore(1)
#loadOrUnload = Semaphore(1)
carsFree = Semaphore(1)


#passenger runner function
def passengerRunner():
	passenger = Passenger()
	passenger.face = faces[increment()%4]
	#time.sleep(randint(2,10))
	platformFree.wait()
	platform.append(passenger)
	platformFree.signal()

def carRunner(threadNo):
	car = RollerCoaster()
	carsFree.wait()
	cars.append(car)
	carsFree.signal() 

carThreads = [ Thread( carRunner,i ) for i in range (CAR_THREADS)]
#passThreads = [ Thread ( passengerRunner,i ) for i in range (PASSENGER_THREADS)]
passThreads = []
dist = 40
while True:
	#populating the display screen with objects(this needs to be done for every frame)
	DISPLAYSURF.fill(WHITE)
	pygame.draw.circle(DISPLAYSURF, BROWN, (500, 250), 200, 1)
	pygame.draw.circle(DISPLAYSURF, BROWN, (500, 250), 180, 1)

	for x in cars:
		if cos(x.angle) == -1 :
			if len(x.seats) == 2:
				x.unload()
				while(len(x.seats)!=0):
					x.seats[0].unboard()
			x.load()
			if(len(platform)>=2):
				platform[0].board(x)
				platform[0].board(x)
				x.angle+=pi/180
				x.position = (center[0]+radius*cos(x.angle) -carHorizontalOffset,center[1]+radius*sin(x.angle)-carHorizontalOffset)
				if x in waitingCars:
					del waitingCars[:]
			else:
				if x not in waitingCars:
					x.angle = -pi-30*pi/180*len(waitingCars)
					waitingCars.append(x)
					x.position = (center[0]+radius*cos(x.angle) -carHorizontalOffset,center[1]+radius*sin(x.angle)-carHorizontalOffset)
			
	for x in cars:
		if cos(x.angle) !=- 1 and x not in waitingCars :
			x.angle+=pi/180
			x.position = (center[0]+radius*cos(x.angle) -carHorizontalOffset,center[1]+radius*sin(x.angle)-carHorizontalOffset)
			if(len(waitingCars)!=0):
				if cos(waitingCars[len(waitingCars)-1].angle-x.angle) <= 0.866+0.01 and cos(waitingCars[len(waitingCars)-1].angle-x.angle) >= 0.866-0.01 and sin(waitingCars[len(waitingCars)-1].angle-x.angle) >= 0.5-0.01 and sin(waitingCars[len(waitingCars)-1].angle-x.angle) <= 0.5+0.01 :
					waitingCars.append(x)

	for x in cars:
		DISPLAYSURF.blit(carImg, x.position)
		count = 0
		for y in x.seats:
			DISPLAYSURF.blit(y.face, (x.position[0]+count*carHorizontalOffset+faceHorizontalOffset,x.position[1]+faceHorizontalOffset))
			count+=1
	count = 2
	for x in platform:
		DISPLAYSURF.blit(x.face, (center[0]-radius-count*dist,center[1]-15))
		count+=1
	#DISPLAYSURF.blit(carImg,rect)
	for event in pygame.event.get():
		if event.type == QUIT:
			pygame.quit()
			sys.exit()
		if event.type == pygame.MOUSEBUTTONUP:
			#mousex,mousey = pygame.mouse.get_pos()
			passThreads.append(Thread ( passengerRunner))	


	pygame.display.update()
	fpsClock.tick(FPS)
