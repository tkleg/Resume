import java.util.function.Function;
import java.lang.Math.*;
import java.lang.Integer;
import java.util.ArrayList;
import java.util.Collections;

public class Algorithms{

    public static class algorithmData{
        String algorithmName;
        int iterations;
        double relError;
        double root;

        public algorithmData(String algorithmName, int iterations, double relError, double root){
            this.algorithmName = algorithmName;
            this.iterations = iterations;
            this.relError = relError;
            this.root = root;
        }

        @Override
        public String toString(){
            return algorithmName + ") Iterations: " + iterations + ", Relative Error: " + relError + ", Root: " + root;
        }
    }
    public static class iterationData{
        int iterationNum;
        double x, fx, absError, relError;

        public static final String HEADER = String.format("%-5s | %-22s | %-25s | %-26s | %-25s\n", "Iter", "x", "f(x)", "Abs Error", "Rel Error");
        public static final String SEPERATOR = new String( new char[HEADER.length()] ).replace("\0", "-");

        public iterationData(int iterationNum, double x, double fx, double absError, double relError){
            this.iterationNum = iterationNum;
            this.x = x;
            this.fx = fx;
            this.absError = absError;
            this.relError = relError;
        }

        @Override
        public String toString(){
            return String.format("%-5d | %-22.18f | %-25.20f | %-26.20e | %-25.20e", iterationNum, x, fx, absError, relError);
        }
    }

    public static final int MAX_ITER = 1000000;

    public static final double EXACT = 1.839286755214161;

    static Function<Double, Double> f = x -> {
        return Math.pow(x, 3) - x * x - x - 1;
    };

    static Function<Double, Double> df = x -> {
        return 3 * x * x - 2 * x - 1;
    };

    public static void main(String[] args) {

        ArrayList<algorithmData> results = new ArrayList<algorithmData>();

        System.out.println("Newton's Method:");
        results.add(newtonMethod(f, df, 1.5, 1e-5, MAX_ITER));
        System.out.println("Bisection Method:");
        results.add(bisectionMethod(f, 1, 2, 1e-5, MAX_ITER));
        System.out.println("Fixed Point Method:");
        results.add(fixedPointMethod(x -> x - 0.35*f.apply(x), 1.5, 1e-5, MAX_ITER));
        System.out.println("Secant Method:");
        results.add(secantMethod(f, 1, 2, 1e-5, MAX_ITER));
        System.out.println("Steffenson's Method:");
        results.add(SteffensonsMethod(x -> x + f.apply(x), 1.5, 1e-5, MAX_ITER));

        Collections.sort(results, (a, b) -> Double.compare(a.relError, b.relError));
        System.out.println("Summary (sorted by relative error):");
        results.forEach(result -> {
            System.out.println(result);
        });

        System.out.println();
        Collections.sort(results, (a, b) -> Integer.compare(a.iterations, b.iterations));
        System.out.println("Summary (sorted by iterations):");
        results.forEach(result -> {
            System.out.println(result);
        });
    }


    /*public static void printNewtonResult(Object result, String algorithm) {
        if (result instanceof String) {
            System.out.println(result);
        } else {
            Object[] resArray = (Object[]) result;
            int iterations = (int) resArray[0];
            double root = (double) resArray[1];
            System.out.println( algorithm + ") Iterations: " + iterations + ", Root: " + root);
        }
    }*/

    public static algorithmData newtonMethod(Function<Double, Double> f, Function<Double, Double> df, double p0, double tol, int maxiter) {
        ArrayList<iterationData> data = new ArrayList<iterationData>();
        data.add(new iterationData(0, p0, f.apply(p0), Math.abs(EXACT - p0), Math.abs((EXACT - p0)/EXACT)));
        int i = 1;
        double p;
        while (i <= maxiter) {
            try {
                p = p0 - f.apply(p0) / df.apply(p0);
                data.add(new iterationData(i, p, f.apply(p), Math.abs(EXACT - p), Math.abs((EXACT - p)/EXACT)));
            } catch (ArithmeticException e) {
                return new algorithmData(null, -1, -1, -1);
            }
            if (Math.abs(p - p0) < tol) {
                System.out.println(iterationData.HEADER + iterationData.SEPERATOR);
                data.forEach(dataLine -> {
                    System.out.println(dataLine);
                });
                System.out.println();
                return new algorithmData("Newton's Method", i, Math.abs(EXACT - p)/EXACT, p);
            }
            i += 1;
            p0 = p;
        }
        return new algorithmData(null, -1, -1, -1);
    }

    public static algorithmData bisectionMethod(Function<Double, Double> f, double a, double b, double tol, int maxiter) {
        ArrayList<iterationData> data = new ArrayList<iterationData>();
        int i = 1;
        double p = a;
        double fp, fa = f.apply(a);
        while (i <= maxiter) {
            p = a + (b - a) / 2;
            fp = f.apply(p);
            data.add(new iterationData(i-1, p, fp, Math.abs(EXACT - p), Math.abs((EXACT - p)/EXACT)));
            if (Math.abs(b - a) / 2 < tol || f.apply(p) == 0.0) {
                System.out.println(iterationData.HEADER + iterationData.SEPERATOR);
                data.forEach(dataLine -> {
                    System.out.println(dataLine);
                });
                System.out.println();
                return new algorithmData("Bisection Method", i, Math.abs(EXACT - p)/EXACT, p);
            }
            i += 1;
            if (fp * fa > 0) {
                a = p;
                fa = fp;
            } else {
                b = p;
            }
        }
        return new algorithmData(null, -1, -1, -1);
    }

    public static algorithmData fixedPointMethod(Function<Double, Double> g, double p0, double tol, int maxiter) {
        ArrayList<iterationData> data = new ArrayList<iterationData>();
        int i = 1;
        while (i <= maxiter) {
            double p;
            try {
                p = g.apply(p0);
                data.add(new iterationData(i-1, p, (p-p0)/-0.35, Math.abs(EXACT - p), Math.abs((EXACT - p)/EXACT)));
            } catch (ArithmeticException e) {
                return new algorithmData(null, -1, -1, -1);
            }
            if( i % 10000000 == 0 ) {
                System.out.println(p-p0);
            }
            if (Math.abs(p - p0) < tol) {
                System.out.println(iterationData.HEADER + iterationData.SEPERATOR);
                data.forEach(dataLine -> {
                    System.out.println(dataLine);
                });
                System.out.println();
                return new algorithmData("Fixed Point Method", i, Math.abs(EXACT - p)/EXACT, p);
            }
            i += 1;
            p0 = p;
        }
        return new algorithmData(null, -1, -1, -1);
    }

    public static algorithmData secantMethod(Function<Double, Double> f, double p0, double p1, double tol, int maxiter) {
        ArrayList<iterationData> data = new ArrayList<iterationData>();
        int i = 2;
        double q0 = f.apply(p0);
        double q1 = f.apply(p1);
        while (i <= maxiter) {
            double p;
            try {
                p = p1 -  q1 * (p1 - p0) / (q1 - q0);
                data.add(new iterationData(i-2, p, f.apply(p), Math.abs(EXACT - p), Math.abs((EXACT - p)/EXACT)));
            } catch (ArithmeticException e) {
                return new algorithmData(null, -1, -1, -1);
            }
            if (Math.abs(p - p1) < tol) {
                System.out.println(iterationData.HEADER + iterationData.SEPERATOR);
                data.forEach(dataLine -> {
                    System.out.println(dataLine);
                });
                System.out.println();
                return new algorithmData("Secant Method", i, Math.abs(EXACT - p)/EXACT, p);
            }
            i += 1;
            p0 = p1;
            p1 = p;
            q0 = q1;
            q1 = f.apply(p1);
        }
        return new algorithmData(null, -1, -1, -1);

    }

    public static algorithmData SteffensonsMethod(Function<Double, Double> f, double p0, double tol, int maxiter) {
        ArrayList<iterationData> data = new ArrayList<iterationData>();
        int i = 1;
        double p = 0, p1, p2;
        while (i <= maxiter) {
            try {
                p1 = f.apply(p0);
                p2 = f.apply(p1);
                p = p0 - Math.pow(p1 - p0, 2) / (p2 - 2 * p1 + p0);
                data.add(new iterationData(i-1, p, p - p1, Math.abs(EXACT - p), Math.abs((EXACT - p)/EXACT)));
            } catch (ArithmeticException e) {
                return new algorithmData(null, -1, -1, -1);
            }
            if (Math.abs(p - p0) < tol) {
                System.out.println(iterationData.HEADER + iterationData.SEPERATOR);
                data.forEach(dataLine -> {
                    System.out.println(dataLine);
                });
                System.out.println();
                return new algorithmData("Steffenson's Method", i, Math.abs(EXACT - p)/EXACT, p);
            }
            i += 1;
            p0 = p;
        }
        return new algorithmData(null, -1, -1, -1);
    }
}