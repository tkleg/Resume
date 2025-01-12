use std::env;
use std::fs;

#[derive (Clone, Debug, Copy)]
struct CPair{
    pub seqStart: u32,
    pub length: u32,
}

impl CPair{
    pub fn new(seqStart: u32, length: u32) -> Self{
        Self { seqStart, length }
    }
    pub fn default() -> Self{
        CPair { seqStart: 0, length: 0 }
    }
    pub fn toString(pair: CPair) -> String {
        return format!("{:>20} {:>20}", pair.seqStart, pair.length);
    }
}

fn collatz( num : u128, counter : &mut u32 ) -> u32{
    if num == 1{
        return *counter;
    }
    *counter += 1;
    if num % 2 == 0{
        return collatz(num/2, counter);
    }else{
        return collatz(num*3+1, counter);
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let Sstart = &args[1];
    let Send = &args[2];
    let mut start: usize = Sstart.parse().expect("Not a number!");
    let mut end: usize = Send.parse().expect("Not a number!");
    if start > end{
        (start, end) = (end, start)
    }
    
    let mut listj: Vec<CPair> = vec![CPair::default(); 10];
    for number in start..end+1{
        let mut counter : u32 = 0;
        let mut newPair : CPair = CPair::new( number as u32, collatz(number as u128, &mut counter) );
        for i in 0..10{
            if newPair.seqStart == 1{
                listj.insert(0, newPair);
                listj.pop();
                break;
            }
            else if listj[i].length == newPair.length{
                break;
            }else if listj[i].length < newPair.length{
                listj.insert(i, newPair);
                listj.pop();
                break;
            }
        }
    }
        while listj[listj.len()-1].seqStart == 0{
            listj.pop();
        }

        println!("Sorted based on sequence length");
        for pair in listj.iter(){
            println!("{}", CPair::toString(*pair));
        }

        let mut anotherPassNeeded : bool = true;
        while anotherPassNeeded{
            //println!("sort iter");
            anotherPassNeeded = false;
            for i in 0..listj.len()-1{
                if listj[i].seqStart < listj[i+1].seqStart{
                    anotherPassNeeded = true;
                    let mut temp = listj[i];
                    listj[i] = listj[i+1];
                    listj[i+1] = temp;
                }
            }
        }

        println!("Sorted based on integer size");
        for pair in listj.iter(){
		println!("{}", CPair::toString(*pair));
        }


}
