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
        palabrasReservadas.put("fun", Token.FUN);
        palabrasReservadas.put("int", Token.INT);
        palabrasReservadas.put("float", Token.FLOAT);
        palabrasReservadas.put("if", Token.IF);
        palabrasReservadas.put("else", Token.ELSE);
        palabrasReservadas.put("fi", Token.FI);
        palabrasReservadas.put("print", Token.PRINT);
        
        // Leer el primer caracter
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
                // La columna es difícil de recuperar exactamente sin leer atrás, 
                // pero para retract en Lexico suele bastar con el puntero de archivo.
                // En este lenguaje la columna en retract solo se usa para el siguiente token.
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
                case 0: // q0
                    if (eof && charActual == '\0') {
                        t.tipo = Token.EOF;
                        return t;
                    }
                    if (charActual <= ' ' && charActual != '\0') { // Blancos
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
                    } else if (charActual == '=') {
                        tokenFila = fila;
                        tokenColumna = columna;
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 8;
                    } else if (charActual == '<') {
                        tokenFila = fila;
                        tokenColumna = columna;
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 11;
                    } else if (charActual == '>') {
                        tokenFila = fila;
                        tokenColumna = columna;
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 14;
                    } else if (charActual == '!') {
                        tokenFila = fila;
                        tokenColumna = columna;
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 17;
                    } else if (charActual == '/') {
                        tokenFila = fila;
                        tokenColumna = columna;
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 19;
                    } else if ("+-*(){};:".indexOf(charActual) != -1) {
                        tokenFila = fila;
                        tokenColumna = columna;
                        t.fila = tokenFila;
                        t.columna = tokenColumna;
                        t.lexema = String.valueOf(charActual);
                        if (charActual == '+') t.tipo = Token.OPAS;
                        else if (charActual == '-') t.tipo = Token.OPAS;
                        else if (charActual == '*') t.tipo = Token.OPMUL;
                        else if (charActual == '(') t.tipo = Token.PARI;
                        else if (charActual == ')') t.tipo = Token.PARD;
                        else if (charActual == '{') t.tipo = Token.LBRA;
                        else if (charActual == '}') t.tipo = Token.RBRA;
                        else if (charActual == ';') t.tipo = Token.PYC;
                        else if (charActual == ':') t.tipo = Token.DOSP;
                        charActual = leerChar();
                        return t;
                    } else {
                        errorLexico(fila, columna, charActual);
                    }
                    break;

                case 1: // q1 (ID)
                    if (Character.isLetterOrDigit(charActual)) {
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 1;
                    } else {
                        estado = 2;
                    }
                    break;

                case 2: // q2 (ID Retract)
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    if (palabrasReservadas.containsKey(t.lexema)) {
                        t.tipo = palabrasReservadas.get(t.lexema);
                    } else {
                        t.tipo = Token.ID;
                    }
                    // No consumimos charActual, se queda para el siguiente q0
                    return t;

                case 3: // q3 (INT)
                    if (Character.isDigit(charActual)) {
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 3;
                    } else if (charActual == '.') {
                        char sig = leerChar();
                        if (Character.isDigit(sig)) {
                            lexema.append(charActual);
                            lexema.append(sig);
                            charActual = leerChar();
                            estado = 6; // Ir directo a q6
                        } else {
                            retroceder(sig);
                            estado = 4; // Aceptar entero
                        }
                    } else {
                        estado = 4;
                    }
                    break;

                case 4: // q4 (INT Retract)
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.NUMENTERO;
                    return t;

                case 5: // q5 (Dote in FLOAT)
                    if (Character.isDigit(charActual)) {
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 6;
                    } else {
                        // Error: esperado digito después de punto
                        errorLexico(fila, columna, charActual);
                    }
                    break;

                case 6: // q6 (FLOAT)
                    if (Character.isDigit(charActual)) {
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 6;
                    } else {
                        estado = 7;
                    }
                    break;

                case 7: // q7 (FLOAT Retract)
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.NUMREAL;
                    return t;

                case 8: // q8 (=)
                    if (charActual == '=') {
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 9;
                    } else {
                        estado = 10;
                    }
                    break;

                case 9: // q9 (==)
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.OPREL;
                    return t;

                case 10: // q10 (= Retract)
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.ASIG;
                    return t;

                case 11: // q11 (<)
                    if (charActual == '=') {
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 13;
                    } else {
                        estado = 12;
                    }
                    break;

                case 12: // q12 (< Retract)
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.OPREL;
                    return t;

                case 13: // q13 (<=)
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.OPREL;
                    return t;

                case 14: // q14 (>)
                    if (charActual == '=') {
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 16;
                    } else {
                        estado = 15;
                    }
                    break;

                case 15: // q15 (> Retract)
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.OPREL;
                    return t;

                case 16: // q16 (>=)
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.OPREL;
                    return t;

                case 17: // q17 (!)
                    if (charActual == '=') {
                        lexema.append(charActual);
                        charActual = leerChar();
                        estado = 18;
                    } else {
                        // Error relacional: ! solo no es válido
                        errorLexico(fila, columna, charActual);
                    }
                    break;

                case 18: // q18 (!=)
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.OPREL;
                    return t;

                case 19: // q19 (/)
                    if (charActual == '*') {
                        charActual = leerChar();
                        estado = 20;
                    } else {
                        estado = 22;
                    }
                    break;

                case 20: // q20 (Body of comment)
                    if (eof && charActual == '\0') {
                        System.err.println("Error lexico: fin de fichero inesperado");
                        System.exit(-1);
                    }
                    if (charActual == '*') {
                        charActual = leerChar();
                        estado = 21;
                    } else {
                        charActual = leerChar();
                        estado = 20;
                    }
                    break;

                case 21: // q21 (Possible end of comment)
                    if (eof && charActual == '\0') {
                        System.err.println("Error lexico: fin de fichero inesperado");
                        System.exit(-1);
                    }
                    if (charActual == '/') {
                        charActual = leerChar();
                        lexema.setLength(0); // Reiniciar lexema para volver a q0
                        estado = 0;
                    } else if (charActual == '*') {
                        charActual = leerChar();
                        estado = 21;
                    } else {
                        charActual = leerChar();
                        estado = 20;
                    }
                    break;

                case 22: // q22 (/ Retract)
                    t.fila = tokenFila;
                    t.columna = tokenColumna;
                    t.lexema = lexema.toString();
                    t.tipo = Token.OPMUL;
                    return t;
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
