using System.Linq;
using System.Collections.Generic;
using System;
//using System.Numerics;

class CollatzPair
{
    public int seqStart { get; set; }
    public int length { get; set; }

    public CollatzPair(int seqStart, int length)
    {
        this.seqStart = seqStart;
        this.length = length;
    }

    public override string ToString()
    {
        return $"{seqStart,20} {length,20}";
    }
}

public class csLoop{
static int Collatz(ulong num, ref int count)
{
    if ( num == 1 )
        return count;
    count++;
    if ( num % 2 == 0)
        return Collatz( num/2, ref count );
    else
        return Collatz( num * 3 + 1, ref count );
}

static void Main(string[] args)
{
    int start = int.Parse(args[0]);
    int end = int.Parse(args[1]);

    if (start > end)
        (start, end) = (end, start);

    List<CollatzPair> listj = new List<CollatzPair>(10);
    for(int x = 0 ; x < 10; x++ )
        listj.Add(new CollatzPair(0,0));
    for (int number = start; number <= end; number++)
    {
        int count = 0;
        CollatzPair newPair = new CollatzPair(number, Collatz((ulong)number, ref count));
        for( int i = 0; i < 10; i++ ){
            if (newPair.seqStart == 1){
                listj.Insert(0, newPair);
                listj.RemoveAt(listj.Count-1);
            }else if(listj[i].length == newPair.length)
                break;
            else if (listj[i].length < newPair.length){
                listj.Insert(i, newPair);
                listj.RemoveAt(listj.Count-1);
                break;
            }
        }
    }

    listj.RemoveAll(p => p.seqStart == 0);

    Console.WriteLine("Sorted based on sequence length");
    foreach (var pair in listj)
    {
        Console.WriteLine(pair);
        if( pair.seqStart == 1 )
            break;
    }

    listj.Sort((a, b) => b.seqStart.CompareTo(a.seqStart));

    Console.WriteLine("Sorted based on integer size");
    foreach (var pair in listj)
    {
        Console.WriteLine(pair);
        if( pair.seqStart == 1 )
            break;
    }
}
}