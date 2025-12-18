import java.util.function.Function;
import static java.lang.Math.*;

public class functions{
    static Function<Double, Double> c = x -> {
        return Math.sin(3 * x)
        + 3 * Math.exp(-2 * x) * Math.sin(x)
        - 3 * Math.exp(-x) * Math.sin(2*x)
        - Math.exp(-3*x);
    };

    static Function<Double, Double> dc = x -> {
        return 3 * Math.cos(3*x)
        + 3 * Math.exp(-x) * sin(2*x)
        - 6 * Math.exp(-x) * Math.cos(2*x)
        - 6 * Math.exp(-2*x) * Math.sin(x)
        + 3 * Math.exp(-2*x) * Math.cos(x)
        + 3 * Math.exp(-3*x);
    };

    static Function<Double, Double> ddc = x -> {
        return -9 * Math.sin(3*x)
        + 3 * ( -Math.exp(-x) * Math.sin(2*x) +
            Math.exp(-x) * 2 * Math.cos(2*x)
            )
        - 6 * ( -Math.exp(-x) * Math.cos(2*x) -
            Math.exp(-2*x) * 2 * Math.sin(2*x)
            )
        - 6 * ( -2 * Math.exp(-2*x) * Math.sin(x) +
            Math.exp(-2*x) * Math.cos(x)
            )
        + 3 * ( -2 * Math.exp(-2*x) * Math.cos(x) -
            Math.exp(-2*x) * Math.sin(x)
            )
        - 9 * Math.exp(-3*x);
    };

    static Function<Double, Double> d = x -> {
        return Math.exp(3*x)
        - 27 * Math.pow( x, 6 )
        + 27 * Math.pow( x, 4 ) * Math.exp(x)
        - 9 * x * x * Math.exp(2*x);
    };

    static Function<Double, Double> dd = x -> {
        return 3 * Math.exp(3*x)
        - 162 * Math.pow(x, 5)
        + 108 * Math.pow(x, 3) * Math.exp(x)
        + 27 * Math.pow(x, 4) * Math.exp(x)
        - 18 * x * Math.exp(2*x)
        - 18 * x * x * Math.exp(2*x);
    };

    static Function<Double, Double> ddd = x -> {
        return 9 * Math.exp(3*x)
        - 810 * Math.pow(x, 4)
        + 324 * Math.pow(x, 2) * Math.exp(x)
        + 216 * Math.pow(x, 3) * Math.exp(x)
        + 27 * Math.pow(x, 4) * Math.exp(x)
        - 18 * Math.exp(2*x)
        - 72 * x * Math.exp(2*x)
        - 36 * x * x * Math.exp(2*x);
    };
}