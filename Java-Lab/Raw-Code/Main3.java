import java.util.Scanner;

class Account {
    static intcurBalance = 1000; // Initial balance
    int amt;

    public Account() {
        Scanner s = new Scanner(System.in);
System.out.println("\nEnter the amount:");
amt = s.nextInt();
    }
    void deposit(int amount) {
curBalance += amount;
System.out.println("Deposit successful.");
    }
    void withdraw(int amount) {
        try {
            if ((curBalance - amount) < 500)
                throw new LessBalanceException(amount);
curBalance -= amount;
System.out.println("Withdrawal successful.");
        } catch (LessBalanceException le) {
System.out.println(le);
        }
    }
    void checkBal() {
System.out.println("\nBalance in your a/c: " + curBalance);
    }
}

class LessBalanceException extends Exception {
    int am;

    public LessBalanceException(int x) {
        am = x;
    }

    public String toString() {
        return ("You cannot withdraw the amount, less balance " + am + " now.");
    }
}

public class Main3 {
    public static void main(String[] args) {
intch;
        Scanner s = new Scanner(System.in);
        Account a = new Account();

        while (true) {
System.out.println("1: Deposit\t2: Withdraw\t3: Check Balance\t4: Exit");
System.out.println("Enter your choice:");
ch = s.nextInt();
            switch (ch) {
                case 1:
System.out.println("Enter deposit amount:");
intdepositAmount = s.nextInt();
a.deposit(depositAmount);
break;
case 2:
System.out.println("Enter withdrawal amount:");
intwithdrawAmount = s.nextInt();
a.withdraw(withdrawAmount);
    break;
case 3:
a.checkBal();
    break;
case 4:
    return;
default:
System.out.println("Invalid choice");
    break;
}
}
}
}
