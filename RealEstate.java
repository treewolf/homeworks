/**
 * Real estate agent advertisements frequently contain words from which all
 * vowels — except for an initial one — have been removed.
 * Thus, Desirable unfurnished flat in quiet residential area might become: 
 * Dsrbl unfrnshd flt in qt rsdntl ar 
 * Write a complete Java program that reads in a normal one-line
 * description of a property (terminated by a carriage-return) and prints the
 * corresponding advertisement. Your program must contain at least one method in
 * addition to the main method, which takes the String description and returns
 * the corresponding vowel-less ad.
 *
 */
class RealEstate {

    public static void main(String[] args) {
        java.util.Scanner kb = new java.util.Scanner(System.in);
        System.out.println("Enter sentence here: ");
        System.out.println(splitter(kb.nextLine()));

    }

    //Where the sentence is split.
    private static String splitter(String sentence) {
        String newStr = "";
        char[] letters = sentence.toCharArray();
        System.out.println(letters);
        for (int i = 0; i < letters.length; i++) {
            if (('a' != letters[i] && 'e' != letters[i] && 'i' != letters[i] && 'o' != letters[i] && 'u' != letters[i])) {
                //This is when the char is a vowel and not in first position inside a word.
                newStr += letters[i];
            } else {
                if (letters[i - 1] == ' ') {
                    newStr += letters[i];
                }
            }
        }
        return newStr;
    }
}
