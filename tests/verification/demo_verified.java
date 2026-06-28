public class DemoVerified {

    // CORRECTO: valor absoluto de -5 siempre es >= 0
    // WP(if(x<0) return -x; return x, result>=0)
    //   = (x<0 ==> -x>=0) && (x>=0 ==> x>=0)
    // Tras x:=-5: (true ==> 5>=0) && (false ==> ...) = true
    // VC: true ==> true → UNSAT = VERIFICADO
    @pre  true
    @post result >= 0
    public static int absValue() {
        int x;
        x = -5;
        if (x < 0) return -x;
        return x;
    }

    // BUG INTENCIONAL: afirmamos result > 10 pero devolvemos 5
    // WP(return 5, result>10) = 5>10 = false
    // VC: true ==> false → SAT = BUG DETECTADO
    @post result > 10
    public static int wrongMethod() {
        int x;
        x = 5;
        return x;
    }

    // Suma 1+2+3+4+5=15 con invariante de bucle completo
    // Invariante: s >= 0 && i >= 1
    // - Iniciacion: antes del bucle s=0>=0 && i=1>=1 → true
    // - Preservacion: (s>=0 && i>=1 && i<=5) ==> (s+i)>=0 && (i+1)>=1
    //   Desde i>=1 y s>=0: s+i >= 1 >= 0 ✓; i+1 >= 2 >= 1 ✓
    // - Uso: (s>=0 && i>=1 && i>5) ==> WP(return s, result>=0) = s>=0 ✓
    // - Terminacion: (... && i<=5) ==> 6-i >= 1 >= 0 ✓
    @post result >= 0
    public static int sumLoop() {
        int i;
        int s;
        i = 1;
        s = 0;
        while (i <= 5)
        @invariant s >= 0 && i >= 1
        @variant   6 - i
        {
            s = s + i;
            i = i + 1;
        }
        return s;
    }

    public static void main(String[] args) {
        int val;
        val = absValue();
        System.out.println(val);
        val = sumLoop();
        System.out.println(val);
    }
}
