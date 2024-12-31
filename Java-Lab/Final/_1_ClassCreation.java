import java.util.Scanner;

class StudentInfo {
    public String vtuno;
    public String fullName;
    public String branch;
    public String semester;
    public String address;

    public StudentInfo() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("VTU NO:");
        vtuno = scanner.nextLine();
        System.out.print("Full Name:");
        fullName = scanner.nextLine();
        System.out.print("branch:");
        branch = scanner.nextLine();
        System.out.print("semester:");
        semester = scanner.nextLine();
        System.out.print("Address:");
        address = scanner.nextLine();

    }

    public void show() {
        System.out.println();
        System.out.println("Entered Data");
        System.out.println("VTU No.: " + vtuno);
        System.out.println("FullName: " + fullName);
        System.out.println("Branch: " + branch);
        System.out.println("semester: " + semester);
        System.out.println("Address: " + address);

    }
}

public class _1_ClassCreation {
    public static void main(String[] args) {
        StudentInfo std = new StudentInfo();
        std.show();
    }
}
