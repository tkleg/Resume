import java.io.PrintWriter;
import java.math.BigDecimal;
import java.math.MathContext;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.Collector;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.stream.Collectors;
import java.util.List;

public class Fibs{

    public static final BigDecimal SQRT5 = sqrt5();

    public static final String DECIMAL_EXTENDER = ".0";

    public enum MATHEMATICA_STRINGS {
        FIB_5("5" + DECIMAL_EXTENDER),
        FIB_10("55" + DECIMAL_EXTENDER),
        FIB_20("6765" + DECIMAL_EXTENDER),
        FIB_50("12586269025" + DECIMAL_EXTENDER),
        FIB_100("354224848179261915075" + DECIMAL_EXTENDER),
        FIB_150("9969216677189303386214405760200" + DECIMAL_EXTENDER),
        FIB_500("139423224561697880139724382870407283950070256587697307264108962948325571622863290691557658876222521294125" + DECIMAL_EXTENDER),
        FIB_1450("481496750250011136428843571903967081463488874846314827219887914560410643881950301258052067445040606537505445337730931321003621678926140591263467695247836877739842986829023011443446962382567319797291217068990256207415422421635642952339494141165239234107295736899191170326343890944201012061648917274457975" + DECIMAL_EXTENDER);

        private final String value;

        MATHEMATICA_STRINGS(String value) {
            this.value = value;
        }

        public String getValue() {
            return value;
        }
    }

    public static void main(String[] args) throws FileNotFoundException, IOException{

        String formatString = "%-8s | %-16s | %-23s | %-15s | %-7s\n";
        String[] headers = new String[]{"n", "32-bit precision", "64-bit precision", "32-bit accuracy", "64-bit accuracy"};

        String header = String.format(formatString, (Object[]) headers);
        System.out.print(header);
        for( int x = 0; x < header.length(); x++ )
            System.out.print("-");
        System.out.println();

        List<List<String>> results = new ArrayList<>();
        for( int n : new int[]{5, 10, 20, 50, 100, 150, 500, 1450}){
            BigDecimal thirtySecond = nth_fib(n, 32);
            String accurateDigits32 = getAccurateDigits( 
                thirtySecond.toPlainString(), MATHEMATICA_STRINGS.valueOf("FIB_" + n).getValue());
            String formatted32 = formattedBigDecimal(thirtySecond);

            BigDecimal sixtyFourth = nth_fib(n, 64);
            String accurateDigits64 = getAccurateDigits(
                sixtyFourth.toPlainString(), MATHEMATICA_STRINGS.valueOf("FIB_" + n).getValue());
            String formatted64 = formattedBigDecimal(sixtyFourth);

            List<String> iterationResults = new ArrayList<String>(
                Arrays.asList(
                    formatted32, formatted64, accurateDigits32, accurateDigits64)
            );
            results.add(iterationResults);
            System.out.printf(formatString, n, 
                cut0sAndPeriod(thirtySecond.toString()), cut0sAndPeriod(sixtyFourth.toString()), 
                accurateDigits32, accurateDigits64 );

        }

        File output = new File("FibsOutput.csv");
        if( output.exists() )
            output.delete();
        output.createNewFile();
        PrintWriter pw = new PrintWriter(output);
        pw.println( String.join(",", headers) );
        results.stream().forEach( row -> pw.println( String.join(",", row) ) );
        pw.close();
    }

    private static String cut0sAndPeriod( String s ){
        if( (! s.contains(".")) || s.contains("E") )
            return s;   
        while( s.charAt( s.length() - 1 ) == '0' )
            s = s.substring(0, s.length() - 1);
        if( s.charAt( s.length() - 1 ) == '.' )
            s = s.substring(0, s.length() - 1);
        return s;
    }

    private static String getAccurateDigits( String computed, String expected ){
        //Ensures the two strings have the same length. Extends the shorter one with 0s
        if( computed.length() < expected.length() )
            computed += new String( new char[ expected.length() - computed.length() ] ).replace("\0", "0");
        else
            expected += new String( new char[ computed.length() - expected.length() ] ).replace("\0", "0");

        if( computed.equals(expected) )
            return "=";

        int accurateDigits = 0;
        for( int i = 0; i < computed.length(); i++ ){
            if( computed.charAt(i) == expected.charAt(i) )
                accurateDigits++;
            else
                return ""+accurateDigits;
        }
        return null;// never returns, satisfies compiler requirement for return
    }


    private static String formattedBigDecimal( BigDecimal bd ){
        return cut0sAndPeriod(bd.toPlainString());
    }

    //Researched online approximations for square root and found an algorithm at https://www.geeksforgeeks.org/dsa/find-root-of-a-number-using-newtons-method/
    //I modified it to work with BigDecimal
    //This gives around 90 digits of accuracy after manually looking at the value
    public static BigDecimal sqrt5() 
    { 
        //140 was picked by manually picking numbers until I found the largest number that would not take a while to compute
        MathContext sqrt5Limit = new MathContext(140);
        
        BigDecimal tolerance = new BigDecimal("1E-100", MathContext.UNLIMITED);

        BigDecimal x = BigDecimal.valueOf(5L); 

        BigDecimal n = BigDecimal.valueOf(5L);

        BigDecimal root; 

        BigDecimal oneHalf = new BigDecimal("0.5", MathContext.UNLIMITED);

        while (true)
        {
            root = oneHalf.multiply(x.add(n.divide(x, sqrt5Limit), MathContext.UNLIMITED), MathContext.UNLIMITED);

            if (root.subtract(x, MathContext.UNLIMITED).abs().compareTo(tolerance) < 0)
                break;
    
            x = root; 
        } 
    
        return root; 
    } 

    
    public static BigDecimal nth_fib(int n, int precision){
        MathContext mc = null;
        switch (precision) {
            case 32:
                mc = MathContext.DECIMAL32;
                break;
            case 64:
                mc = MathContext.DECIMAL64;
                break;
        }
        BigDecimal firstTerm = BigDecimal.ONE.add(SQRT5, mc).divide(new BigDecimal(2), mc).pow(n, mc);
        BigDecimal secondTerm = BigDecimal.ONE.subtract(SQRT5, mc).divide(new BigDecimal(2), mc).pow(n, mc);
        return firstTerm.subtract(secondTerm, mc).divide(SQRT5, mc);
    }


}