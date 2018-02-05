import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	
	public static int process(BigInteger n)
	{
		BigInteger k = new BigInteger("100000000");
		BigInteger m = n.mod(k);
		String s = m.toString();
		int a = Integer.parseInt(s);
		a += 256;
		int twopow = 1;
		int i = 0;
		while((a - twopow) % 256 != 0) { twopow *= 2; i++; }
		return (i+1);
	}
	
    public static void main(String[] args) {
	    Scanner sc = new Scanner(System.in);
	    while(sc.hasNextLine()){
	        BigInteger n = sc.nextBigInteger();
	        BigInteger k = new BigInteger("256");
	        int i;
	        char[] c = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
	        for(i = 0; i < 8; i++){
	        	System.out.print(c[i]);
	        	System.out.print(process(n));
	        	if(i != 7){
	        		System.out.print(" ");
	        	}
	        	else{
	        		System.out.print('\n');
	        	}
	        	n = n.divide(k);
	        }
	    }
    }
}