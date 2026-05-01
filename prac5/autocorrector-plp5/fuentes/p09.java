
import java.util.Scanner;

public class p09 {

 public static void main(String[] args)
 {
  double fact,sumafact;
  int  i,j,k;
  Scanner sca = new Scanner(System.in);

  k = sca.nextInt(); // La entrada es "4"
  sumafact = 0.0;
  i = k;

  while (i>1) 
  {
   j = i;
   fact = 1;
   while (j>1) 
   {
      if ( fact >= 1 )
         fact = fact * j;
      else
         fact = 0;
      j = j-1;
   }
   sumafact = sumafact + fact;
   i = i -1;
  }

  System.out.println(sumafact); // Debe salir "32.000"
 }
}
