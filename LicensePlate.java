/**
 * License plate generator, default is set to 20 plates. Three numbers which cannot start with 0 and
 * three letters in uppercase.
 * 
 * @author treewolf
 */

class LicensePlate {
    
    //Number of plates.
    private final static int number_of_plates = 20;
    
    //Where randomly generated pairs are stored.
    private final static java.util.ArrayList<String> part1 = new java.util.ArrayList<>();
    private final static java.util.ArrayList<String> part2 = new java.util.ArrayList<>();

    //Pairs up lists.
    public static void main(String[] args) {
        for(int i=0; i<number_of_plates; i++){
            
            //Calls methods.
            addNumbers();
            addLetters();
            
            //Prints out each result.
            System.out.println(part1.get(i) + part2.get(i));
        }
    }
    
    //Generates random 3-digit number, stores as string.
    private static void addNumbers(){
        java.util.Random r = new java.util.Random();
        part1.add( ( r.nextInt(999 - 100) + 100 )+"" );        
    }
    
    //Generates 3 random letters, stores as string.
    private static void addLetters(){
        char[] letter = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
        java.util.Random r = new java.util.Random();
        String temp = "";
        for(int i=0; i<3; i++){
            int j = r.nextInt(26 - 1) + 1;
            temp += letter[j-1];
        }
        part2.add(temp);
    } 
}
