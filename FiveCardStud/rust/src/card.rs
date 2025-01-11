#[derive(Copy, Clone)]
pub struct Card {
    pub value: i32,
    pub suit: char,
}

impl Card {
    pub fn new(value: i32, suit: char) -> Self {
        Self { value, suit }
    }

    pub fn default() -> Self{
        Card { value : 0, suit: 'z' }
    }

    pub fn suit_rank(&self) -> i32 {
        match self.suit {
            'D' => 0,
            'C' => 1,
            'H' => 2,
            'S' => 3,
            _ => -1,
        }
    }

    pub fn value_from_char(c: char) -> i32 {
        match c {
            '2' => 0,
            '3' => 1,
            '4' => 2,
            '5' => 3,
            '6' => 4,
            '7' => 5,
            '8' => 6,
            '9' => 7,
            'J' => 9,
            'Q' => 10,
            'K' => 11,
            'A' => 12,
            _ => -1,
        }
    }

    pub fn to_string(&self) -> String {
        let faces = ["2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"];
        format!("{}{}", faces[self.value as usize], self.suit)
    }
}