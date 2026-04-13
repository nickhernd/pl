
import java.util.Stack;

public class TraductorDR {
    private AnalizadorLexico al;
    private Token tok;
    private TablaSimbolos tsActual;
    
    private final int ERRYADECL=1, ERRNODECL=2, ERRTIPOS=3, ERRNOSIMPLE=4, ERRNOENTERO=5;

    public TraductorDR(AnalizadorLexico al) {
        this.al = al;
        this.tok = al.siguienteToken();
        this.tsActual = new TablaSimbolos(null);
    }

    private void emparejar(int tipo) {
        if (tok.tipo == tipo) {
            tok = al.siguienteToken();
        } else {
            System.err.println("Error sintactico en fila " + tok.fila + ", columna " + tok.columna + ": se esperaba " + tipo + " y se encontro " + tok.tipo);
            System.exit(-1);
        }
    }

    public void comprobarFinFichero() {
        if (tok.tipo != Token.EOF) {
            System.err.println("Error sintactico: se esperaba fin de fichero");
            System.exit(-1);
        }
    }

    private void errorSemantico(int nerror, Token t) {
        System.err.print("Error semantico (" + t.fila + "," + t.columna + "): en '" + t.lexema + "', ");
        switch (nerror) {
            case ERRYADECL: System.err.println("ya existe en este ambito"); break;
            case ERRNODECL: System.err.println("no ha sido declarado"); break;
            case ERRTIPOS: System.err.println("tipos incompatibles entero/real"); break;
            case ERRNOSIMPLE: System.err.println("debe ser de tipo entero o real"); break;
            case ERRNOENTERO: System.err.println("la expresion debe ser de tipo entero"); break;
        }
        System.exit(-1);
    }

    public String S(String prefijo) {
        return Clases(prefijo);
    }

    private String Clases(String prefijo) {
        StringBuilder sb = new StringBuilder();
        while (tok.tipo == Token.CLASS) {
            emparejar(Token.CLASS);
            Token idTok = tok;
            emparejar(Token.ID);
            
            String nuevoPrefijo = (prefijo.equals("") ? idTok.lexema : prefijo + "_" + idTok.lexema);
            
            if (!tsActual.set(new Simbolo(idTok.lexema, Simbolo.CLASS, nuevoPrefijo))) {
                errorSemantico(ERRYADECL, idTok);
            }
            
            tsActual = new TablaSimbolos(tsActual);
            emparejar(Token.LBRACE);
            String miembros = Miembros(nuevoPrefijo, false, "");
            emparejar(Token.RBRACE);
            tsActual = tsActual.getParent();
            
            sb.append("// class ").append(nuevoPrefijo).append("\n").append(miembros).append("\n");
        }
        return sb.toString();
    }

    private String Miembros(String prefijo, boolean enFuncion, String prefijoBloque) {
        StringBuilder sb = new StringBuilder();
        while (tok.tipo != Token.RBRACE && tok.tipo != Token.EOF && tok.tipo != Token.ELSE && tok.tipo != Token.FI) {
            if (tok.tipo == Token.INT || tok.tipo == Token.FLOAT) {
                sb.append(DefVar(prefijo, enFuncion, prefijoBloque)).append(";\n");
                if (tok.tipo == Token.SEMICOLON) emparejar(Token.SEMICOLON);
            } else if (tok.tipo == Token.FUN) {
                sb.append(DefFun(prefijo));
            } else if (tok.tipo == Token.CLASS) {
                sb.append(Clases(prefijo));
            } else if (esInicioSentencia() || tok.tipo == Token.LBRACE) {
                sb.append(Sentencia(prefijo, enFuncion, prefijoBloque));
                if (tok.tipo == Token.SEMICOLON) emparejar(Token.SEMICOLON);
            } else if (tok.tipo == Token.SEMICOLON) {
                emparejar(Token.SEMICOLON);
            } else {
                // Error sintáctico, forzamos error con emparejar
                emparejar(Token.RBRACE);
            }
        }
        return sb.toString();
    }

    private boolean esInicioSentencia() {
        return tok.tipo == Token.ID || tok.tipo == Token.PRINT || tok.tipo == Token.IF;
    }

    private String DefVar(String prefijo, boolean enFuncion, String prefijoBloque) {
        int tipo = (tok.tipo == Token.INT ? Simbolo.ENTERO : Simbolo.REAL);
        String tipoStr = (tipo == Simbolo.ENTERO ? "int" : "float");
        emparejar(tok.tipo);
        Token idTok = tok;
        emparejar(Token.ID);
        
        String nomTrad;
        if (enFuncion) {
            nomTrad = prefijo + prefijoBloque + "_" + idTok.lexema;
        } else {
            nomTrad = prefijo + "_" + idTok.lexema;
        }
        
        if (!tsActual.set(new Simbolo(idTok.lexema, tipo, nomTrad))) {
            errorSemantico(ERRYADECL, idTok);
        }
        
        return tipoStr + " " + nomTrad;
    }

    private String DefFun(String prefijo) {
        emparejar(Token.FUN);
        Token idTok = tok;
        emparejar(Token.ID);
        
        String nuevoPrefijo = prefijo + "_" + idTok.lexema;
        if (!tsActual.set(new Simbolo(idTok.lexema, Simbolo.FUN, nuevoPrefijo))) {
            errorSemantico(ERRYADECL, idTok);
        }
        
        tsActual = new TablaSimbolos(tsActual);
        String params = Parametros(nuevoPrefijo);
        emparejar(Token.LBRACE);
        String miembros = Miembros(nuevoPrefijo, true, "");
        emparejar(Token.RBRACE);
        tsActual = tsActual.getParent();
        
        return "void " + nuevoPrefijo + "(" + params + ") {\n" + miembros + "} // " + nuevoPrefijo + "\n";
    }

    private String Parametros(String prefijo) {
        if (tok.tipo == Token.INT || tok.tipo == Token.FLOAT) {
            int tipo = (tok.tipo == Token.INT ? Simbolo.ENTERO : Simbolo.REAL);
            String tipoStr = (tipo == Simbolo.ENTERO ? "int" : "float");
            emparejar(tok.tipo);
            Token idTok = tok;
            emparejar(Token.ID);
            
            String nomTrad = "arg_" + prefijo + "_" + idTok.lexema;
            if (!tsActual.set(new Simbolo(idTok.lexema, tipo, nomTrad))) {
                errorSemantico(ERRYADECL, idTok);
            }
            
            String miTrad = tipoStr + " " + nomTrad;
            if (tok.tipo == Token.SEMICOLON) {
                emparejar(Token.SEMICOLON);
                return miTrad + "," + Parametros(prefijo);
            } else if (tok.tipo == Token.INT || tok.tipo == Token.FLOAT) {
                return miTrad + "," + Parametros(prefijo);
            }
            return miTrad;
        }
        return "";
    }

    private String Sentencia(String prefijo, boolean enFuncion, String prefijoBloque) {
        if (tok.tipo == Token.ID) {
            Token idTok = tok;
            emparejar(Token.ID);
            Simbolo s = tsActual.get(idTok.lexema);
            if (s == null) errorSemantico(ERRNODECL, idTok);
            if (s.tipo != Simbolo.ENTERO && s.tipo != Simbolo.REAL) errorSemantico(ERRNOSIMPLE, idTok);
            
            Token assignTok = tok;
            emparejar(Token.ASSIGN);
            ResExp exp = Exp();
            
            String trad;
            if (s.tipo == Simbolo.REAL && exp.tipo == Simbolo.ENTERO) {
                trad = s.nomtrad + " = itor(" + exp.trad + ");\n";
            } else if (s.tipo == exp.tipo) {
                trad = s.nomtrad + " = " + exp.trad + ";\n";
            } else {
                errorSemantico(ERRTIPOS, assignTok);
                trad = "";
            }
            return trad;
        } else if (tok.tipo == Token.PRINT) {
            emparejar(Token.PRINT);
            ResExp exp = Exp();
            if (exp.tipo == Simbolo.ENTERO) {
                return "printf(\"%d\"," + exp.trad + ");\n";
            } else {
                return "printf(\"%f\"," + exp.trad + ");\n";
            }
        } else if (tok.tipo == Token.IF) {
            Token ifTok = tok;
            emparejar(Token.IF);
            ResExp exp = Exp();
            if (exp.tipo != Simbolo.ENTERO) {
                errorSemantico(ERRNOENTERO, ifTok);
            }
            
            emparejar(Token.COLON);
            String s1 = Sentencia(prefijo, enFuncion, prefijoBloque);
            String s2 = "";
            if (tok.tipo == Token.ELSE) {
                emparejar(Token.ELSE);
                s2 = "else\n" + Sentencia(prefijo, enFuncion, prefijoBloque);
            }
            emparejar(Token.FI);
            return "if (" + exp.trad + ")\n" + s1 + "\n" + s2;
        } else if (tok.tipo == Token.LBRACE) {
            emparejar(Token.LBRACE);
            tsActual = new TablaSimbolos(tsActual);
            String bloque = "{\n" + Miembros(prefijo, enFuncion, prefijoBloque + "_") + "}\n";
            emparejar(Token.RBRACE);
            tsActual = tsActual.getParent();
            return bloque;
        } else if (tok.tipo == Token.INT || tok.tipo == Token.FLOAT) {
            return DefVar(prefijo, enFuncion, prefijoBloque) + ";\n";
        }
        return "";
    }

    private ResExp Exp() {
        return ExpRel();
    }

    private ResExp ExpRel() {
        ResExp e1 = ExpAdd();
        while (tok.tipo == Token.LT || tok.tipo == Token.GT || tok.tipo == Token.LE || tok.tipo == Token.GE || tok.tipo == Token.EQ || tok.tipo == Token.NE) {
            Token op = tok;
            emparejar(tok.tipo);
            ResExp e2 = ExpAdd();
            
            String opStr = op.lexema;
            int tipoResult = Simbolo.ENTERO;
            String t1 = e1.trad, t2 = e2.trad;
            String suffix = "i";
            
            if (e1.tipo == Simbolo.REAL || e2.tipo == Simbolo.REAL) {
                suffix = "r";
                if (e1.tipo == Simbolo.ENTERO) t1 = "itor(" + t1 + ")";
                if (e2.tipo == Simbolo.ENTERO) t2 = "itor(" + t2 + ")";
            }
            
            e1 = new ResExp(tipoResult, t1 + " " + opStr + suffix + " " + t2);
        }
        return e1;
    }

    private ResExp ExpAdd() {
        ResExp e1 = ExpMult();
        while (tok.tipo == Token.PLUS || tok.tipo == Token.MINUS) {
            Token op = tok;
            emparejar(tok.tipo);
            ResExp e2 = ExpMult();
            
            String opStr = op.lexema;
            int tipoResult;
            String t1 = e1.trad, t2 = e2.trad;
            String suffix = "i";
            
            if (e1.tipo == Simbolo.REAL || e2.tipo == Simbolo.REAL) {
                tipoResult = Simbolo.REAL;
                suffix = "r";
                if (e1.tipo == Simbolo.ENTERO) t1 = "itor(" + t1 + ")";
                if (e2.tipo == Simbolo.ENTERO) t2 = "itor(" + t2 + ")";
            } else {
                tipoResult = Simbolo.ENTERO;
            }
            
            e1 = new ResExp(tipoResult, t1 + " " + opStr + suffix + " " + t2);
        }
        return e1;
    }

    private ResExp ExpMult() {
        ResExp e1 = Factor();
        while (tok.tipo == Token.MULT || tok.tipo == Token.DIV) {
            Token op = tok;
            emparejar(tok.tipo);
            ResExp e2 = Factor();
            
            String opStr = op.lexema;
            int tipoResult;
            String t1 = e1.trad, t2 = e2.trad;
            String suffix = "i";
            
            if (e1.tipo == Simbolo.REAL || e2.tipo == Simbolo.REAL) {
                tipoResult = Simbolo.REAL;
                suffix = "r";
                if (e1.tipo == Simbolo.ENTERO) t1 = "itor(" + t1 + ")";
                if (e2.tipo == Simbolo.ENTERO) t2 = "itor(" + t2 + ")";
            } else {
                tipoResult = Simbolo.ENTERO;
            }
            
            e1 = new ResExp(tipoResult, t1 + " " + opStr + suffix + " " + t2);
        }
        return e1;
    }

    private ResExp Factor() {
        if (tok.tipo == Token.ID) {
            Token idTok = tok;
            emparejar(Token.ID);
            Simbolo s = tsActual.get(idTok.lexema);
            if (s == null) errorSemantico(ERRNODECL, idTok);
            if (s.tipo != Simbolo.ENTERO && s.tipo != Simbolo.REAL) errorSemantico(ERRNOSIMPLE, idTok);
            return new ResExp(s.tipo, s.nomtrad);
        } else if (tok.tipo == Token.NUM) {
            String lex = tok.lexema;
            emparejar(Token.NUM);
            return new ResExp(Simbolo.ENTERO, lex);
        } else if (tok.tipo == Token.REAL) {
            String lex = tok.lexema;
            emparejar(Token.REAL);
            return new ResExp(Simbolo.REAL, lex);
        } else if (tok.tipo == Token.LPARENT) {
            emparejar(Token.LPARENT);
            ResExp e = Exp();
            emparejar(Token.RPARENT);
            return new ResExp(e.tipo, "(" + e.trad + ")");
        }
        // Forzamos error sintáctico
        emparejar(Token.NUM);
        return null;
    }

    private class ResExp {
        int tipo;
        String trad;
        ResExp(int t, String tr) { tipo = t; trad = tr; }
    }
}
