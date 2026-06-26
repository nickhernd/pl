// [IR-10] Test operadores logicos y booleanos
public class ir04_logic {
    public static void main(String[] args) {
        boolean a;
        boolean b;
        boolean c;
        a = true;
        b = false;
        c = a && b;
        if (c) {
            System.out.println(1);
        }
        if (!b) {
            System.out.println(2);
        }
    }
}
