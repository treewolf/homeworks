/**
 * @author treewolf
 */
public class Node<E> {
    E item;
    Node<E> next;
    Node<E> previous;
    
    public Node(E item, Node<E> next, Node<E> previous){
        this.item = item;
        this.next = next;
        this.previous = previous;
    }
}
