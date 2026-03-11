import java.io.RandomAccessFile;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class AnalizadorLexico {

    private RandomAccessFile entrada;
    private int fila = 1;
    private int columna = 0;
    private int tokenFila;
    private int tokenColumna;
    private char charActual = ' ';
    private boolean eof = false;
    private Map<String, Integer> palabrasReservadas;

    public AnalizadorLexico(RandomAccessFile entrada) {
        this.entrada = entrada;
        this.palabrasReservadas = new HashMap<>();
        palabrasReservadas.put("class", Token.CLASS);
        palabrasReservadas.put("fun",   Token.FUN);
        palabrasReservadas.put("int",   Token.INT);
        palabrasReservadas.put("float", Token.FLOAT);
        palabrasReservadas.put("print", Token.PRINT);
        charActual = leerChar();
    }

    private char leerChar() {
        try {
            int byteRead = entrada.read();
            if (byteRead == -1) {
                eof = true;
                return '\0';
            }
            char c = (char) byteRead;
            columna++;
            if (c == '\n') {
                fila++;
                columna = 0;
            }
            return c;
        } catch (IOException e) {
            System.err.println("Error de E/S");
            System.exit(-1);
        }
        return '\0';
    }

    private void retroceder(char c) {
        if (c == '\0' && eof) return;
        try {
            entrada.seek(entrada.getFilePointer() - 1);
            if (c == '\n') {
                fila--;
            } else {
                columna--;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Token siguienteToken() {
        int estado = 0;
        StringBuilder lexema = new StringBuilder();
        Token t = new Token();

        while (true) {
            switch (estado) {
                case 0: // estado inicial
                    if (eof && charActual == '\0') {
                        t.tipo = Token.EOF;
                        t.fila = fila;
                        t.columna = columna;
                        t.lexema = "";
                        return t;
                    }
                    if (charActual <= ' ' && charActual != '\0') {
                        charActual = leerChar();
                        estado = 0;
                    } else if (Character.isLetter(charActual)) {
                        tokenFila = fila;
                        tokenColumna = columna;
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 1;
                    } else if (Character.isDigit(charActual)) {
                        tokenFila = fila;
                        tokenColumna = columna;
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 3;
                    } else if (charActual == '/') {
                        tokenFila = fila;
                        tokenColumna = columna;
                        charActual = leerChar();
                        estado = 8;
                    } else if (charActual == '+' || charActual == '-') {
                        t.fila = fila;
                        t.columna = columna;
                        t.lexema = String.valueOf(charActual);
                        t.tipo = Token.OPAS;
                        charActual = leerChar();
                        return t;
                    } else if (charActual == '{') {
                        t.fila = fila;
                        t.columna = columna;
                        t.lexema = "{";
                        t.tipo = Token.LBRA;
                        charActual = leerChar();
                        return t;
                    } else if (charActual == '}') {
                        t.fila = fila;
                        t.columna = columna;
                        t.lexema = "}";
                        t.tipo = Token.RBRA;
                        charActual = leerChar();
                        return t;
                    } else if (charActual == ';') {
                        t.fila = fila;
                        t.columna = columna;
                        t.lexema = ";";
                        t.tipo = Token.PYC;
                        charActual = leerChar();
                        return t;
                    } else if (charActual == '=') {
                        t.fila = fila;
                        t.columna = columna;
                        t.lexema = "=";
                        t.tipo = Token.ASIG;
                        charActual = leerChar();
                        return t;
                    } else {
                        errorLexico(fila, columna, charActual);
                    }
                    break;

                case 1: // leyendo identificador
                    if (Character.isLetterOrDigit(charActual)) {
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 1;
                    } else {
                        estado = 2;
                    }
                    break;

                case 2: // aceptar identificador/keyword
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    if (palabrasReservadas.containsKey(t.lexema)) {
                        t.tipo = palabrasReservadas.get(t.lexema);
                    } else {
                        t.tipo = Token.ID;
                    }
                    return t;

                case 3: // leyendo digitos enteros
                    if (Character.isDigit(charActual)) {
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 3;
                    } else if (charActual == '.') {
                        char sig = leerChar();
                        if (Character.isDigit(sig)) {
                            lexema.append('.');
                            lexema.append(sig);
                            charActual = leerChar();
                            estado = 6;
                        } else {
                            retroceder(sig);
                            estado = 4; // charActual queda como '.'
                        }
                    } else {
                        estado = 4;
                    }
                    break;

                case 4: // aceptar numero entero
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.NUMENTERO;
                    return t;

                case 6: // leyendo digitos del real
                    if (Character.isDigit(charActual)) {
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 6;
                    } else {
                        estado = 7;
                    }
                    break;

                case 7: // aceptar numero real
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.NUMREAL;
                    return t;

                case 8: // despues de leer '/'
                    if (charActual == '*') {
                        charActual = leerChar();
                        estado = 9; // cuerpo del comentario
                    } else {
                        // '/' solo no es valido
                        System.err.println("Error lexico (" + tokenFila + "," + tokenColumna + "): caracter '/' incorrecto");
                        System.exit(-1);
                    }
                    break;

                case 9: // cuerpo del comentario
                    if (eof && charActual == '\0') {
                        System.err.println("Error lexico: fin de fichero inesperado");
                        System.exit(-1);
                    }
                    if (charActual == '*') {
                        charActual = leerChar();
                        estado = 10;
                    } else {
                        charActual = leerChar();
                        estado = 9;
                    }
                    break;

                case 10: // posible fin de comentario (despues de '*')
                    if (eof && charActual == '\0') {
                        System.err.println("Error lexico: fin de fichero inesperado");
                        System.exit(-1);
                    }
                    if (charActual == '/') {
                        charActual = leerChar();
                        lexema.setLength(0);
                        estado = 0;
                    } else if (charActual == '*') {
                        charActual = leerChar();
                        estado = 10;
                    } else {
                        charActual = leerChar();
                        estado = 9;
                    }
                    break;
            }
        }
    }

    private void errorLexico(int f, int c, char car) {
        if (eof && car == '\0') {
            System.err.println("Error lexico: fin de fichero inesperado");
        } else {
            System.err.println("Error lexico (" + f + "," + c + "): caracter '" + car + "' incorrecto");
        }
        System.exit(-1);
    }
}
