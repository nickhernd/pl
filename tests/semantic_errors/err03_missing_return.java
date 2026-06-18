public class Error03 {
    public static int test() {
        if (true) {
            return 1;
        }
        // Error: Method must return a value (missing else)
    }
    public static void main(String[] args) {
    }
}
