/**
* Assignment: Project 3
* Due date: 11/22/13
* Instructor: Dr. DePasquale 
* Submitted by: Leah Lewy
*/

package utils;

/**
 * Represents a node in a linked data structure.
 * @author Java Foundations
 * @version 4.0
 */
public class LinearNode<T>
{
    private LinearNode<T> next;
    private T element;
 
    /**
     * Provides the ability to instantiate an empty node.
     */
    public LinearNode()
    {
        next = null;
        element = null;
	}
 
    /**
     * Provides the ability to instantiate a node with that specific element
     * @param the element to be stored
     */
    public LinearNode(T elem)
    {
        next = null;
        element = elem;
    }
 
    /**
     * Returns the next node in the chain.
     * @return reference to next node
     */
    public LinearNode<T> getNext()
    {
        return next;
    }
 
    /**
     * Sets the next node in the chain.
     * @param the node you want to be following 
     */
    public void setNext(LinearNode<T> node)
    {
        next = node;
    }
 
    /**
     * Returns the element stored in the current node.
     * @return element stored at the node
     */
    public T getElement()
    {
        return element;
    }
 
    /**
     * Sets the element stored in the current node.
     * @param element to be stored at the node
     */
    public void setElement(T elem)
    {
        element = elem;
    }
}
