public class Runner{
	@SuppressWarnings("rawtypes")
	public static void main(String [] args){
		RedBlackBST bst = new RedBlackBST<Integer, Integer>();
	
		int [] a = {77, 67, 53, 92, 46, 39, 82, 24, 15, 25};
		for(int i = 0; i < a.length; ++i)
			bst.put(a[i], i);

		bst.print();
	}
}
