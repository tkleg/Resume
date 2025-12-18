import java.util.function.Function;

public class sec2_3Q28 {
    
    public static void main(String[] args) {
        Function<Double, Double> c_toSolve = t -> Math.E / 3 * t * Math.exp(-t / 3) - 0.25;
        Function<Double, Double> c_dt = t -> Math.E / 3 * Math.exp(-t / 3) * (1 - t / 3);

        Object bResultNewton = Q28Solvers.newtonMethod(c_toSolve, c_dt, 10.0, 1e-5, 10000);
        Object bResultSecant = Q28Solvers.secantMethod(c_toSolve, 10.0, 12.0, 1e-5, 10000);
        System.out.println("Using Newton's Method:");
        double bRootNewton = (double) ((Object[]) bResultNewton)[1];
        if (bResultNewton instanceof Object[]) {
            int iterations = (int) ((Object[]) bResultNewton)[0];
            System.out.println("Iterations: " + iterations + ", Root: " + bRootNewton + " hours" + " or " + bRootNewton * 60 + " minutes");
        } else {
            System.out.println(bResultNewton);
        }
        
        System.out.println("Using Secant Method:");
        double bRootSecant = (double) ((Object[]) bResultSecant)[1];
        if (bResultSecant instanceof Object[]) {
            int iterations = (int) ((Object[]) bResultSecant)[0];
            System.out.println("Iterations: " + iterations + ", Root: " + bRootSecant + " hours" + " or " + bRootSecant * 60 + " minutes");
        } else {
            System.out.println(bResultSecant);
        }

        Function<Double, Double> c_t_3rdInjection = c_3rdInjection(bRootNewton);
        Function<Double, Double> c_t_3rdInjection_dt = c_3rdInjection_dt(bRootNewton);
        Object result2 = Q28Solvers.newtonMethod(c_t_3rdInjection, c_t_3rdInjection_dt, 5.0, 1e-5, 10000);
        if (result2 instanceof Object[]) {
            int iterations2 = (int) ((Object[]) result2)[0];
            double root2 = (double) ((Object[]) result2)[1];
            System.out.println("Iterations: " + iterations2 + ", Root: " + root2 + " hours" + " or " + root2 * 60 + " minutes");
        } else
            System.out.println(result2);
        
    }

    public static Function<Double, Double> c_3rdInjection( double time2ndInjection) {
        return t -> 0.25 + Math.E/3 * (t - time2ndInjection) * Math.exp(-(t - time2ndInjection) / 3)
        + Math.E/4 * (t - time2ndInjection) * Math.exp( - t / 3 );
    }

    public static Function<Double, Double> c_3rdInjection_dt( double time2ndInjection) {
        return t -> ((t - time2ndInjection) * Math.exp(1 - (t - time2ndInjection) / 3) ) / 3 +
            t * Math.exp( 1 - t / 3 ) / 4 + 0.25;
    }
}