public class p17 {
 public static void main(String[] args) {
  int[][] m = new int[3][3];
  int i, j, suma;
  i = 0;
  while (i < 3) {
    j = 0;
    while (j < 3) {
      m[i][j] = i * 3 + j;
      j = j + 1;
    }
    i = i + 1;
  }
  suma = m[0][0] + m[1][1] + m[2][2];
  System.out.println(suma);
 }
}
