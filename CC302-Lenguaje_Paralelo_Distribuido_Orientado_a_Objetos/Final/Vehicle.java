/**
* Assignment: Project 3
* Due date: 11/22/13
* Instructor: Dr. DePasquale 
* Submitted by: Leah Lewy
*/

/**
* The Vehicle class encapsulates the representation of a car object. Each vehicle is labeled with a number.
* It is also marked by the time it arrives at the intersection and the time it departs. The object also
* keeps track of which of the eight lanes the car is in at the intersection.
* @author Leah Lewy
*/
public class Vehicle {
	/**
	*This is the creation of the enumerated type direction with its possible values of 
	* north, east, west, or south. 
	*/
	public enum Direction{N, E, S, W};
	/**
	*This is the creation of the enumerated type street with its possible values of 
	* Main or Church. This is later determined by which direction the car is going in.
	*/
	public enum Street{Main, Church};
	/**
	*This is the creation of the enumerated type lane with its possible values of 
	* left (car is continuing straight) or right (car is turning).
	*/
	public enum Lane{Left, Right};
	/** This integer value will represent the vehicle number, which will start at 1 and increment with each new car.*/
	private int vehicleNumber;
	/** This integer value will represent the time at which the car arrives at the intersection. */
	private int arrivalTime;
	/** This integer value will represent the time at which the car leaves at the intersection. */
	private int departureTime;
	/** This enumerated type will represent the street that the car pulls up at. */
	private Street street;
	/** This enumerated type will represent the direction in which the car is heading. */
	private Direction direction;
	/** This enumerated type will represent the lane in which the car is in. */
	private Lane lane;
	/** This string object will later be used in the toString to store the value of northbound, eastbound, etc. */
	private String bound;
	/** 
	*This string object will later be used in the toString to store the phrase of where the car continues after 
	*exiting the intersection.
	*/
	private String continuation;

	/**
    * This is a constructor. It sets up the ability for a car object to be instantiated.
    * Each time a vehicle is created, it is provided a random direction, street, and lane as well
    * as given the values it is passed in through the parameters.
    * @param vehicleNum The int value of this object's vehicle number.
    * @param aTime The int value of this object's arrival time.
    * @param dTime The int value of this object's departure time.
    */
	public Vehicle (int vehicleNum, int aTime, int dTime) {
		vehicleNumber = vehicleNum;
		arrivalTime = aTime;
		departureTime = dTime;
		direction = randomDirection();
		street = randomStreet();
		lane = randomLane();
	}

	/**
	* This method assigns each new vehicle a randomly generated direction using the Math.random function.
	* @return the direction the car is headed 
	*/
	public Direction randomDirection() {
		int dirIndicator = (int)(Math.random() * (4 - 0) + 0);
			if(dirIndicator == 1)
				direction = Direction.N;
			else if(dirIndicator == 2)
				direction = Direction.E;
			else if(dirIndicator == 3)
				direction = Direction.S;
			else
				direction = Direction.W;

			return direction;
	}

	/**
	* This method assigns each new vehicle a street based on the previously generated direction
	* from the above method.
	* @return the street the car is on
	*/
	public Street randomStreet() {
		if(direction == Direction.N || direction == Direction.S) {
				street = Street.Church;
			}
		else
			street = Street.Main;

		return street;
	}

	/**
	* This method assigns each new vehicle a randomly generated lane using the Math.random function.
	* @return the lane the car is in
	*/
	public Lane randomLane() {
		int laneIndicator = (int)(Math.random() * (2 - 0) + 0);
		if (laneIndicator ==1)
			lane =Lane.Left;
		else 
			lane = Lane.Right;

		return lane;
	}

	/** 
    *This is an accessor method that allows an outside class to view the direction of a car object. 
    *@return the direction of the car
    */
	public Direction getDirection() {
		return direction;
	}

	/** 
    *This is an accessor method that allows an outside class to view the street of a car object. 
    *@return the street of the car
    */
	public Street getStreet() {
		return street;
	}

	/** 
    *This is an accessor method that allows an outside class to view the lane of a car object. 
    *@return the lane of the object
    */
	public Lane getLane() {
		return lane;
	}

	/** 
    *This is a mutator method that allows an outside class to set the departure time of a car object. 
    *@param the current time
    */
	public void setDepartureTime(int time){
		departureTime = time;
	}

	/** 
    *This is an accessor method that allows an outside class to view the vehicle number of a car object. 
    *@return the vehicle number of the object
    */
	public int getVehicleNumber() {
		return vehicleNumber;
	}
	
	/**
	* This method sets the string value of bound to the associated direction in which the car starts off in.
	* @return the string representation of the original bound
	*/
	public String getBound() {
		if (direction == Direction.S)
			return "southbound";
		else if (direction == Direction.N)
			return "northbound";
		else if (direction == Direction.W)
			return "westbound";
		else
			return"eastbound";
	}

	/**
	* This method sets the string value of continuation to the associated direction in which the car is headed.
	* If the car is going straight, the direction stays the same. If the car is turning, the continuation value
	* mimics that by displaying a new bound that has shifted by 90 degrees.
	* @return the string representation of the new bound 
	*/
	private String getContinuation() {
		if (lane == Lane.Left)
			return "continued straight";
		else if (lane ==Lane.Right && direction == Direction.S)
			return "turned right and headed westbound";
		else if (lane ==Lane.Right && direction == Direction.N)
			return "turned right and headed eastbound";
		else if (lane ==Lane.Right && direction == Direction.W)
			return "turned right and headed northbound";
		else
			return "turned right and headed southbound";
	}

	/** 
    *Returns a string representation of the object
    *@return string representation
    */
	public String toString() {
		String waittime = String.format("%02d", 
					(departureTime - arrivalTime));
		return "[Time " + String.format("%02d", departureTime) + "] Vehicle #" + vehicleNumber + " (" + getBound() + ") " + getContinuation() + ". Total wait time " + waittime + " seconds."; 
	}
}