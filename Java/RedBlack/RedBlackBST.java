public class RedBlackBST<Key extends Comparable<Key>, Value>{
	
	private static final boolean RED = true;
	private static final boolean BLACK = false;

	public class Node{

		private Key key;	// key
		private Value val;	// associated value
		private Node left, right;	// links to subtrees
		private int N;		// # nodes in subtree rooted here
		private boolean color;

		public Node(Key key, Value val, int N, boolean color){
			this.key = key;
			this.val = val;
			this.N = N;
			this.color = color;
		}
	}

	private Node root;

	private boolean isRed(Node x){
		if(x == null)
			return false;
		return x.color == RED;
	}

	public void print(){
		print(root);
	}

	private Node print(Node x){
		if(x == null)
			return x;
		String c = "";
		if(isRed(x))
			c = "RED";
		else
			c = "BLACK";
		System.out.println(x.key.toString() + "\t" + c + "\t" + (size(x) - 1));
		print(x.left);
		print(x.right);
		return x;
	}

	@SuppressWarnings("unchecked")
	public void put(Key key, Value val){
		root = put(root, key, val);
		root.color = BLACK;
	}

	@SuppressWarnings("unchecked")
	private Node put(Node h, Key key, Value val){
		if(h == null)
			return new Node(key, val, 1, RED);
		
		int cmp = key.compareTo(h.key);
		if(cmp < 0) 
			h.left = put(h.left, key, val);
		else if(cmp > 0)
			h.right = put(h.right, key, val);
		else
			h.val = val;

		if(isRed(h.right) && !isRed(h.left))
			h = rotateLeft(h);
		if(isRed(h.left) && isRed(h.left.left))
			h = rotateRight(h);
		if(isRed(h.left) && isRed(h.right))
			flipColors(h);

		h.N = size(h.left) + size(h.right) + 1;
		return h;
	}

	private Node rotateLeft(Node h){
		Node x = h.right;
		h.right = x.left;
		x.left = h;
		x.color = h.color;
		h.color = RED;
		x.N = h.N;
		h.N = 1 + size(h.left) + size(h.right);
		return x;
	}
	
	private Node rotateRight(Node h){
		Node x = h.left;
		h.left = x.right;
		x.right = h;
		x.color = h.color;
		h.color = RED;
		x.N = h.N;
		h.N = 1 + size(h.left) + size(h.right);
		return x;
	}

	private void flipColors(Node h){
		h.color = RED;
		h.left.color = BLACK;
		h.right.color = BLACK;
	}

	public int size(){
		return size(root);
	}

	private int size(Node x){
		if(x == null)
			return 0;
		else
			return x.N;
	}
}
