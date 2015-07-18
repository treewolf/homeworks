
class ShuffleCipher {

    String msg, original;
    java.util.ArrayList<Character> charList = new java.util.ArrayList<>();

    public String decide(String message, boolean isEncrypt) {

        //converts all letters to lowercase.
        original = message.toLowerCase();
        java.util.Scanner kb = new java.util.Scanner(System.in);
        int val;
        int min = Math.abs((original.length() - 4) - original.length()), max = Math.abs((original.length() / min - 1) + original.length() / 3 - original.length() / (original.length() / 2));
        System.out.println("Enter shuffle value " + min + "-" + max + ": ");
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
        char[] extra = new char[7];

        int p = 0, wmark = secondHalf.length;
        int valuePointer = value;
        while (wmark > valuePointer / 2) {
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
            try {
                if (secondHalf.length % value != 0) {
                    int mIndex = secondHalf.length - (secondHalf.length % value);
                    for (int j = mIndex; j < secondHalf.length; j++) {
                        extra[j - mIndex] = secondHalf[j];
                    }
                } else {
                }
            } catch (java.lang.Exception e) {
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

        String tempStr = "";
        newStr = original;
        try {
            boolean onA = true, more = true;
            for (int i = 0; i < 1; i++) {
                if (onA && more) {
                    atemp.add(newStr.substring(i, i + value));
                    tempStr = newStr.substring(i + value);
                    newStr = tempStr;
                    onA = false;
                    if (newStr.length() < value) {
                        more = false;
                    } else {
                        i--;
                    }
                } else if (onA == false && more) {
                    btemp.add(newStr.substring(i, i + value));
                    tempStr = newStr.substring(i + value);
                    newStr = tempStr;
                    onA = true;
                    if (newStr.length() < value) {
                        more = false;
                        ctemp.add(newStr);
                        for (int ex = 0; ex < ctemp.size(); ex++) {
                            atemp.add((ctemp.get(0).substring(ex, ctemp.get(0).length() / 2)));
                            btemp.add((ctemp.get(0).substring(ctemp.get(0).length() / 2)));
                        }
                    } else {
                        i--;
                    }
                } else {
                }
            }
        } catch (java.lang.Exception e) {
        }

        newStr = "";
        for (String a : atemp) {
            newStr += a;
        }
        for (String b : btemp) {
            newStr += b;
        }

        return newStr;
    }

}
