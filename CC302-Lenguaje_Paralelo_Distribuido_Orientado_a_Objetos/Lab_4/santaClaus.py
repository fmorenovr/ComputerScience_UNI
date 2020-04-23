import random
from threading import Semaphore
from threading import Thread
import time

elves_c = 0
reindeer_c = 0
santaSem = Semaphore()
reindeerSem = Semaphore()
elfTex = Semaphore()
mutex = Semaphore(1)


def prepareSleigh():
    global reindeer_c
    print("Santa Claus: preparing sleigh")


def helpElves():
    print("Santa Claus: helping elves")


def getHitched():
    print("This is reindeer ", reindeer_c)


def getHelp():
    print("This is elve", elves_c)


def santa():
    global elves_c, reindeer_c
    print("Santa Claus: Hoho, here I am")
    while True:
        santaSem.acquire()
        mutex.acquire()
        if reindeer_c >= 9:
            prepareSleigh()
            for i in range(9):
                reindeerSem.release()
            print("Santa Claus: make all kids in the world happy")
            reindeer_c -= 9
            time.sleep(4)
        elif elves_c == 3:
            helpElves()
        mutex.release()


def reindeer():
    global reindeer_c
    while True:
        mutex.acquire()
        reindeer_c += 1
        if reindeer_c == 9:
            santaSem.release()
        mutex.release()
        getHitched()
        print("Reindeer", reindeer_c, "getting hitched")
        reindeerSem.acquire()
        time.sleep(random.randint(2, 3))


def elves():
    global elves_c
    while True:
        elfTex.acquire()
        mutex.acquire()
        elves_c += 1
        if elves_c == 3:
            santaSem.release()
        else:
            elfTex.release()
        mutex.release()
        getHelp()
        time.sleep(random.randint(2, 5))
        mutex.acquire()
        elves_c -= 1
        if elves_c == 0:
            elfTex.release()
        mutex.release()
        print("Elve", elves_c, "at work")


elfThread = []  # threads for elves
reindThread = []  # threads from reindeers


def main():
    thread = Thread(target=santa)  # main thread for SantaClaus
    thread.start()  # starting the thread
    for i in range(9):
        reindThread.append(Thread(target=reindeer))
    for j in range(9):
        elfThread.append(Thread(target=elves))
    for t in elfThread:
        t.start()
    for t in reindThread:
        t.start()
    for t in elfThread:
        t.join()
    for t in reindThread:
        t.join()
    thread.join()


main()
