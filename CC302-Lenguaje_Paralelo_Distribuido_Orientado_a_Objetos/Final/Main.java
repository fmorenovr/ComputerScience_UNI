/**
* Assignment: Project 3
* Due date: 11/22/13
* Instructor: Dr. DePasquale 
* Submitted by: Leah Lewy
*/

/**
* The Driver class acts as a container for the main method. There is not a
* specific inherent purpose for the class.
* @author Leah Lewy
*/
public class Main {
	/**
	* All functionality of the Driver application exists within 
	* main method. It soley instantiates a simulator object and then runs a method
	* that performs the entire simulation of the traffic intersection.
	* @param args Permits functionality of the command line	
	*/
	public static void main (String[] args) {
		Simulator simulator = new Simulator();
		simulator.Simulate();
	}
}
