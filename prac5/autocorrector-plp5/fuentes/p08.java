
public class p08 {

 public static void main(String[] args)
 {
  int[][][] a = new int[3][3][2];
  int[] b = new int[18];
  {

    int n,i,j,k,aux;
  
    n=50;
    i=0;
    while (i<3)
     {
      j=0;
      while (j<3)
       {
        k=0;
        while (k<2)
         {
          a[i][j][k]=n;
          n=n-1;
          k=k+1;
         }
        j=j+1;
       }
      i=i+1;
     }
    i=0;
    while (i<3)
     {
      j=0;
      while (j<3)
       {
        k=0;
        while (k<2)
         {
          b[i*3*2+j*2+k]=a[i][j][k];
          k=k+1;
         }
        j=j+1;
       }
      i=i+1;
     }
    i=1;
    while (i<=17)
     {
      aux=b[i];
      j=i-1;
      while ((j!=0-1) && (aux<b[j]))
       {
        b[j+1] = b[j];
        j = j-1;
       }
      b[j+1]=aux;
      i=i+1;
     } 
    i=0; n=0;
    while (i<=2)
     {
      n=n+b[i];
      i=i+1;
     }
    System.out.println(n);   // Debe salir "102"
  }
 }
}
