import java.util.function.Function;

public class sec2_3Q29 {

    static double A, B, C, E;

    public static void setConstants(double l, double h, double D, double beta) {
        double betaRadians = Math.toRadians(beta);
        double betaSin = Math.sin(betaRadians), betaCos = Math.cos(betaRadians), betaTan = Math.tan(betaRadians);
        A = l * betaSin;
        B = l * betaCos;
        double C1 = ( h + 0.5 * D ) * betaSin;
        double C2 = 0.5 * D * betaTan;
        C = C1 - C2;
        E = ( h + 0.5 * D ) * betaCos - 0.5 * D;
    }

    public static void main(String[] args) {
        System.out.println();
        
        int l = 89, h = 49, D = 55;
        double beta = 11.5;
        setConstants(l, h, D, beta);
        Function<Double, Double> fA = angleFunction();
        Function<Double, Double> dfA = angleDerivativeFunction();

        Object newtonResult = Q28Solvers.newtonMethod(fA, dfA, 0.5, 1e-16, 1000000);
        int iterations = (int) ((Object[]) newtonResult)[0];
        double angle = Math.toDegrees((double) ((Object[]) newtonResult)[1]);
        System.out.println("Newton's Method Part A:");
        System.out.println("Iterations: " + iterations + ", Angle: " + angle + " degrees\n");

        Object secantResult = Q28Solvers.secantMethod(fA, 0, 1, 1e-16, 1000000);
        iterations = (int) ((Object[]) secantResult)[0];
        angle = Math.toDegrees((double) ((Object[]) secantResult)[1]);
        System.out.println("Secant Method Part A:");
        System.out.println("Iterations: " + iterations + ", Angle: " + angle + " degrees\n");

        D = 30;
        setConstants(l, h, D, beta);
        Function<Double, Double> fB = angleFunction();
        Function<Double, Double> dfB = angleDerivativeFunction();
        newtonResult = Q28Solvers.newtonMethod(fB, dfB, 0.5, 1e-16, 1000000);
        iterations = (int) ((Object[]) newtonResult)[0];
        angle = Math.toDegrees((double) ((Object[]) newtonResult)[1]);
        System.out.println("Newton's Method Part B:");
        System.out.println("Iterations: " + iterations + ", Angle: " + angle + " degrees\n");

        secantResult = Q28Solvers.secantMethod(fB, 0, 1, 1e-14, 1000000);
        iterations = (int) ((Object[]) secantResult)[0];
        angle = Math.toDegrees((double) ((Object[]) secantResult)[1]);
        System.out.println("Secant Method Part B:");
        System.out.println("Iterations: " + iterations + ", Angle: " + angle + " degrees\n");

    }

    public static Function<Double, Double> angleFunction() {

        return x -> {
            double cos = Math.cos(x);
            double sin = Math.sin(x);
            return 
                A * sin * cos
                + B * Math.pow(sin, 2)
                - C * cos
                - E * sin;
        };
    }

    public static Function<Double, Double> angleDerivativeFunction() {

        return x -> {
            double cos = Math.cos(x);
            double sin = Math.sin(x);
            return 
                A * ( Math.pow( cos, 2) - Math.pow( sin, 2) )
                + B * 2 * sin * cos
                - C * -sin
                - E * cos;
        };
    }

}
