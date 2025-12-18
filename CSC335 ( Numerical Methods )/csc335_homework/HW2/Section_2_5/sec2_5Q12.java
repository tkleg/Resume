import java.util.ArrayList;
import java.util.function.Function;
import java.lang.Math.*;

public class sec2_5Q12 {
    

    public static void main(String[] args) {
        printResults("a", SteffensonsMethod( a, 2.5, 1e-5, 1000000) );
        printResults("b", SteffensonsMethod( b, 2.5, 1e-5, 1000000) );
        printResults("c", SteffensonsMethod( c, 0.75, 1e-5, 1000000) );
        printResults("d", SteffensonsMethod( d, 0, 1e-5, 1000000) );
    }

    public static void printResults(String equationName, Object result) {
        if (result instanceof String) {
            System.out.println(result);
        } else {
            Object[] resArray = (Object[]) result;
            int iterations = (int) resArray[0];
            double root = (double) resArray[1];
            System.out.println( equationName + ") Iterations: " + iterations + ", Root: " + root);
        }
    }

    public static Object SteffensonsMethod(Function<Double, Double> f, double p0, double tol, int maxiter) {
        int i = 1;
        double p = 0, p1, p2;
        while (i <= maxiter) {
            try {
                p1 = f.apply(p0);
                p2 = f.apply(p1);
                p = p0 - Math.pow(p1 - p0, 2) / (p2 - 2 * p1 + p0);
            } catch (ArithmeticException e) {
                return "Overflow Error";
            }
            if (Math.abs(p - p0) < tol)
                return new Object[]{i, p};
            i += 1;
            p0 = p;
        }
        return "Max Iterations hit";
    }

    static Function<Double, Double> a = x ->
        2 + Math.sin(x);

    static Function<Double, Double> b = x ->
        Math.pow(2*x + 5, 1.0/3);

    static Function<Double, Double> c = x ->
        Math.sqrt( Math.exp(x) / 3.0);

    static Function<Double, Double> d = x ->
        Math.cos(x);
}
