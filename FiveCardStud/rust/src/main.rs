//extern crate rand;
mod card;
mod hand;
mod poker;
//use crate::hand::Hand;
use crate::card::Card;
use crate::hand::Hand;
use std::fs;
use std::env;
use std::process;
const HAND_RANKS: [&str; 10] = ["High Card","Pair","Two Pair","Three of a Kind", "Straight", "Flush", "Full House", "Four Of A Kind", "Straight Flush", "Royal Flush"];
fn main() {

    let args: Vec<String> = env::args().collect();
    let random = args.len() == 1;
    let mut cards : [Card; 52] = [Card::default(); 52];
    let mut hands : [Hand; 6] = [Hand::default(); 6];
    let mut fullFile : String = "".to_string();
    if random{
        cards = poker::getRandCards();
        hands = poker::getRandHands(cards);
    }else{
        fullFile = poker::getFullFile();
        cards = poker::padCardArray(poker::getFileCards(fullFile.clone()));
        hands = poker::getFileHands(cards);
    }
    let mut dupCard = Card::new(-1,'z');
    if !random{
        dupCard = poker::checkDupCards(hands);
    }
    let dupPresent = dupCard.value != -1;
    poker::printDeckAndHands(hands, cards, random, dupPresent, fullFile);
    if dupPresent{
        println!("{}", "\n*** ERROR - DUPLICATE CARD FOUND IN DECK ***" );
        println!("{} {} {}", "\n\n*** DUPLICATE:", dupCard.to_string(), "***");
        process::exit(0);
    }
    let originalHands : [Hand;6] = hands.clone();
    poker::sortEach(&mut hands); 
    for x in 0..6{
        poker::markCards( &mut hands[x as usize] );
        poker::getNumEachCard( &mut hands[x as usize] );
        poker::gradeHand( &mut hands[x as usize] );
    }
    let indexTracker = poker::sortHands( &mut hands );
    //printHands(hands);
    poker::printResults(hands, originalHands, indexTracker);
}
fn printHands( hands : [Hand;6] ){
    println!();
    for hand in hands{
        printHand(hand);
        print!(": {}", HAND_RANKS[hand.handRank as usize]);
        println!();
    }
}

fn printHand( hand : Hand ){
    for card in hand.myCards{
        print!("{} ", card.to_string());
    }
}

fn printMarks( hands : [Hand;6]){
    for hand in hands{
        for x in 0..4{
            for y in 0..13{
                if hand.markedCards[x as usize][y as usize]{
                    print!("{} ", "1");
                }else{
                    print!("{} ", "0");
                }
            }
            println!();
        }
        println!();
    }
}

fn printNumEachCard( hands : [Hand;6] ){
    for x in 0..6{
        for y in 0..13{
            print!("{} ", hands[x as usize].numEachCard[y as usize]);
        }
        println!("\n");
    }
}