
import java.util.Scanner;

public class p03 {

 public static void main(String[] args) {
  int i,j;
  int a,b,c;
  double[][] p = new double [4][4];
  Scanner sc = new Scanner(System.in);
  
  i=0;
  j=0;
  while (i<4)
  {
    j=0;
    while (j<4)
    {
      p[i][j] = sc.nextDouble();
      j=j+1;
    }
    i=i+1;
  }
  
  if (i==j)
  {
    double sumafila,sumatotal;
    int div;
    div = sc.nextInt();
    
    i=0;
    sumatotal=0;
    while (i<4)
    {
      j=0;
      sumafila=0;
      while (j<4)
      {
        sumafila=sumafila+p[i][j];
        j=j+1;
      }
      System.out.println(sumafila);
      i=i+1;
      sumatotal = sumatotal+sumafila;
    }
    System.out.println(sumatotal/div);
  }
 }
}