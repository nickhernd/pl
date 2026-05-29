public class p19 {
 public static void main(String[] args) {
  int n, res;
  n = 7;
  if (n < 0) res = 0;
  else if (n < 5) res = 1;
  else if (n < 10) res = 2;
  else res = 3;
  System.out.println(res);
  n = 15;
  if (n < 0) res = 0;
  else if (n < 5) res = 1;
  else if (n < 10) res = 2;
  else res = 3;
  System.out.println(res);
 }
}
