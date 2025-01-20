import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';

import 'package:app/main.dart';

void main() {
  testWidgets("Tic Tac Toe - Turn change test", (WidgetTester tester) async {
    // Build our app and trigger a frame.
    await tester.pumpWidget(const MyApp());

    final allButtons = tester.widgetList(find.byType(ElevatedButton));
    for( int i = 0 ; i <= 6; i++ ){//the game is one after the 7th button is clicked every time
      
      String turnString = (i%2 == 0) ? "Current Turn: X" : "Current Turn: O";
      expect(find.text(turnString), findsOneWidget);
      
      final button = allButtons.toList()[i];
      final buttonFinder = find.byWidget(button);
      await tester.tap(buttonFinder);
      await tester.pump();
    }
    expect(find.text("X is the Winner, Congrats!"), findsOneWidget);
    expect(find.text("Refresh the page to play again."), findsOneWidget);

  });
}
