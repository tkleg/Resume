import java.util.function.Function;
import static java.lang.Math.*;

public class sec2_4Q2and4 {

    static final int MAX_ITER = 1000000;

    public static void main(String[] args) {
        printNewtonResult(newtonMethodModified(functions.c, functions.dc, functions.ddc, 3.5, 1e-5, MAX_ITER), "c modified");
        printNewtonResult(newtonMethod(functions.c, functions.dc, 3.5, 1e-5, MAX_ITER), "c");
        printNewtonResult(newtonMethodModified(functions.d, functions.dd, functions.ddd, 4, 1e-5, MAX_ITER), "d modified");
        printNewtonResult(newtonMethod(functions.d, functions.dd, 4, 1e-5, MAX_ITER), "d");
    }

    public static void printNewtonResult(Object result, String functionName) {
        if (result instanceof String) {
            System.out.println(result);
        } else {
            Object[] resArray = (Object[]) result;
            int iterations = (int) resArray[0];
            double root = (double) resArray[1];
            System.out.println( functionName + ") Iterations: " + iterations + ", Root: " + root);
        }
    }

    public static Object newtonMethod(Function<Double, Double> f, Function<Double, Double> df, double p0, double tol, int maxiter) {
        int i = 1;
        while (i <= maxiter) {
            double p;
            try {
                p = p0 - f.apply(p0) / df.apply(p0);
            } catch (ArithmeticException e) {
                return "Overflow Error";
            }
            if (Math.abs(p - p0) < tol) {
                return new Object[]{i, p};
            }
            i += 1;
            p0 = p;
        }
        return "Max Iterations hit";
    }

    public static Object newtonMethodModified(Function<Double, Double> f, Function<Double, Double> df, Function<Double, Double> ddf, double p0, double tol, int maxiter) {
        int i = 1;
        while (i <= maxiter) {
            double p;
            try {
                p = p0 - ( f.apply(p0) * df.apply(p0) ) / ( Math.pow( df.apply(p0), 2 ) - f.apply(p0) * ddf.apply(p0) );
            } catch (ArithmeticException e) {
                return "Overflow Error";
            }
            if (Math.abs(p - p0) < tol) {
                return new Object[]{i, p};
            }
            i += 1;
            p0 = p;
        }
        return "Max Iterations hit";
    }
}