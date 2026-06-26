// [IR-10] Test saltos condicionales
public class ir02_if {
    public static void main(String[] args) {
        int x;
        x = 10;
        if (x > 5) {
            x = 1;
        } else {
            x = 0;
        }
        System.out.println(x);
    }
}
