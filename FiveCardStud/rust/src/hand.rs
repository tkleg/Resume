//extern crate rand;

use crate::card::Card;
use std::fs::File;
use std::io::{BufRead, BufReader, Error};
use std::path::Path;

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

#[derive(Copy, Clone)]
pub struct Hand {
    pub myCards: [Card; 5],
    pub markedCards: [[bool; 13]; 4],
    pub numEachCard: [u8; 13],
    pub handRank: u8,
    pub flushSuit: i32,
    pub kickerSuit: i32,
    pub kickerValue: i32,
    pub pairHighSuit: u8,
    pub valueOfTriple: u8,
    pub fourKindVal: u8,
    pub pairValue: u8,
    pub twoPairValue: u8,
    pub doubleCardVal: u8,
}
impl Hand{
    pub fn default() -> Self{
        Hand{
            myCards: [Card::default(); 5],
            markedCards: [[false; 13]; 4],
            numEachCard: [0; 13],
            handRank: 0,
            flushSuit: 0,
            kickerSuit: 0,
            kickerValue: 0,
            pairHighSuit: 0,
            valueOfTriple: 0,
            fourKindVal: 0,
            pairValue: 0,
            twoPairValue: 0,
            doubleCardVal: 0,
        }
    }

    pub fn losesTo( self, hand2 : Hand ) -> bool{
        if self.handRank != hand2.handRank {
            return self.handRank < hand2.handRank;
        } else if self.handRank == HIGH_CARD{
            for x in 0usize..5usize{
                if self.myCards[x].value != hand2.myCards[x].value{
                    return self.myCards[x].value < hand2.myCards[x].value;
                }
            }
            return self.myCards[0].suit_rank() < hand2.myCards[0].suit_rank();
        } else if self.handRank == PAIR{
            if self.pairValue != hand2.pairValue{
                return self.pairValue < hand2.pairValue;
            }
            for x in 0usize..5usize{
                if self.myCards[x].value != hand2.myCards[x].value{
                    return self.myCards[x].value < hand2.myCards[x].value;
                }
            }
            return self.kickerSuit < hand2.kickerSuit;
        } else if self.handRank == TWO_PAIR{
            if self.twoPairValue != hand2.twoPairValue{
                return self.twoPairValue < hand2.twoPairValue;
            } else if self.pairValue != hand2.pairValue{
                return self.pairValue < hand2.pairValue;
            } else if self.kickerValue != hand2.kickerValue{
                return self.kickerValue < hand2.kickerValue;
            } else{
                return self.kickerSuit < hand2.kickerSuit;
            }
        } else if self.handRank == THREE_OF_A_KIND{
            return self.valueOfTriple < hand2.valueOfTriple;
        } else if self.handRank == STRAIGHT{
            if self.myCards[0].value != hand2.myCards[0].value{
                return self.myCards[0].value < hand2.myCards[0].value;
            }
            return self.myCards[0].suit_rank() < hand2.myCards[0].suit_rank();
        } else if self.handRank == FLUSH{
            for x in 0usize..5usize{
                if self.myCards[x].value != hand2.myCards[x].value{
                    return self.myCards[x].value < hand2.myCards[x].value;
                }
            }
            return self.flushSuit < hand2.flushSuit;
        } else if self.handRank == FULL_HOUSE{
            return self.valueOfTriple < hand2.valueOfTriple;
        } else if self.handRank == FOUR_OF_A_KIND{
            return self.fourKindVal < hand2.fourKindVal;
        } else if self.handRank == STRAIGHT_FLUSH{
            if self.myCards[0].value != hand2.myCards[0].value{
                return self.myCards[0].value < hand2.myCards[0].value;
            }
            return self.myCards[0].suit_rank() < hand2.myCards[0].suit_rank(); 
        } else {
            return self.flushSuit < hand2.flushSuit;
        }
    }

    pub fn royalFlush(&mut self) -> bool {
        for x in 0u8..4u8{
            for y in 8u8..14u8{
                if y == 13{
                    self.flushSuit = x as i32;
                    return true;
                }
                if ! self.markedCards[x as usize][y as usize]{
                    break;
                }
            }
        }
        return false
    }
    
    pub fn straightFlush(&mut self) -> bool {
        for x in 0u8..4u8{
            let mut curConsecutive = 0;
            for y in 0u8..13u8{
                if curConsecutive == 5{
                    self.flushSuit = x as i32;
                    return true;
                } else if self.markedCards[x as usize][y as usize]{
                    curConsecutive += 1;
                } else{
                    curConsecutive = 0;
                }
            }
        }

        if self.myCards[4].value != 12{
            return false;
        }
        let potentialSuit = self.myCards[4].suit;
        for x in 0u8..4u8{
            if self.myCards[x as usize].value != (3-x as i32) || potentialSuit != self.myCards[x as usize].suit{
                return false;
            }
        }
        return true;
    }
    pub fn fourOfAKind(&mut self) -> bool {
        for x in 0u8..13u8{
            if self.numEachCard[x as usize] == 4{
                self.fourKindVal = x;
                return true;
            }
        }
        return false;
    }
    pub fn fullHouse(&mut self) -> bool {
        let mut tripleFound = false;
        let mut doubleFound = false;
        for x in 0u8..13u8{
            if self.numEachCard[x as usize] == 3{
                self.valueOfTriple = x;
                tripleFound = true;
            } else if self.numEachCard[x as usize] == 2{
                self.doubleCardVal = x;
                doubleFound = true;
            }
            if doubleFound && tripleFound{
                return true;
            }
        }
        return false;
    }

    pub fn straight(&mut self) -> bool {
        let mut curConsecutive = 0;
        for y in 0u8..13u8{
            if curConsecutive == 5{
                return true;
            } else if self.numEachCard[y as usize] == 1{
                curConsecutive += 1;
            } else {
                curConsecutive = 0;
            }
        }
        if self.myCards[4].value != 12{
            return false;
        }
        for x in 0i32..4i32{
            if self.myCards[x as usize].value != (3-x){
                return false;
            }
        }
        return true;
    }

    pub fn flush(&mut self) -> bool {
        let potentialSuit = self.myCards[0].suit;
        for x in 0usize..5usize{
            if self.myCards[x].suit != potentialSuit{
                return false;
            }
        }
        self.flushSuit = self.myCards[0].suit_rank();
        return true;
    }

    pub fn threeOfAKind(&mut self) -> bool {
        for x in 0u8..13u8{
            if self.numEachCard[x as usize] == 3{
                self.valueOfTriple = x;
                return true;
            }
        }
        return false;
    }

    pub fn twoPair(&mut self) -> bool {
        let mut pairFound = false;
        for x in 0u8..13u8{
            if self.numEachCard[x as usize] > 1{
                if pairFound{
                    self.twoPairValue = x;
                    self.markKicker();
                    if self.twoPairValue < self.pairValue{
                        let temp = self.pairValue;
                        self.pairValue = self.twoPairValue;
                        self.twoPairValue = temp;
                    }
                    return true;
                } else {
                    self.pairValue = x;
                    pairFound = true;
                }
            }
        }
        return false;
    }
    pub fn markKicker(&mut self){
        for x in 0i32..13i32{
            if self.numEachCard[x as usize] == 1{
                for y in 0usize..5usize{
                    if self.myCards[y].value == x{
                        self.kickerSuit = self.myCards[y].suit_rank();
                        self.kickerValue = self.myCards[y].value;
                        return;
                    }
                }
            }
        }
    }

    pub fn pair(&mut self) -> bool {
        for x in 0u8..13u8{
            if self.numEachCard[x as usize] == 2{
                let mut suitHighCardNoPair = -1;
                let mut valueHighCardNoPair = -1;
                for y in 0usize..5usize{
                    if self.numEachCard[self.myCards[y].value as usize] == 1 && valueHighCardNoPair < self.myCards[y].value {
                        valueHighCardNoPair = self.myCards[y].value;
                        suitHighCardNoPair = self.myCards[y].suit_rank();
                    }
                }
                self.kickerSuit = suitHighCardNoPair;
                self.kickerValue = valueHighCardNoPair;
                self.pairValue = x;
                return true
            }
        }
        return false;
    }
}