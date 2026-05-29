public class p18 {
 public static void main(String[] args) {
  int a, b, c;
  a = 5;
  b = 10;
  c = 0;
  if (a < b && b > 0) c = c + 1;
  if (a > b || b == 10) c = c + 1;
  if (!(a == b)) c = c + 1;
  System.out.println(c);
 }
}
