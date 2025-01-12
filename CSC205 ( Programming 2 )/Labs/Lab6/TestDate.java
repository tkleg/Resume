
import java.util.*;

public class TestDate
{
	public static void main(String[] args)
	{
		Date today = new Date();
		Date holiday = new Date(2018, 9, 17);
		Date lastSunday = new Date(2018, 9, 17);
		System.out.println("today = " + today);
		System.out.println("lastSunday = " + lastSunday);
		System.out.println("holiday = " + holiday);

		if (lastSunday.equals(holiday))
			System.out.println("They are Equal!");
		else
			System.out.println("They are NOT Equal!");

		lastSunday = holiday;

		if (lastSunday == holiday)
			System.out.println("They are Equal!");
		else
			System.out.println("They are NOT Equal!");
	}
}
