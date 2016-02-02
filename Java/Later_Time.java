/**
 * 
Homework 1
A Later Time
Objective:
Create a program which prompts the user to enter a time in "Hour:Minute" format and then prompts the user to enter a value, in minutes, that will add to that time. Once the
calculation is completed output the resulting time.
This is assumed to be in military time, so make sure that there is only 24 hours (0-23), 60 minutes (0-59) in any given time.
Take a variety of inputs as long as it is in the format "Hour:Minute" (06:02 and 6:2 are both valid inputs)
Output the original time along with the new time
Example Dialog:
 Enter a time in the format hour:minute
3:30
 Enter a number of minutes to add to this time
50
 The time 50 minutes after 3:30 will be 4:20
Hint:
Here is an algorithm to solve this problem
Read the date.
Make a copy of the date.
Find the index of the ':'. Check out page 86 for some String methods that could be used to do this (or read below)
Copy the hour part out of the time to a new variable.
Parse the hour string into a number.
Next save the minutes into a different variable
Parse the minutes
Add the new minutes to the recently parsed minutes
Adjust the number of minutes to only be 0-59 and add the number of hours, if needed to the hours. Also adjust the hours to be 0-23 if needed.
Print the results!
You may use the ".indexOf(<char>)" operator to find the index of a character in a String.
e.g. "Hello, World!".indexOf('e') returns 1, since the character 'e' has an index of 1 in the String "Hello, World!"
You may need to be able to convert Strings to ints. To do this, you can use Integer.parseInt(<String>).
e.g. Integer.parseInt("100") returns the integer 100.
Note that the String given to parseInt must not have any characters other than numbers, or your program will crash
Finally:
Upload to Dropbox.

@author treewolf
 */
public class Later {
    public static void main(String [] args){
        String time, newMinutes;
        java.util.Scanner kb = new java.util.Scanner(System.in);
        System.out.println("Enter a time in the format hour:minute");
        time = kb.nextLine();
        System.out.println("Enter a number of minutes to add to this time");
        newMinutes = kb.nextLine();
        
        /* Splitted string and parsed ints */
        String[] timeArray = time.split(":");
        int hour = Integer.parseInt(timeArray[0]);
        int minute = Integer.parseInt(timeArray[1]);
        int adding = Integer.parseInt(newMinutes);
        
        /* Add time and format as needed, and set flag for extraneous minutes */
        minute += adding;
        int carryToHour = 0;
        while(minute > 59){
            ++carryToHour;
            minute -= 60;
        }
        hour += carryToHour;
        while(hour > 23){
            hour -= 24;
        }
        
        /* Put together and store */
        String newTime;
        newTime = hour + ":" + minute;
        
        /* Print everything */        
        System.out.println("The time " + newMinutes + " minutes after " + time + " will be " + newTime);
    }
}
