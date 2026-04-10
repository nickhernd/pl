
public class Token {
    public static final int EOF = 0;
    public static final int ID = 1;
    public static final int CLASS = 2;
    public static final int FUN = 3;
    public static final int INT = 4;
    public static final int FLOAT = 5;
    public static final int IF = 6;
    public static final int ELSE = 7;
    public static final int FI = 8;
    public static final int PRINT = 9;
    public static final int NUM = 10;
    public static final int REAL = 11;
    public static final int LBRACE = 12; // {
    public static final int RBRACE = 13; // }
    public static final int SEMICOLON = 14; // ;
    public static final int COLON = 15; // :
    public static final int COMMA = 16; // ,
    public static final int ASSIGN = 17; // =
    public static final int PLUS = 18; // +
    public static final int MINUS = 19; // -
    public static final int MULT = 20; // *
    public static final int DIV = 21; // /
    public static final int LT = 22; // <
    public static final int GT = 23; // >
    public static final int LE = 24; // <=
    public static final int GE = 25; // >=
    public static final int EQ = 26; // ==
    public static final int NE = 27; // !=

    public static final int LPARENT = 28; // (
    public static final int RPARENT = 29; // )
    
    public int tipo;
    public String lexema;
    public int fila;
    public int columna;

    public Token(int tipo, String lexema, int fila, int columna) {
        this.tipo = tipo;
        this.lexema = lexema;
        this.fila = fila;
        this.columna = columna;
    }
}
