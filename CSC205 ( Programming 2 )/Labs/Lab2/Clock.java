public class Clock{

	private int hours, minutes, seconds;

	public Clock(){
		hours = 0;
		minutes = 0;
		seconds = 0;
	}

	public Clock( int hours, int minutes, int seconds ){
		this.hours = hours;
		this.minutes = minutes;
		this.seconds = seconds;
	}

	public void reset(){
		hours = 0;
		minutes = 0;
		seconds = 0;
	}

	public void reset( int hours, int minutes, int seconds ){
		this.hours = hours;
		this.minutes = minutes;
		this.seconds = seconds;
	}

	public void advance(){
		seconds++;
		if( seconds > 59 ){
			minutes++;
			seconds = 0;
			if( minutes > 59 ){
				hours++;
				minutes = 0;
				hours = ( hours > 23 ) ? 0 : hours;
			}
		}
	}

	public String toString(){
		String output = ( hours < 10 ) ? "0"+hours+":" : hours+":";
		output += ( minutes < 10 ) ? "0"+minutes+":" : minutes+":";
		output += ( seconds < 10 ) ? "0"+seconds : seconds;
		return output;
	}

}
