import java.util.function.Function;

public class Q28Solvers {
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

    public static Object secantMethod(Function<Double, Double> f, double p0, double p1, double tol, int maxiter){
        try{
            int i = 2;
            double q0 = f.apply(p0);
            double q1 = f.apply(p1);
            while( i <= maxiter ){
                double p = p1 - q1 * (p1 - p0)/(q1 - q0);
                if( Math.abs(p-p1) < tol )
                    return new Object[]{i, p};
                i += 1;
                p0 = p1;
                q0 = q1;
                p1 = p;
                q1 = f.apply(p);
            }
            return "Max Iterations hit";
        }catch( ArithmeticException e ){
            return "Overflow Error";
        }
    }
}