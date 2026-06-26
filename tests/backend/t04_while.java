public class TestWhile {
    public static void main(String[] args) {
        int i;
        int sum;
        i = 1;
        sum = 0;
        while (i <= 5) {
            sum = sum + i;
            i = i + 1;
        }
        System.out.println(sum);
    }
}
