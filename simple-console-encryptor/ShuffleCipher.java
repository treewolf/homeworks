
class ShuffleCipher {

    String msg, original;
    java.util.ArrayList<Character> charList = new java.util.ArrayList<>();

    public String decide(String message, boolean isEncrypt) {

        //converts all letters to lowercase.
        original = message.toLowerCase();
        java.util.Scanner kb = new java.util.Scanner(System.in);
        int val;
        System.out.println("Enter shuffle value 1-5: ");
        val = kb.nextInt();
        if (isEncrypt == true) {
            msg = encrypt(val);
        } else {
            msg = decrypt(val);
        }
        return msg;
    }

    //split
    private String encrypt(int value) {
        String newStr = "";
        char[] toarray = original.toCharArray();
        char[] firstHalf = java.util.Arrays.copyOfRange(toarray, 0, toarray.length / 2);
        char[] secondHalf = java.util.Arrays.copyOfRange(toarray, toarray.length / 2, toarray.length);

        int p = 0, wmark = secondHalf.length;
        int valuePointer = value;
        while (wmark > p) {
            for (int q = p; q < valuePointer; q++) {
                try {
                    charList.add(firstHalf[q]);
                } catch (java.lang.Exception e) {
                }
            }

            for (int q1 = p; q1 < valuePointer; q1++) {
                try {
                    charList.add(secondHalf[q1]);
                } catch (java.lang.Exception e) {
                }
            }
            p += value;
            valuePointer += value;
        }
        for (char c : charList) {
            newStr += c;
        }
        return newStr;
    }

    //merge
    private String decrypt(int value) {
        String newStr = "";
        java.util.ArrayList<String> atemp = new java.util.ArrayList<>();
        java.util.ArrayList<String> btemp = new java.util.ArrayList<>();
        java.util.ArrayList<String> ctemp = new java.util.ArrayList<>();

        boolean onA = true;
        int tempor = original.length() / value, numberOfTimes = original.length() / value + 1, index = 0;
        if (tempor % 2 == 0) {
            numberOfTimes = tempor;
        } else {
            numberOfTimes = tempor + 1;
        }

        try {
            for (int i = 0; i < numberOfTimes; i++) {
                for (int j = 0; j < value; j++) {
                    if (onA && (((original.length() - index) + 1) - (2 * value)) >= 0) {
                        atemp.add(original.substring(index, index + 1));
                        index++;
                        if (j + 1 >= value) {
                            onA = !onA;
                        }
                    } else if (onA == false && (((original.length() - index) + 1) - (2 * value)) >= 0) {
                        btemp.add(original.substring(index, index + 1));
                        index++;
                        if (j + 1 >= value) {
                            onA = !onA;
                        }
                    } else {
                        ctemp.add(original.substring(index));
                    }
                }
            }

        } catch (java.lang.Exception e) {
        }
        for (String a : atemp) {
            newStr += a;
        }
        for (String b : btemp) {
            newStr += b;
        }
        try {
            for (String c : ctemp) {
                newStr += c;
            }
        } catch (java.lang.Exception e) {
        }
        return newStr;
    }

}
