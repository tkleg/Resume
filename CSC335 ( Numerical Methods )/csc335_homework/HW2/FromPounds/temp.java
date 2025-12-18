import java.util.function.Function;

public class temp {
    public static void main(String[] args) {
        Function<Double, Double> f = x -> {
            return Math.pow(x, 3) + 3 * x + 10;
        };
        Function<Double, Double> g = x -> Math.cbrt(-2 * x - 10);
        System.out.println(Algorithms.fixedPointMethod(g, -2, 1e-5, 100000000));
        //System.out.println(Algorithms.fixedPointMethod(f, -2, 1e-5, 100000000));
        f = x -> Math.pow(x, 3) + 2*x + 10;
        System.out.println(Algorithms.bisectionMethod(f, -2, -1, 1e-5, 100000000));
        System.out.println(Algorithms.newtonMethod(f, x -> 3*Math.pow(x, 2) + 2, -2, 1e-10, 100000000));
    }
}