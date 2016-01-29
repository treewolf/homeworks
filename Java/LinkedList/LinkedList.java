/**
 * @author treewolf
 */
public class LinkedList<E> {
    Node<E> first;
    
    /* Inserts a node at head */
    public void addFirst(E item){
        Node<E> newHead = new Node<E>(item, first, null);
        first = newHead;        
    }
    
    /* Removes a node from head and returns the deleted node's item */
    /* Does not nullify removed head */
    public E removeFirst(){
        E item = null;
        if(first != null){
            item = first.item;
            first = first.next;    
        }
        return item;
    }
    
    /* Appends a node at tail */
    public void addLast(E item){
        Node<E> newNode = new Node<E>(item, null, null);
        if(first == null){
            first = newNode;
        }
        else{
            Node<E> currentNode = first;
            while(currentNode.next != null){
                currentNode = currentNode.next;
            }
            currentNode.next = newNode;
            newNode.previous = currentNode;
        }
    }
    
    /* Removes a node from tail and returns the deleted node's item */
    /* Removed tail becomes null */
    public E removeLast(){
        Node<E> currentNode = null;
        E item = null;
        if(currentNode != null){
            currentNode = first;
            while(currentNode.next != null){
                currentNode = currentNode.next;
            }
            currentNode.previous.next = null;
            item = currentNode.item;
            currentNode = null;
        }
        return item;
    }
    
    /* Removes the kth node and returns item */
    /* k is 1-based i.e. list=[1, 2, 3, 4, ..] */
    /* If head or tail is k-node, then will use inside function */
    public E remove(int k){
        Node<E> currentNode = null;
        E item = null;
        int n = 0;
        if(first != null){
            currentNode = first;
            n = 1;
            while(n != k && k > 0){
                if(currentNode.next != null){
                    currentNode = currentNode.next;
                    ++n;
                }
            }
            if(n == 1){
                item = removeFirst();
            }
            else if(currentNode.next == null){
                item = removeLast();
            }
            else{
                item = currentNode.item;
                currentNode.previous.next = currentNode.next;
                currentNode.next.previous = currentNode.previous;
            }
            currentNode = null;
            return item;
        }
        return item;
    }
    
}
