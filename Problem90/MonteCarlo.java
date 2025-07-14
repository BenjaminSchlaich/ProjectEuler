import java.util.Arrays;
import java.util.LinkedList;
import java.util.Random;

public class MonteCarlo {

    public static int total = 44100;

    public static final LinkedList<Character> cs = new LinkedList<>(Arrays.asList('0','1','2','3','4','5','6','7','8','9'));

    public static LinkedList<LinkedList<Character>> genAllCubes(int remaining, int digit)
    {
        LinkedList<LinkedList<Character>> ac = new LinkedList<>();

        LinkedList<Character> can = new LinkedList<>(cs);

        for(int i=0; i<digit; i++)
            can.removeFirst();
        
        if(can.size() < remaining || remaining == 0)
            return ac;
        else if(can.size() == remaining)
            ac.add(can);
        else
        {
            ac = genAllCubes(remaining - 1, digit + 1);

            for(LinkedList<Character> l: ac)
                l.addFirst(Integer.toString(digit).charAt(0));
            
            if(ac.size() == 0)
            {
                LinkedList<Character> l0 = new LinkedList<>();
                l0.add(Integer.toString(digit).charAt(0));
                ac.add(l0);
            }
            
            ac.addAll(genAllCubes(remaining, digit + 1));
        }
        
        return ac;
    }

    public static void monteCarlo()
    {
        Random r = new Random();

        int T = 10000000;
        
        int satisfied = 0;

        for(int t=0; t<T; t++)
        {
            LinkedList<Character> s0 = new LinkedList<>(cs);
            LinkedList<Character> s1 = new LinkedList<>(cs);

            // select randomly by removing randomly
            for(int i=0; i<4; i++)
            {
                int x = r.nextInt(s0.size());
                int y = r.nextInt(s1.size());

                s0.remove(x);
                s1.remove(y);
            }

            // check whether all squares below 100 can be built
            if(satisfies(s0, s1))
                satisfied++;
        }

        System.out.println("In total there are " + total + " ways of choosing the two dice.");
        System.out.println("Out of " + T + " random samples " + satisfied + " satisfied the conditions.");

        double d = ((double) satisfied) / T;

        System.out.println("This makes up " + d * 100 + " percent.");
        System.out.println ("Therefore we can expect (n*p) " + (int) Math.round(d * total) + " arrangements.");
    }

    public static boolean satisfies(LinkedList<Character> s0, LinkedList<Character> s1)
    {
        // prepare the list of squares below 100
        LinkedList<String> squares = new LinkedList<>();
        for(int i=1; i<10; i++)
        {
            String sq = Integer.toString(i*i);

            if(sq.length() == 1)
                sq = "0" + sq;
            
            squares.add(sq);
        }

        for(String sq: squares)
            {
                if(!(
                    s0.contains(sq.charAt(0)) && s1.contains(sq.charAt(1)) ||
                    s0.contains(sq.charAt(1)) && s1.contains(sq.charAt(0))
                ))
                    return false;
            }
        
        return true;
    }
    
    public static void main(String[] args)
    {
        LinkedList<LinkedList<Character>> ac0 = genAllCubes(6, 0);
        // LinkedList<LinkedList<Character>> ac1 = genAllCubes(6, 0);

        // our variation allows the 6 = 9 rule
        for(LinkedList<Character> l: ac0)
        {
            if(l.contains('6') && !l.contains('9'))
                l.add('9');
            
            if(l.contains('9') && !l.contains('6'))
                l.add('6');
        }

        int count = 0;

        /**
        for(LinkedList<Character> l0: ac0)
        {
            for(LinkedList<Character> l1: ac1)
            {
                if(satisfies(l0, l1))
                    count++;
            }
        }
         */

        // count uniquely
        for(int i=0; i<ac0.size(); i++)
        {
            for(int j=i+1; j<ac0.size(); j++)
            {
                if(satisfies(ac0.get(i), ac0.get(j)))
                {
                    count++;

                    System.out.println("{" + ac0.get(i) + " -- " + ac0.get(j) + "}");
                }
            }
        }

        System.out.println("Satisfying: " + count + " / " + total + " = " + ((double) count)/total);
    }

    // 01, 04, 09, 16, 25, 36, 49, 64, 81

}
