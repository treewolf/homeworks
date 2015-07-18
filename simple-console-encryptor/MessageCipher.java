
/**
 * This class is where the user will interact with the gui. I will leave the gui
 * building up to you. It is also up to you if you want error checking. For now,
 * we will assume the user only uses letters in the English alphabet.
 */
class MessageCipher {

    public static void main(String[] args) {

        //Initiates two subclasses
        SubstitutionCipher subst = new SubstitutionCipher();
        ShuffleCipher shuf = new ShuffleCipher();

        java.util.Scanner kb = new java.util.Scanner(System.in);
        String message;
        int ciph, encrypt; // oppose to decrypt
        boolean isEncrypt = true;

        //User interactio here.
        System.out.println("Choose cipher: 1 Substitution    2 Shuffle : ");
        ciph = kb.nextInt();
        System.out.println("Enter message now: ");
        message = kb.next();
        System.out.println("Encrypt or decrypt (0,1) : ");
        encrypt = kb.nextInt();

        if (encrypt == 1) {
            isEncrypt = false;
            System.out.println("Decrypt");
        } else {
            System.out.println("Encrypt");
        }

        //Calls one of two methods - you need to program interface that chooses.
        if (ciph == 1) {
            message = subst.decide(message, isEncrypt);
        } else if (ciph == 2) {
            message = shuf.decide(message, isEncrypt);
        } else {
            System.out.println("No valid option found. Returning orignial message.");
        }

        //This is where encryption and return value will be.
        System.out.println(message);
    }
}
