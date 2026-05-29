public class p20 {
 public static void main(String[] args) {
  int[] a = new int[10];
  int i, suma;
  i = 0;
  while (i < 5) {
    a[i*2] = i * i;
    i = i + 1;
  }
  suma = 0;
  i = 0;
  while (i < 5) {
    suma = suma + a[i*2];
    i = i + 1;
  }
  System.out.println(suma);
 }
}
