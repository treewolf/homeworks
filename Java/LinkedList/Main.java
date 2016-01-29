/**
 * @author treewolf
 */
/*
* This program tests LinkedList
*/
public class Main {
    public static void main(String [] args){
        LinkedList<String> list = new LinkedList<String>();
        System.out.println("*-- Building basic chain: Head,Middle,Tail --*");
        list.addFirst("Head");
        list.addLast("Middle");
        list.addLast("Tail");
        
        System.out.println("List: " + list.first.item + "," + list.first.next.item + "," + list.first.next.next.item);
        System.out.println("-- Adding new head: NewHead");
        list.addFirst("NewHead");
        System.out.println("List: " + list.first.item + "," + list.first.next.item + "," + list.first.next.next.item + "," + list.first.next.next.next.item);
        System.out.println("-- Adding new tail: NewTail");
        list.addLast("NewTail");
        System.out.println("List: " + list.first.item + "," + list.first.next.item + "," + list.first.next.next.item + "," + list.first.next.next.next.item + "," + list.first.next.next.next.next.item);
        System.out.println("-- Removing first: NewHead");
        list.removeFirst();
        System.out.println("List: " + list.first.item + "," + list.first.next.item + "," + list.first.next.next.item + "," + list.first.next.next.next.item);
        System.out.println("-- Removing last: NewTail");
        list.removeLast();
        System.out.println("List: " + list.first.item + "," + list.first.next.item + "," + list.first.next.next.item);
        System.out.println("-- Removing element 2:Middle");
        list.remove(2);
        System.out.println("List: " + list.first.item + "," + list.first.next.item);
    }
}
