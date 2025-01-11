//mod card;
use crate::hand::Hand;
use crate::card::Card;
use std::env;
use std::fs;
use rand::prelude::*;
use rand::Rng;
use rand::thread_rng;

const HIGH_CARD : u8 = 0;
const PAIR : u8 = 1;
const TWO_PAIR : u8 = 2;
const THREE_OF_A_KIND : u8 = 3;
const STRAIGHT : u8 = 4;
const FLUSH : u8 = 5;
const FULL_HOUSE : u8 = 6;
const FOUR_OF_A_KIND : u8 = 7;
const STRAIGHT_FLUSH : u8 = 8;
const ROYAL_FLUSH : u8 = 9;
const HAND_RANKS: [&str; 10] = ["High Card","Pair","Two Pair","Three of a Kind", "Straight", "Flush", "Full House", "Four Of A Kind", "Straight Flush", "Royal Flush"];

pub fn printResults( hands : [Hand; 6], originalHands : [Hand; 6], indexTracker : [usize;6] ){
    println!("\n --- WINNING HAND ORDER ---");
    for x in 0usize..6usize{
        let mut origIndexToPrint = indexTracker[x];
        print!(" {}", originalHands[origIndexToPrint].myCards[0].to_string());
        for y in 1usize..5usize{
            let mut handHelp = originalHands[origIndexToPrint];
            let mut cardString = String::from("");
            if y == 2 && handHelp.myCards[1].value == 8 && handHelp.myCards[0].value == 8 {
                cardString.push_str(" ");
            } else if handHelp.myCards[0].value == 8 && y == 1 && originalHands[origIndexToPrint].myCards[y].value != 8{
                cardString.push_str(" ");
            } else if originalHands[origIndexToPrint].myCards[y].value != 8{
                cardString.push_str("  ");
            } else {
                cardString.push_str(" ");
            }
            cardString.push_str(handHelp.myCards[y].to_string().as_str());
            print!("{}",cardString);
        }
        println!(" - {}", HAND_RANKS[hands[x].handRank as usize]);
    }
}

pub fn sortHands( hands : &mut [Hand;6] ) -> [usize; 6]{
    let mut indexTracker : [usize; 6] = [0;6];
    for x in 0usize..6usize{
        indexTracker[x] = x;
    }
    let mut anotherPassneeded = true;
    while anotherPassneeded{
        anotherPassneeded = false;
        for x in 0usize..5usize{
            if hands[x].losesTo(hands[x+1]){
                anotherPassneeded = true;
                let tempHand = hands[x];
                hands[x] = hands[x+1];
                hands[x+1] = tempHand;

                let tempIndex = indexTracker[x];
                indexTracker[x] = indexTracker[x+1];
                indexTracker[x+1] = tempIndex;
            }
        }
    }
    return indexTracker;
}

pub fn gradeHand( hand : &mut Hand ){
    if hand.royalFlush(){
        hand.handRank = ROYAL_FLUSH;
    } else if hand.straightFlush(){
        hand.handRank = STRAIGHT_FLUSH;
    } else if hand.fourOfAKind(){
        hand.handRank = FOUR_OF_A_KIND;
    } else if hand.fullHouse(){
        hand.handRank = FULL_HOUSE;
    } else if hand.flush(){
        hand.handRank = FLUSH;
    } else if hand.straight(){
        hand.handRank = STRAIGHT;
    } else if hand.threeOfAKind(){
        hand.handRank = THREE_OF_A_KIND;
    } else if hand.twoPair(){
        hand.handRank = TWO_PAIR;
    } else if hand.pair(){
        hand.handRank = PAIR;
    } else{
        hand.handRank = HIGH_CARD;
    }
}

pub fn checkDupCards( hands : [Hand;6] ) -> Card{
    let mut cardsFound : [[bool;13];4] = [[false;13];4];
    for i in 0..6{
        for j in 0..5{
            let mut card = hands[i].myCards[j];
            let mut sRank = card.suit_rank();
            let mut value = card.value;
            if cardsFound[sRank as usize][value as usize]{
                return card;
            }else{
                cardsFound[sRank as usize][value as usize] = true;
            }
        }
    }
    return Card::new(-1,'z');
}

pub fn padCardArray( smallCards : [Card; 30] ) -> [Card; 52]{  
    let mut cards : [Card;52] = [Card::default(); 52];
    for x in 0..30{
        cards[x as usize] = smallCards[x as usize];
    }
    cards
}

pub fn getRandCards() -> [Card; 52] {
    let mut cards: [Card; 52] = [Card::default(); 52];
    let suits = ['H','D','S','C'];
    for x in 0..4{
        for y in 0..13{
            let card = Card::new(y, suits[x as usize]);
            cards[(x*13+y) as usize] = card;
        }
    }

    let mut rng = thread_rng();

    for i in (0..cards.len()).rev() {
      let j = rng.gen_range(0..=i);
      cards.swap(i, j);
    }
    cards
}

pub fn getRandHands(cards : [Card; 52]) -> [Hand; 6] {
let mut hands: [Hand; 6] = [Hand::default(); 6];
let mut curHand = 0;
let mut numCard = 0;
/*for card in cards{
    println!("{}", card.to_string() );
}*/
for x in 0..30{
    hands[curHand as usize ].myCards[numCard as usize] = cards[x as usize];
    curHand += 1;
    if curHand == 6 {
        curHand = 0;
        numCard += 1;
    }
}
hands
}

pub fn markCards( hand : &mut Hand ){
    for x in 0..5{
        let mut sRank = hand.myCards[x as usize].suit_rank();
        hand.markedCards[sRank as usize][hand.myCards[x as usize].value as usize] = true;
    }
}

pub fn getNumEachCard( hand : &mut Hand ){
    for x in 0..5{
        hand.numEachCard[ hand.myCards[x as usize].value as usize] += 1;
    }
}

pub fn sortEach( hands : &mut [Hand;6]){
    for x in 0..6{
        let mut anotherPassneeded = true;
        while anotherPassneeded{
            anotherPassneeded = false;
            for y in 0..4{
                if hands[x as usize].myCards[y as usize].value < hands[x as usize].myCards[(y+1) as usize].value{
                    anotherPassneeded = true;
                    let mut temp = hands[x as usize].myCards[y as usize];
                    hands[x as usize].myCards[y as usize] = hands[x as usize].myCards[(y+1) as usize];
                    hands[x as usize].myCards[(y+1) as usize] = temp;
                }
            }
        }
        aceLowStraightCheck( &mut hands[x as usize]);
    }
}

pub fn aceLowStraightCheck( hand : &mut Hand ){
    if hand.myCards[0].value != 12{
        return;
    } else if hand.myCards[1].value != 3{
        return;
    } else if hand.myCards[2].value != 2{
        return;
    } else if hand.myCards[3].value != 1{
        return;
    } else if hand.myCards[4].value != 0{
        return
    }
    let mut temp = hand.myCards[0];
    for x in 0..4{
        hand.myCards[x as usize] = hand.myCards[(x+1) as usize];
    }
    hand.myCards[4] = temp;

}

pub fn printDeckAndHands( hands : [Hand;6], cards : [Card;52], random : bool, dupPresent : bool, fullFile : String){
    println!("{}","\n*** P O K E R  H A N D  A N A L Y Z E R ***\n");
    if random{
        println!("{}","\n*** USING RANDOMIZED DECK OF CARDS ***\n\n*** Shuffled 52 card deck:");
        print!("{} ", cards[0].to_string() );
        for x in 1..52{
            print!("{} ", cards[x as usize].to_string());
            if x % 13 == 0{
                println!("");
            }
        }
        println!("");
    } else{
        let args: Vec<String> = env::args().collect();
        let name = &args[1];
        print!("{}{}\n{}","\n*** USING TEST DECK ***\n\n*** File: ../../handsets/", name, fullFile);
    }
    if dupPresent {
        return;
    }
    println!("{}","\n*** Here are the six hands...");
    for x in 0..6{
        for y in 0..5{
            print!("{} ",hands[x as usize].myCards[y as usize].to_string());
        }
        println!("");
    }
    if !random{
        return;
    }
    println!("{}","\n*** Here is what remains in the deck...");
    for x in 30..52{
        print!("{} ",cards[x as usize].to_string());
    }
    println!("");
}

pub fn getFullFile() -> String{
    let args: Vec<String> = env::args().collect();
    let name = &args[1];
    let fullPath = "../../handsets/".to_string() + name;
    let filename = String::from(fullPath);

    let contents = fs::read_to_string(filename)
        .expect("Something went wrong reading the file");
    contents
}

pub fn getFileCards( fullFile : String ) -> [Card; 30]{
    let mut cards = [Card::default(); 30];
    let lines: Vec<&str> = fullFile.split("\n").collect();
    let mut counter = 0;
    for line in &lines{
        if line.is_empty(){
            continue;
        }
        let mut lineStrings: Vec<String> = line.split(",")
                                .map(|s| s.to_string())
                                .collect();
        for x in 0..5{
            lineStrings[x as usize] = lineStrings[x as usize].trim().to_string();
            //print!(":{}:", lineStrings[counter as usize]);
            //counter += 1;
            if lineStrings[x as usize].len() == 2{
                cards[counter] = Card::new(Card::value_from_char(
                    lineStrings[x as usize].chars().nth(0).unwrap()),  lineStrings[x as usize].chars().nth(1).unwrap())
                    
            }else{
                cards[counter] = Card::new(8, lineStrings[x as usize].chars().nth(2).unwrap());
            }
            counter += 1;
        }
        //println!("");
    }
    cards
}

pub fn getFileHands( cards : [Card;52] ) -> [Hand; 6] {
    let mut hands = [Hand::default(); 6];
    for i in 0..6{
        for j in 0..5{
            hands[i].myCards[j] = cards[(i*5+j) as usize];
        }
    }
    hands
}