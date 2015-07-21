
/**
 * A student has decided to celebrate the start of Spring Break by getting a bit
 * smashed. Her home is at 1st street and main street, and the jail is at 11th
 * street. and main street. The student starts at 6th street and main street and
 * randomly chooses to wander one block up or down main street with equal
 * probability, 0.5. At each intersection she repeats the process until arriving
 * safely at home or landing in jail. That is, at each intersection, the drunk
 * student has a 50-50 probability of staggering a block one way or the other,
 * to the next higher-numbered or next lower-numbered street. Write a method
 * named drunkWalk() using a while or a do-while loop that simulates the drunk
 * student’s walk; your method should return an integer that indicates how many
 * blocks were walked. You should print out how many blocks were walked and
 * where the student landed. You should not print out each step taken in your
 * final version of the method, though you might want to do this while you are
 * debugging. Once you have your method working, have your main program call
 * upon your drunkWalk()method N times (where N is a final variable). Finally,
 * have it calculate and print the average number of blocks that the student
 * took for one trip, to one decimal place. Here’s what your program might look
 * like in action, with N equal to 5: Here we go again... time for a walk!
 * Walked 37 blocks, and Landed at HOME Here we go again... time for a walk!
 * Walked 19 blocks, and Landed in JAIL Here we go again... time for a walk!
 * Walked 13 blocks, and Landed in JAIL Here we go again... time for a walk!
 * Walked 25 blocks, and Landed in JAIL  Here we go again... time for a walk!
 * Walked 15 blocks, and Landed at HOME Average # of blocks equals 21.8
 *
 */
class Drunk {

    private static double blocks = 0;

    public static void main(String[] args) {
        java.util.Scanner kb = new java.util.Scanner(System.in);
        System.out.println("How many tries? ");
        int input = kb.nextInt();
        drunkWalk(input);
        System.out.println("Average # of blocks equals " + (double) (blocks / input));
    }

    //if random is even, student walks down, else walks up.
    public static void drunkWalk(int count) {
        java.util.Random r = new java.util.Random();
        String temp = "";
        int tries = 0;

        while (tries < count) {
            boolean cont = true;
            int blocks_per_turn = 0, currentBlock = 6;

            while (cont) {
                int num = r.nextInt(9 - 0 + 1) + 0;
                if (num % 2 == 0) {
                    currentBlock++;
                } else {
                    currentBlock--;
                }
                blocks++;
                blocks_per_turn++;

                //checks to see if in jail or at home
                if (currentBlock == 11) {
                    cont = false;
                    temp = "in JAIL";

                } else if (currentBlock == 1) {
                    cont = false;
                    temp = "at HOME";
                }
            }
            tries++;
            System.out.print("\nHere we go again...time for a walk!"
                    + "\nWalked " + blocks_per_turn + " blocks, and\n"
                    + "Landed " + temp + "\n");
        }
    }
}
