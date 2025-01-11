import java.util.Scanner;
import java.util.Arrays;

class exam{

public static void main( String[] args ){

	Scanner scan = new Scanner( System.in );
	String answerKey = scan.next();
	String[] answers = new String[ Integer.parseInt( scan.next() )];
	for( int x = 0; x < answers.length; x++ )
		answers[x] = scan.next();
	int[] scores = new int[ answers.length ];
	int[] correctByQuestion = new int[25];
	for( int x = 0; x < answers.length; x++ )
		for( int index = 0; index < 25; index++ )
			if( answerKey.charAt( index ) == answers[x].charAt( index ) ){
				scores[x] += 4;
				correctByQuestion[index]++;
			}
	double total = 0;
	int high = scores[0];
	for( int score : scores ){
		total += score;
		if( score > high )
			high = score;
	}
	
	Arrays.sort( scores );
	double median;
	if( scores.length % 2 == 0 ){
		double num1 = scores[ scores.length / 2 ];
		double num2 = scores[ (scores.length/2)-1 ];
		median = ( num1 + num2 ) / 2;
	}else
		median = scores[ scores.length/2 ];

	int mostCorrect = correctByQuestion[0];
	int mostCorrectIndex = 0;
	int leastCorrect = correctByQuestion[0];
	int leastCorrectIndex = 0;
	for( int x = 0; x < correctByQuestion.length; x++ ){
		if( correctByQuestion[x] > mostCorrect ){
			mostCorrect = correctByQuestion[x];
			mostCorrectIndex = x;
		}
		if( correctByQuestion[x] < leastCorrect ){
			leastCorrect = correctByQuestion[x];
			leastCorrectIndex = x;
		}
	}

	System.out.println( "High Score = " + high + "%" );
	System.out.printf( "Median Score = %.1f%s\n", median, "%" );
	System.out.println( "Question Number Answered Most Correctly = " + (mostCorrectIndex+1) );
	System.out.println( "Question Number Answered Most Incorrectly = " + ( leastCorrectIndex+1 ) );
}

}
