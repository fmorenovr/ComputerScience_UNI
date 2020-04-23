/**
* Assignment: Project 3
* Due date: 11/22/13
* Instructor: Dr. DePasquale 
* Submitted by: Leah Lewy
*/

package exceptions;

/**
 * Represents the situation in which a collection is empty.
 * It inherits from the runtime exception class.
 * @author Java Foundations
 * @version 4.0
 */
public class EmptyCollectionException extends RuntimeException
{
    /**
     * Sets up this exception with a fitting message.
     * @param the name of the collection
     */
    public EmptyCollectionException(String collection)
    {
        super("The " + collection + " is empty.");
    }
}
