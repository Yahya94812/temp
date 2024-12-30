import java.util.Scanner;
public class Student
{
public String vtuno;
public String fullName;
public intsem;
public String branchcode;
public String address;

public Student()
{
	Scanner scanner=new Scanner(System.in);
	System.out.print("VTU NO:");
	vtuno=scanner.nextLine();
	System.out.print("FullName:");
	fullName=scanner.nextLine();
	System.out.print("Address:");
	address=scanner.nextLine();
	System.out.print("branch:");
	branchcode=scanner.nextLine();
	System.out.print("semester:");
	sem=scanner.nextInt();
	}

public void show()
{
	System.out.println("Entered Data");
	System.out.println("VTU No. "+vtuno);
	System.out.println("FullName:"+fullName);
	System.out.println("sem:"+sem);
	System.out.println("Branch:"+branchcode);
	System.out.println("Address:"+address);
}
public static void main(String[] args)
{
Student std=new Student();
std.show();
}
}
