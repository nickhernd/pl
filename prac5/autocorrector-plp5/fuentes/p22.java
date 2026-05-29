import java.util.Scanner;
public class p22 {
 public static void main(String[] args) {
  int[] a = new int[10];
  int i, n, suma;
  Scanner sc = new Scanner(System.in);
  n = sc.nextInt();
  i = 0;
  while (i < n) {
    a[i] = sc.nextInt();
    i = i + 1;
  }
  suma = 0;
  i = 0;
  while (i < n) {
    suma = suma + a[i];
    i = i + 1;
  }
  System.out.println(suma);
 }
}
