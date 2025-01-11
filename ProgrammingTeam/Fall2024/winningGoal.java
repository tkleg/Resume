import java.util.Scanner;
import java.util.ArrayList;

public class winningGoal{

	public static void main( String[] args ){
		Scanner scan = new Scanner(System.in);
		int numGames = Integer.parseInt( scan.nextLine().split(" ")[0] );
		ArrayList<String> l = new ArrayList<String>();
		while( true ){
			String help = scan.nextLine();
			if( help.equals("*") )
				break;
			l.add( help );
		}
		String[] lines = new String[l.size()];
		for(int x = 0; x < l.size(); x++ )
			lines[x] = l.get(x);

		int counter = 0;
		Game[] games = new Game[numGames];
		int curGame = -1;
		for( String line : lines ){
			String[] splitLine = line.split(" ");
			if( line.charAt(0) == 'G' ){
				curGame++;
				games[curGame] = new Game(curGame+1, splitLine[2], splitLine[4] );
			}else{
				String team = splitLine[0];
				int teamIndex = team.equals(games[curGame].teams[0]) ? 0 : 1;
				if( games[curGame].isTied() )
					games[curGame].name = splitLine[2] + " " + splitLine[3];
				games[curGame].scores[teamIndex]++;
			}
			counter++;
		}

		for( Game game : games ){
			game.setWinner();
			System.out.println(game);
		}
	}

}

class Game{
	int gameNum;
	String[] teams;
	int[] scores;
	String name = "";

	public Game( int gameNum,  String team1, String team2 ){
		this.gameNum = gameNum;
		this.teams[0] = team1;
		this.teams[1] = team2;
	}

	public boolean isTied(){
		return scores[0] == scores[1];
	}

	public void setWinner(){
		if( scores[0] < scores[1] ){
			int tempScore = scores[0];
			scores[0] = scores[1];
			scores[1] = tempScore;

			String tempTeam = teams[0];
			teams[0] = teams[1];
			teams[1] = tempTeam;
		}
	}

	public String toString(){
		return "Game" + gameNum + ", " +teams[0]+" "+scores[0]+" "+teams[1]+" "+scores[1]+", winning goal by "+name;
	}

}
