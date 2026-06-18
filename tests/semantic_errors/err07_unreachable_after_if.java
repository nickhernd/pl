public class Error07 {
    public static int test() {
        if (true) {
            return 1;
        } else {
            return 2;
        }
        System.out.println(1); // Error: Unreachable code detected
        return 0;
    }
    public static void main(String[] args) {
    }
}
