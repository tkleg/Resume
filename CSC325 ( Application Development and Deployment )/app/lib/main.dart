import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'TicTacToe',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSwatch(primarySwatch: Colors.deepPurple),
      ),
      home: const MyHomePage(title: 'TicTacToe'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

enum Turns { Xturn, Oturn }

class _MyHomePageState extends State<MyHomePage> {
  
  List<IconData> currIcons = List.filled(9, Icons.square); // Initialize currIcons
  Turns currTurn = Turns.Xturn; // Correct enum usage
  String currTurnString = "X";
  String headerText = "Current Turn: ";
  bool gameOver = false;

  void changeIconAndTurn(int index, Turns who) {
    if (currIcons[index] != Icons.square) return;
    if (who == Turns.Xturn)
      currIcons[index] = Icons.clear_outlined;
    else
      currIcons[index] = Icons.circle_outlined;

    // Toggle turns
    currTurn = (currTurn == Turns.Xturn) ? Turns.Oturn : Turns.Xturn;
    currTurnString = (currTurn == Turns.Xturn) ? "X" : "O";
  }

void checkEndGame(){
  for( int x = 0; x < 9; x++ ){//check for a tie
    if( currIcons[x] == Icons.square )
      break;
    if( x == 8 ){
      gameOver = true;
      headerText = "It's a Tie!";
    }
  }
  if( checkWin(Icons.clear_outlined) ){//Did X win
      gameOver = true;
      headerText = "X is the Winner, Congrats!";
  }else if( checkWin(Icons.circle_outlined) ){//Did O win
      gameOver = true;
      headerText = "O is the Winner, Congrats!";
  }

}

bool checkWin( IconData d ){
  if( currIcons[0] == d && currIcons[3] == d && currIcons[6] == d )
    return true;
  else if( currIcons[1] == d && currIcons[4] == d && currIcons[7] == d ) 
    return true;
  else if( currIcons[2] == d && currIcons[5] == d && currIcons[8] == d )
    return true;
  else if( currIcons[0] == d && currIcons[1] == d && currIcons[2] == d )
    return true;
  else if( currIcons[3] == d && currIcons[4] == d && currIcons[5] == d ) 
    return true;
  else if( currIcons[6] == d && currIcons[7] == d && currIcons[8] == d )
    return true;
  else if( currIcons[0] == d && currIcons[4] == d && currIcons[8] == d ) 
    return true;
  else if( currIcons[2] == d && currIcons[4] == d && currIcons[6] == d )
    return true;
  else
  return false; 
}

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: (!gameOver) ? SingleChildScrollView(
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(
                "Current Turn: $currTurnString",
                style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
              ),
              SizedBox(height: 20),
              Container(
                width: 350,
                height: 350,
                child: GridView.count(
                  crossAxisCount: 3,
                  shrinkWrap: true,
                  padding: EdgeInsets.zero,
                  children: List.generate(9, (index) {
                    return SizedBox(
                      width: 50,
                      height: 50,
                      child: ElevatedButton(
                        onPressed: () {
                          changeIconAndTurn(index, currTurn);
                          checkEndGame();
                          setState((){});
                        },
                        child: Icon(currIcons[index], size: 50),
                      ),
                    );
                  }),
                ),
              ),
            ],
          ),
        ),
      )
      : Center(
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [ 
                    Text(
                    headerText,
                    style: TextStyle(fontSize: 24),
                    ),
                    Text( "Refresh the page to play again.",
                      style: TextStyle(fontSize: 24)
                    ),
                  ],
                ),
      ),
    );
  }
}