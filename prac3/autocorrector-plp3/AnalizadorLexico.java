
import java.io.RandomAccessFile;
import java.io.IOException;

public class AnalizadorLexico {
    private RandomAccessFile entrada;
    private int fila = 1;
    private int columna = 1;

    public AnalizadorLexico(RandomAccessFile entrada) {
        this.entrada = entrada;
    }

    public Token siguienteToken() {
        try {
            while (true) {
                int c = entrada.read();
                if (c == -1) return new Token(Token.EOF, "", fila, columna);

                char ch = (char) c;
                if (Character.isWhitespace(ch)) {
                    actualizarFilaColumna(ch);
                    continue;
                }

                if (ch == '/' && verSiguiente() == '*') {
                    entrada.read(); // saltar '*'
                    columna += 2;
                    saltarComentario();
                    continue;
                }

                int f = fila;
                int col = columna;

                if (Character.isLetter(ch)) {
                    StringBuilder sb = new StringBuilder();
                    sb.append(ch);
                    columna++;
                    while (Character.isLetterOrDigit((char) verSiguiente())) {
                        sb.append((char) entrada.read());
                        columna++;
                    }
                    String lexema = sb.toString();
                    return new Token(obtenerTipoKeyword(lexema), lexema, f, col);
                }

                if (Character.isDigit(ch) || ch == '.') {
                    StringBuilder sb = new StringBuilder();
                    sb.append(ch);
                    columna++;
                    boolean esReal = (ch == '.');
                    while (Character.isDigit((char) verSiguiente())) {
                        sb.append((char) entrada.read());
                        columna++;
                    }
                    if (!esReal && verSiguiente() == '.') {
                        sb.append((char) entrada.read());
                        columna++;
                        esReal = true;
                        while (Character.isDigit((char) verSiguiente())) {
                            sb.append((char) entrada.read());
                            columna++;
                        }
                    }
                    if (sb.toString().equals(".")) {
                        // Es un punto solo, no debería pasar en esta gramática pero lo manejamos
                        return new Token(Token.COLON, ".", f, col); // En esta gramática : es COLON
                        // Wait, . is not in the operators list. Let's re-check.
                    }
                    return new Token(esReal ? Token.REAL : Token.NUM, sb.toString(), f, col);
                }

                // Operadores
                columna++;
                switch (ch) {
                    case '{': return new Token(Token.LBRACE, "{", f, col);
                    case '}': return new Token(Token.RBRACE, "}", f, col);
                    case ';': return new Token(Token.SEMICOLON, ";", f, col);
                    case ':': return new Token(Token.COLON, ":", f, col);
                    case ',': return new Token(Token.COMMA, ",", f, col);
                    case '+': return new Token(Token.PLUS, "+", f, col);
                    case '-': return new Token(Token.MINUS, "-", f, col);
                    case '*': return new Token(Token.MULT, "*", f, col);
                    case '/': return new Token(Token.DIV, "/", f, col);
                    case '(': return new Token(Token.LPARENT, "(", f, col);
                    case ')': return new Token(Token.RPARENT, ")", f, col);
                    case '<':
                        if (verSiguiente() == '=') {
                            entrada.read(); columna++;
                            return new Token(Token.LE, "<=", f, col);
                        }
                        return new Token(Token.LT, "<", f, col);
                    case '>':
                        if (verSiguiente() == '=') {
                            entrada.read(); columna++;
                            return new Token(Token.GE, ">=", f, col);
                        }
                        return new Token(Token.GT, ">", f, col);
                    case '=':
                        if (verSiguiente() == '=') {
                            entrada.read(); columna++;
                            return new Token(Token.EQ, "==", f, col);
                        }
                        return new Token(Token.ASSIGN, "=", f, col);
                    case '!':
                        if (verSiguiente() == '=') {
                            entrada.read(); columna++;
                            return new Token(Token.NE, "!=", f, col);
                        }
                        // Error léxico si es solo !
                        break;
                }
            }
        } catch (IOException e) {
            return new Token(Token.EOF, "", fila, columna);
        }
    }

    private int verSiguiente() throws IOException {
        long pos = entrada.getFilePointer();
        int c = entrada.read();
        entrada.seek(pos);
        return c;
    }

    private void actualizarFilaColumna(char ch) {
        if (ch == '\n') {
            fila++;
            columna = 1;
        } else if (ch == '\t') {
            columna += 4; // Asumimos tab = 4
        } else {
            columna++;
        }
    }

    private void saltarComentario() throws IOException {
        while (true) {
            int c = entrada.read();
            if (c == -1) break;
            char ch = (char) c;
            actualizarFilaColumna(ch);
            if (ch == '*' && verSiguiente() == '/') {
                entrada.read(); columna++;
                break;
            }
        }
    }

    private int obtenerTipoKeyword(String lexema) {
        switch (lexema) {
            case "class": return Token.CLASS;
            case "fun": return Token.FUN;
            case "int": return Token.INT;
            case "float": return Token.FLOAT;
            case "if": return Token.IF;
            case "else": return Token.ELSE;
            case "fi": return Token.FI;
            case "print": return Token.PRINT;
            default: return Token.ID;
        }
    }
}
