public class Error10 {
    public static void main(String[] args) {
        int x;
        x = 10;
        if (x) { // Error: If condition must be boolean
            x = 20;
        }
    }
}
