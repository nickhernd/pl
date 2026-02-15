import java.io.RandomAccessFile;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class AnalizadorLexico {

    private RandomAccessFile entrada;
    private int fila = 1;
    private int columna = 0;
    private char charActual = ' '; 
    private boolean eof = false;
    private Map<String, Integer> palabrasReservadas;

    public AnalizadorLexico(RandomAccessFile entrada) {
        this.entrada = entrada;
        // Mapeo basado en TUS constantes de Token.java
        this.palabrasReservadas = new HashMap<>();
        palabrasReservadas.put("class", Token.CLASS);
        palabrasReservadas.put("fun", Token.FUN);
        palabrasReservadas.put("int", Token.INT);
        palabrasReservadas.put("float", Token.FLOAT);
        palabrasReservadas.put("if", Token.IF);
        palabrasReservadas.put("else", Token.ELSE);
        palabrasReservadas.put("fi", Token.FI);
        palabrasReservadas.put("print", Token.PRINT);
    }

    private char leerChar() {
        try {
            int byteRead = entrada.read();
            if (byteRead == -1) {
                eof = true;
                return '\0';
            }
            char c = (char) byteRead;
            if (c == '\n') {
                fila++;
                columna = 0; 
            } else if (c == '\t') {
                columna++; 
            } else {
                columna++;
            }
            return c;
        } catch (IOException e) {
            System.err.println("Error de E/S");
            System.exit(-1);
        }
        return '\0';
    }

    private void retroceder() {
        try {
            if (!eof && entrada.getFilePointer() > 0) {
                entrada.seek(entrada.getFilePointer() - 1);
                columna--; 
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Token siguienteToken() {
        Token t = new Token();
        
        // 1. Consumir blancos y comentarios
        while (true) {
            if (charActual == '\0' && eof) {
                t.tipo = Token.EOF;
                return t;
            }
            
            if (charActual <= ' ') { // Blancos, saltos, tabs
                charActual = leerChar();
                continue;
            }
            
            // Logica de comentarios con '/'
            if (charActual == '/') {
                char sig = leerChar();
                if (sig == '*') {
                    boolean cerrado = false;
                    while (!eof) {
                        char c = leerChar();
                        if (c == '*') {
                            char c2 = leerChar();
                            if (c2 == '/') {
                                cerrado = true;
                                charActual = leerChar(); 
                                break;
                            } else {
                                retroceder(); 
                            }
                        }
                    }
                    if (!cerrado && eof) {
                        System.err.println("Error lexico: fin de fichero inesperado"); // Mensaje PDF 
                        System.exit(-1);
                    }
                    continue; 
                } else {
                    retroceder(); 
                    // No es comentario, el '/' se procesará abajo como OPMUL
                    break; 
                }
            }
            break; 
        }

        if (eof) {
            t.tipo = Token.EOF;
            return t;
        }

        t.fila = fila;
        t.columna = columna; 

        // 2. Automata principal mapeado a TU Token.java
        switch (charActual) {
            case '(': t.tipo = Token.PARI; t.lexema = "("; charActual = leerChar(); break;
            case ')': t.tipo = Token.PARD; t.lexema = ")"; charActual = leerChar(); break;
            case '{': t.tipo = Token.LBRA; t.lexema = "{"; charActual = leerChar(); break;
            case '}': t.tipo = Token.RBRA; t.lexema = "}"; charActual = leerChar(); break;
            case ';': t.tipo = Token.PYC;  t.lexema = ";"; charActual = leerChar(); break;
            case ':': t.tipo = Token.DOSP; t.lexema = ":"; charActual = leerChar(); break;
            
            case '+': 
            case '-': 
                t.tipo = Token.OPAS; t.lexema = String.valueOf(charActual); charActual = leerChar(); break;
            
            case '*': 
            case '/': 
                t.tipo = Token.OPMUL; t.lexema = String.valueOf(charActual); charActual = leerChar(); break;
            
            case '=': 
                char sig = leerChar();
                if (sig == '=') {
                   t.tipo = Token.OPREL; t.lexema = "=="; charActual = leerChar();
                } else {
                   retroceder();
                   t.tipo = Token.ASIG; t.lexema = "="; charActual = leerChar();
                }
                break;

            case '<':
                sig = leerChar();
                if (sig == '=') {
                   t.tipo = Token.OPREL; t.lexema = "<="; charActual = leerChar();
                } else {
                   retroceder();
                   t.tipo = Token.OPREL; t.lexema = "<"; charActual = leerChar();
                }
                break;
                
            case '>':
                sig = leerChar();
                if (sig == '=') {
                   t.tipo = Token.OPREL; t.lexema = ">="; charActual = leerChar();
                } else {
                   retroceder();
                   t.tipo = Token.OPREL; t.lexema = ">"; charActual = leerChar();
                }
                break;
                
            case '!':
                sig = leerChar();
                if (sig == '=') {
                   t.tipo = Token.OPREL; t.lexema = "!="; charActual = leerChar();
                } else {
                   errorLexico(t.fila, t.columna, '!');
                }
                break;

            default:
                if (Character.isLetter(charActual)) {
                    StringBuilder sb = new StringBuilder();
                    while (Character.isLetterOrDigit(charActual)) {
                        sb.append(charActual);
                        charActual = leerChar();
                    }
                    String lex = sb.toString();
                    t.lexema = lex;
                    if (palabrasReservadas.containsKey(lex)) {
                        t.tipo = palabrasReservadas.get(lex);
                    } else {
                        t.tipo = Token.ID;
                    }
                } else if (Character.isDigit(charActual)) {
                    StringBuilder sb = new StringBuilder();
                    while (Character.isDigit(charActual)) {
                        sb.append(charActual);
                        charActual = leerChar();
                    }
                    if (charActual == '.') {
                        char next = leerChar();
                        retroceder();
                        if (Character.isDigit(next)) {
                            // It's a float
                            sb.append(charActual);
                            charActual = leerChar(); // consume dot
                            
                            while(Character.isDigit(charActual)) {
                                sb.append(charActual);
                                charActual = leerChar();
                            }
                            t.tipo = Token.NUMREAL;
                        } else {
                            // It's an integer
                            t.tipo = Token.NUMENTERO;
                        }
                    } else {
                        t.tipo = Token.NUMENTERO;
                    }
                    t.lexema = sb.toString();
                } else {
                    errorLexico(t.fila, t.columna, charActual);
                }
        }
        return t;
    }

    private void errorLexico(int f, int c, char car) {
        System.err.println("Error lexico (" + f + "," + c + "): caracter '" + car + "' incorrecto");
        System.exit(-1);
    }
}
