import java.util.Scanner;

public class _2_StringHandling {
    public static void main(String[] args) {
        // StringBuffer used to make mutable strings
        StringBuffer s = new StringBuffer();
        s.append("Java Programming");
        String str;

        System.out.println("Initial string without append:" + s);
        System.out.println("The current capacity of StringBuffer is:" + s.capacity());

        Scanner input = new Scanner(System.in);
        System.out.print("Enter a string to append:");
        str = input.nextLine();
        s.append(" " + str);
        System.out.println("Initial string after appending:" + s);

        System.out.println("string after reversing:" + s.reverse());

        int i = 0;
        while (i < s.length()) {
            // replace(int start, int end, String str) :it replaces string parts
            s.replace(i, i + 1, s.substring(i, i + 1).toUpperCase());
            i = i + 1;
        }
        System.out.println("After reversing and converting to upper case:" + s);
    }

}
