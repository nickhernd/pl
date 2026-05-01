
import java.util.Scanner;

public class p15 {

 public static void main(String[] args)
 {
  int a,b,mcd, sig;
  boolean salir;
  Scanner sc = new Scanner(System.in);

  salir = false;
  a = sc.nextInt(); // La entrada es "27"
  b = a / 3 * 2;
  mcd = 1;
  sig = 1;

  System.out.println(a);
  System.out.println(b);
  while ( ! salir )
  {
   sig = sig + 1;
   if ( sig > b ) salir = true;
   else {
        System.out.println(sig);
        System.out.println(sig * (a/sig));     
        System.out.println(sig * (b/sig));
        if ( sig * (a / sig) == a && sig * (b / sig) == b  ) {
             mcd = sig;
             System.out.println(1000+sig);
        }
   }
  }
  System.out.println(mcd); // Debe salir "9"
 }
}
