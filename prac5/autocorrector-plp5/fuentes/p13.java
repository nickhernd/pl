
public class p13 {

 public static void main(String[] args)
 {
     int   i;
     int[] SerieDeFibonacci = new int [ 100 ];

  SerieDeFibonacci[0]=1;
  SerieDeFibonacci[1]=1;
  i=2;
  while (i<100)
  {
      SerieDeFibonacci[i]= SerieDeFibonacci[i-1]+SerieDeFibonacci[i-2];
      i=i+1;
  }
  System.out.println(SerieDeFibonacci[SerieDeFibonacci[SerieDeFibonacci[4]]]);
   // Debe salir "34"

 }
}
