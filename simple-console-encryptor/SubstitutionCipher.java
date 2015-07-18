
class SubstitutionCipher {

    String original = "", newStr = "";
    java.util.ArrayList<Integer> nums = new java.util.ArrayList<>();

    public String decide(String message, boolean isEncrypt) {

        String msg = "";
        //converts all letters to lowercase.
        original = message.toLowerCase();
        java.util.Scanner kb = new java.util.Scanner(System.in);
        int val;
        System.out.println("Enter shift value 1-26: ");
        val = kb.nextInt();
        if (isEncrypt == true) {
            msg = encrypt(val);
        } else {
            msg = decrypt(val);
        }
        return msg;
    }

    //Adds to nums list and changes values
    private String encrypt(int value) {
        convert(0);
        java.util.ArrayList<Integer> tempA = new java.util.ArrayList<>();
        for (int p : nums) {
            int x = p;
            if ((x + value) > 26) {
                int temp = x + value;
                int y = temp - 26;
                p = y;
                tempA.add(p);
            } else {
                p += value;
                tempA.add(p);
            }
        }
        nums = tempA;
        convert(1);
        return newStr;
    }

    private String decrypt(int value) {
        convert(0);
        java.util.ArrayList<Integer> tempA = new java.util.ArrayList<>();
        for (int p : nums) {
            int x = p;
            if ((x - value) < 1) {
                int temp = value - x;
                int y = 26 - temp;
                p = y;
                tempA.add(p);
            } else {
                p -= value;
                tempA.add(p);
            }
        }
        nums = tempA;
        convert(1);
        return newStr;
    }

    private void convert(int which) {
        int[] numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
        char[] letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

        //to numbers
        if (which == 0) {
            char[] stringToChar = original.toCharArray();
            for (char c : stringToChar) {
                for (int m = 0; m < letters.length; m++) {
                    if (c == letters[m]) {
                        nums.add(numbers[m]);
                    }
                }
            }
        } //to letters
        else {
            for (int i : nums) {
                for (int m = 0; m < numbers.length; m++) {
                    if (i == numbers[m]) {
                        newStr += letters[m];
                    }
                }
            }
        }
    }
}
