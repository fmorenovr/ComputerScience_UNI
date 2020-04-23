/**
* Assignment: Project 3
* Due date: 11/22/13
* Instructor: Dr. DePasquale 
* Submitted by: Leah Lewy
*/
import java.lang.Math;
import java.io.*;
import java.util.*;
import java.net.*;
import java.io.*;

import utils.*;
import exceptions.*;

/**
*This class is where all action resides. It contains all the queues that represent the lanes at the intersection.
* It also contains all methods that pertain to populating the intersection and moving the vehicles in their 
* retrospective directions.
*/
public class Simulator {
	/** This queue will hold only vehicle objects that enter in the left lane on Main Street headed East. */
	private LinkedQueue<Vehicle> EMainL = new LinkedQueue<Vehicle>();
	/** This queue will hold only vehicle objects that enter in the right lane on Main Street headed East. */
	private LinkedQueue<Vehicle> EMainR = new LinkedQueue<Vehicle>();
	/** This queue will hold only vehicle objects that enter in the left lane on Main Street headed West. */
	private LinkedQueue<Vehicle> WMainL = new LinkedQueue<Vehicle>();
	/** This queue will hold only vehicle objects that enter in the right lane on Main Street headed West. */
	private LinkedQueue<Vehicle> WMainR = new LinkedQueue<Vehicle>();
	/** This queue will hold only vehicle objects that enter in the left lane on Church Street headed North. */
	private LinkedQueue<Vehicle> NChurchL = new LinkedQueue<Vehicle>();
	/** This queue will hold only vehicle objects that enter in the right lane on Church Street headed North. */
	private LinkedQueue<Vehicle> NChurchR = new LinkedQueue<Vehicle>();
	/** This queue will hold only vehicle objects that enter in the left lane on Church Street headed South. */
	private LinkedQueue<Vehicle> SChurchL = new LinkedQueue<Vehicle>();
	/** This queue will hold only vehicle objects that enter in the right lane on Church Street headed South. */
	private LinkedQueue<Vehicle> SChurchR = new LinkedQueue<Vehicle>();
	/** This integer value will keep track of the current time during the simulation.*/
	int time = 0;
	/** This integer value will be used to make sure only two vehicles move during each light change for each lane. */
	int i = 0;
	/** This integer value will keep track of the vehicle numbers of the cars that arrive at the intersection. */
	int vehicleNum = 1;
	/** This creates a filewriter object that allows us for the ability to write streams of characters to a file. */
	FileWriter fw;
	/** This creates a bufferedwriter object that allows for the efficient writing to the file. */
	BufferedWriter bw;
	/** This creates a printwriter object that allows for the ability to use the print methods when writing to the file. */
	PrintWriter outFile;

	/**
    * This is a constructor. It sets up the ability for a simulator object to be instantiated.
    */
	public Simulator() {}

	/** 
	* This method calls all others methods in this class. It firsts instantiates the objects associated with
	* writing to the file. It then calls the populate method to start the simulation and create car objects. The 
	* amount of car objects created is between 7 and 12. Until all queues are empty, the simulation will continue 
	* to run. During the simulation, the cars will move in the North/South direction for 6 seconds, then more 
	* cars will arrive (between 8 and 15). Then the cars will move in the East/ West direction for 6 seconds, 
	* and more cars will arrive (between 3 and 15).
	* @throws IOException this is done in case their is an error printing to the file
	*/
	public void Simulate() {
		try {
		fw = new FileWriter("output.txt");
		bw = new BufferedWriter(fw);
		outFile = new PrintWriter(bw);
	
			outFile.print("---Start of simulation, time set to 0.--- \n");
			populate((int)(Math.random() * (13 - 7) + 7));
			while(!queuesEmpty()) {
				outFile.print("---Light changed. Now processing north/south-bound traffic--- \n");
				moveNorthSouth();
				populate((int)(Math.random() * (16 - 8) + 8));
				outFile.println();
				outFile.print("---Light changed. Now processing east/west-bound traffic---\n");
				moveEastWest();
				populate((int)(Math.random() * (16 - 3) + 3));
				outFile.println();
			}	
			outFile.close();
		}
		catch(IOException e){
			System.err.println("Error printing to file");
		}
	}

	/**
	* This method is only called once when first populating the intersection. It instantiates the amount of cars
	* according to the number that is passed in. The time they are created, their arrival times, is 
	* the current time in the simulation. Each time a new vehicle is created, the vehicle number increases by 1.
	* Depending on what lane and direction the car enters the simulation, it is placed correctly into its
	* corresponding queue. 
	* @param number of cars to be instantiated
	*/
	private void populate(int randomNum) {
		int count = 0;
		while (count < randomNum && vehicleNum <=120) {
			Vehicle car = new Vehicle(vehicleNum, time, time);
			count++;
			vehicleNum++;
			if (car.getStreet() == Vehicle.Street.Main && car.getDirection() == Vehicle.Direction.E && car.getLane() == Vehicle.Lane.Left)
				EMainL.enqueue(car);
			else if (car.getStreet() == Vehicle.Street.Main && car.getDirection() == Vehicle.Direction.E && car.getLane() == Vehicle.Lane.Right)
				EMainR.enqueue(car);
			else if (car.getStreet() == Vehicle.Street.Main && car.getDirection() == Vehicle.Direction.W && car.getLane() == Vehicle.Lane.Left)
				WMainL.enqueue(car);
			else if (car.getStreet() == Vehicle.Street.Main && car.getDirection() == Vehicle.Direction.W && car.getLane() == Vehicle.Lane.Right)
				WMainR.enqueue(car);
			else if (car.getStreet() == Vehicle.Street.Church && car.getDirection() == Vehicle.Direction.N && car.getLane() == Vehicle.Lane.Left)
				NChurchL.enqueue(car);
			else if (car.getStreet() == Vehicle.Street.Church && car.getDirection() == Vehicle.Direction.N && car.getLane() == Vehicle.Lane.Right)
				NChurchR.enqueue(car);
			else if (car.getStreet() == Vehicle.Street.Church && car.getDirection() == Vehicle.Direction.S && car.getLane() == Vehicle.Lane.Left)
				SChurchL.enqueue(car);
			else
				SChurchR.enqueue(car);
		}	
	}

	/**
	* This method simulates the movement of vehicles in the North / South direction. Four queues are operated
	* on at this traffic light, but the NChurchL one will be used to exemplify the functionality of the method.
	* If there are cars waiting to move and while only two are allowed to move, a new vehicle object is 
	* instantiated. The first car in the spot is then dequeued and stored into the new car object. Its departure
	* time is set to the current time on the clock, which was previously increased by 3 seconds each time the loop
	* begins. 
	* @throws EmptyCollectionException this is done in case the queue is empty
	*/
	private void moveNorthSouth() {
		int i = 0;
		while (i < 2) {
			time+=3;
			try {
				if (!NChurchL.isEmpty()) {
					Vehicle car = new Vehicle(0,0,0);
					car = NChurchL.dequeue();
					car.setDepartureTime(time);
					outFile.println(car);					
				}
			}
			catch(EmptyCollectionException e) {}
			try {	
				if (!NChurchR.isEmpty()) {
					Vehicle car = new Vehicle(0,0,0);
					car = NChurchR.dequeue();
					car.setDepartureTime(time);
					outFile.println(car);					
				}
			}
			catch(EmptyCollectionException e) {}
			try {
				if (!SChurchL.isEmpty()) {
					Vehicle car = new Vehicle(0,0,0);
					car = SChurchL.dequeue();
					car.setDepartureTime(time);
					outFile.println(car);					
				}
			}
			catch(EmptyCollectionException e) {}
			try {
				if (!SChurchR.isEmpty()) {
					Vehicle car = new Vehicle(0,0,0);
					car = SChurchR.dequeue();
					car.setDepartureTime(time);
					outFile.println(car);					
				}
			}
			catch(EmptyCollectionException e) {}
		i++;
		}
	}

	/**
	* This method mimics the above method. However, in this instance, only vehicles in the east and west
	* lanes will be operated on.
	*/
	private void moveEastWest() {
		int i = 0;
		while (i < 3) {
			time+=3;
			try {
				if (!EMainL.isEmpty()) {
					Vehicle car = new Vehicle(0,0,0);
					car = EMainL.dequeue();
					car.setDepartureTime(time);
					outFile.println(car);					
				}
			}
			catch(EmptyCollectionException e) {}
			try {	
				if (!EMainR.isEmpty()) {
					Vehicle car = new Vehicle(0,0,0);
					car = EMainR.dequeue();
					car.setDepartureTime(time);
					outFile.println(car);					
				}
			}
			catch(EmptyCollectionException e) {}
			try {	
				if (!WMainL.isEmpty()) {
					Vehicle car = new Vehicle(0,0,0);
					car = WMainL.dequeue();
					car.setDepartureTime(time);
					outFile.println(car);					
				}
			}
			catch(EmptyCollectionException e) {}
			try {	
				if (!WMainR.isEmpty()) {
					Vehicle car = new Vehicle(0,0,0);
					car = WMainR.dequeue();
					car.setDepartureTime(time);
					outFile.println(car);					
				}
			}
			catch(EmptyCollectionException e) {}	
		i++;
		}	
	}

	/**
	* This method goes through each queue and checks to see if they are empty. At the end, if all queues are
	* empty, it returns a true value. This method is later used to know when to stop the simulation.
	*/
	private boolean queuesEmpty(){
		boolean empty;
		
		empty = EMainL.isEmpty();
		
		if(empty)
			empty = EMainR.isEmpty();
		if(empty)
			empty = WMainL.isEmpty();
		if(empty)
			empty = WMainR.isEmpty();
		if(empty)
			empty = NChurchL.isEmpty();
		if(empty)
			empty = NChurchR.isEmpty();
		if(empty)
			empty = SChurchL.isEmpty();
		if(empty)
			empty = SChurchR.isEmpty();
			
		return empty;
	}

}
