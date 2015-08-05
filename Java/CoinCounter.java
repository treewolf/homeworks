/**
* @Author - treewolf
* Write a Java program that reads from an input file whose data is a series of pairs of tokens, where each pair
* begins with an integer value and is followed by the type of coin, which will be “pennies” (1 cent each), “nickels”
* (5 cents each), “dimes” (10 cents each), or “quarters” (25 cents each), case-insensitively. Your program should add
* up the cash value of all the coins and then output the total amount of money. For example, if the input file
* contains the text
* 3 pennies 2 quarters 1 Pennies 23 NiCKeLs 4 DIMES
* then your program would output Total money = $2.09
*/

class CoinCounter{
    public static void main(String[] args){
        String sentence = "", line = null;
        java.util.Scanner kb = new java.util.Scanner(System.in);
        double total = 0.0;
        //formats the var total for money data
        java.text.NumberFormat form = new java.text.DecimalFormat("$#0.00");
        
        //be sure to enter full path name
        System.out.println("Enter file name: example- C:/Users/Claire.textFile.txt ");
        
        String fileName = kb.nextLine();
        //uncomment if you have a pre-determined text file, and enter file path here. Remember to comment out above statement.
        //String fileName = "<your text file path here>";
        
        try{
            java.io.FileReader fr = new java.io.FileReader(fileName);
            java.io.BufferedReader br = new java.io.BufferedReader(fr);

            //if line is not null, append to string.
            while((line = br.readLine()) != null){
                sentence += line;
            }
        }
        //catches any exception.
        catch(java.lang.Exception e){
            System.out.println("Make sure you have entered the full, correct, name of the file to be read from.");
        }
        System.out.println(sentence);
        
        //assumes text file only has pairs ie 4 penny 5 dimes
        String[] pairs = sentence.split("\\s+");
        for(int element = 0; element < pairs.length - 1; element += 2){
            double amount = Double.parseDouble(pairs[element]);
            if(pairs[element + 1].equalsIgnoreCase("nickels")){
                amount *= 5;
            }
            else if(pairs[element + 1].equalsIgnoreCase("dimes")){
                amount *= 10;
            }
            else if(pairs[element + 1].equalsIgnoreCase("quarters")){
                amount *= 25;
            }
            else if(pairs[element + 1].equalsIgnoreCase("pennies")){
                //There doesn't need to be anything done here.
            }
            else{}
            total += amount;

            //Uncomment this to see what is being processed.
            //System.out.println(pairs[element]);
        }
        System.out.println("Total money: " + form.format(total * .01) );
    }
}

/**
 * ALWAYS wrap your file reader with a buffered reader because then you can read
 * lines at a time rather than characters at a time.
 * 
 * What the program does:
 * 1. Takes a file's contents, assuming everything is either a coin or value.
 * 2. Adds all contents to a string.
 * 3. Splits the string by space: so pairs are now index and index + 1
 * 4. parses values and adds to the total
 * 5. Formats total to readable form and divides by 100 to get coin value
 */
