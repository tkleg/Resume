
public class TestChecking
{
	public static void main(String[] args)
	{		
		CheckingAccount personal = new CheckingAccount(500.0);
		System.out.println("beg balance = $" + personal.getBalance());

		System.out.println("\nnow writing a check!");
		personal.writeCheck(127.99);
		System.out.println("total checks = " +
                                    personal.getChecksWritten());
		System.out.println("balance = $" + personal.getBalance());

		System.out.println("\nnow closing account!");
		personal.close();
	}
}
