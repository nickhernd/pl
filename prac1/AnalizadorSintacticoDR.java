public class AnalizadorSintacticoDR {

    private AnalizadorLexico al;
    private Token tokenActual;
    private StringBuilder reglas;
    private boolean mostrarReglas = true; 

    public AnalizadorSintacticoDR(AnalizadorLexico al) {
        this.al = al;
        this.reglas = new StringBuilder();
        this.tokenActual = al.siguienteToken();
    }

    public void comprobarFinFichero() {
        if (tokenActual.tipo != Token.EOF) {
            errorSintactico(Token.EOF);
        }
        if (mostrarReglas) {
            System.out.println(reglas.toString().trim());
        }
    }

    private void emparejar(int tipoEsperado) {
        if (tokenActual.tipo == tipoEsperado) {
            tokenActual = al.siguienteToken();
        } else {
            errorSintactico(tipoEsperado);
        }
    }

    private void errorSintactico(int... tokensEsperados) {
        int[] ordenPDF = {
            Token.CLASS, Token.ID, Token.LBRA, Token.RBRA, Token.FUN, Token.PYC,
            Token.INT, Token.FLOAT, Token.ASIG, Token.IF, Token.DOSP, Token.ELSE,
            Token.FI, Token.PRINT, Token.OPREL, Token.OPAS, Token.OPMUL,
            Token.NUMENTERO, Token.NUMREAL, Token.PARI, Token.PARD
        };

        if (tokenActual.tipo == Token.EOF) {
             System.err.print("Error sintactico: encontrado fin de fichero, esperaba");
        } else {
             System.err.print("Error sintactico (" + tokenActual.fila + "," + tokenActual.columna + "): encontrado '" + tokenActual.lexema + "', esperaba");
        }
        
        for (int tipoOrden : ordenPDF) {
            for (int esperado : tokensEsperados) {
                if (tipoOrden == esperado) {
                    System.err.print(" " + Token.nombreToken.get(tipoOrden));
                    break;
                }
            }
        }
        System.err.println(" ");
        System.exit(-1);
    }

    private void regla(int n) {
        reglas.append(n).append(" ");
    }

    // 1. S -> class id lbra M rbra
    public void S() {
        if (tokenActual.tipo == Token.CLASS) {
            regla(1);
            emparejar(Token.CLASS);
            emparejar(Token.ID);
            emparejar(Token.LBRA);
            M();
            emparejar(Token.RBRA);
        } else {
            errorSintactico(Token.CLASS);
        }
    }

    // 2. M -> Fun M
    // 3. M -> S M
    // 4. M -> epsilon
    public void M() {
        if (tokenActual.tipo == Token.FUN) {
            regla(2);
            Fun();
            M();
        } else if (tokenActual.tipo == Token.CLASS) {
            regla(3);
            S();
            M();
        } else if (tokenActual.tipo == Token.RBRA || tokenActual.tipo == Token.LBRA || 
                   tokenActual.tipo == Token.ID || tokenActual.tipo == Token.IF || 
                   tokenActual.tipo == Token.PRINT || tokenActual.tipo == Token.INT || 
                   tokenActual.tipo == Token.FLOAT) {
            regla(4);
        } else {
            errorSintactico(Token.FUN, Token.CLASS, Token.RBRA, Token.LBRA, Token.ID, Token.IF, Token.PRINT, Token.INT, Token.FLOAT);
        }
    }

    // 5. Fun -> fun id A lbra M Cod rbra
    public void Fun() {
        if (tokenActual.tipo == Token.FUN) {
            regla(5);
            emparejar(Token.FUN);
            emparejar(Token.ID);
            A();
            emparejar(Token.LBRA);
            M();
            Cod();
            emparejar(Token.RBRA);
        } else {
            errorSintactico(Token.FUN);
        }
    }

    // 6. A -> DV Ap
    // 35. A -> epsilon
    public void A() {
        if (tokenActual.tipo == Token.INT || tokenActual.tipo == Token.FLOAT) {
            regla(6);
            DV();
            Ap();
        } else if (tokenActual.tipo == Token.LBRA) {
            regla(35);
        } else {
            errorSintactico(Token.INT, Token.FLOAT, Token.LBRA);
        }
    }

    // 7. Ap -> pyc DV Ap
    // 8. Ap -> epsilon
    public void Ap() {
        if (tokenActual.tipo == Token.PYC) {
            regla(7);
            emparejar(Token.PYC);
            DV();
            Ap();
        } else if (tokenActual.tipo == Token.LBRA) {
            regla(8);
        } else {
            errorSintactico(Token.PYC, Token.LBRA);
        }
    }

    // 9. DV -> Tipo id
    public void DV() {
        if (tokenActual.tipo == Token.INT || tokenActual.tipo == Token.FLOAT) {
            regla(9);
            Tipo();
            emparejar(Token.ID);
        } else {
            errorSintactico(Token.INT, Token.FLOAT);
        }
    }

    // 10. Tipo -> int
    // 11. Tipo -> float
    public void Tipo() {
        if (tokenActual.tipo == Token.INT) {
            regla(10);
            emparejar(Token.INT);
        } else if (tokenActual.tipo == Token.FLOAT) {
            regla(11);
            emparejar(Token.FLOAT);
        } else {
            errorSintactico(Token.INT, Token.FLOAT);
        }
    }

    // 12. Cod -> I Codp
    public void Cod() {
        if (tokenActual.tipo == Token.LBRA || tokenActual.tipo == Token.ID || 
            tokenActual.tipo == Token.IF || tokenActual.tipo == Token.PRINT || 
            tokenActual.tipo == Token.INT || tokenActual.tipo == Token.FLOAT) {
            regla(12);
            I();
            Codp();
        } else {
            errorSintactico(Token.LBRA, Token.ID, Token.IF, Token.PRINT, Token.INT, Token.FLOAT);
        }
    }

    // 13. Codp -> pyc I Codp
    // 14. Codp -> epsilon
    public void Codp() {
        if (tokenActual.tipo == Token.PYC) {
            regla(13);
            emparejar(Token.PYC);
            I();
            Codp();
        } else if (tokenActual.tipo == Token.RBRA) {
            regla(14);
        } else {
            errorSintactico(Token.PYC, Token.RBRA);
        }
    }

    // 16. I -> lbra Cod rbra
    // 17. I -> id asig Expr
    // 18. I -> if Expr dosp I Ip
    // 21. I -> print Expr
    // 15. I -> DV
    public void I() {
        if (tokenActual.tipo == Token.LBRA) {
            regla(16);
            emparejar(Token.LBRA);
            Cod();
            emparejar(Token.RBRA);
        } else if (tokenActual.tipo == Token.ID) {
            regla(17);
            emparejar(Token.ID);
            emparejar(Token.ASIG);
            Expr();
        } else if (tokenActual.tipo == Token.IF) {
            regla(18);
            emparejar(Token.IF);
            Expr();
            emparejar(Token.DOSP);
            I();
            Ip();
        } else if (tokenActual.tipo == Token.PRINT) {
            regla(21);
            emparejar(Token.PRINT);
            Expr();
        } else if (tokenActual.tipo == Token.INT || tokenActual.tipo == Token.FLOAT) {
            regla(15);
            DV();
        } else {
            errorSintactico(Token.LBRA, Token.ID, Token.IF, Token.PRINT, Token.INT, Token.FLOAT);
        }
    }

    // 19. Ip -> else I fi
    // 20. Ip -> fi
    public void Ip() {
        if (tokenActual.tipo == Token.ELSE) {
            regla(19);
            emparejar(Token.ELSE);
            I();
            emparejar(Token.FI);
        } else if (tokenActual.tipo == Token.FI) {
            regla(20);
            emparejar(Token.FI);
        } else {
            errorSintactico(Token.ELSE, Token.FI);
        }
    }

    // 22. Expr -> E Exprp
    public void Expr() {
        if (tokenActual.tipo == Token.ID || tokenActual.tipo == Token.NUMENTERO || 
            tokenActual.tipo == Token.NUMREAL || tokenActual.tipo == Token.PARI) {
            regla(22);
            E();
            Exprp();
        } else {
            errorSintactico(Token.ID, Token.NUMENTERO, Token.NUMREAL, Token.PARI);
        }
    }

    // 23. Exprp -> oprel E
    // 24. Exprp -> epsilon
    public void Exprp() {
        if (tokenActual.tipo == Token.OPREL) {
            regla(23);
            emparejar(Token.OPREL);
            E();
        } else if (tokenActual.tipo == Token.DOSP || tokenActual.tipo == Token.PARD || 
                   tokenActual.tipo == Token.PYC || tokenActual.tipo == Token.RBRA || 
                   tokenActual.tipo == Token.ELSE || tokenActual.tipo == Token.FI) {
            regla(24);
        } else {
            errorSintactico(Token.OPREL, Token.DOSP, Token.PARD, Token.PYC, Token.RBRA, Token.ELSE, Token.FI);
        }
    }

    // 25. E -> T Ep
    public void E() {
        if (tokenActual.tipo == Token.ID || tokenActual.tipo == Token.NUMENTERO || 
            tokenActual.tipo == Token.NUMREAL || tokenActual.tipo == Token.PARI) {
            regla(25);
            T();
            Ep();
        } else {
            errorSintactico(Token.ID, Token.NUMENTERO, Token.NUMREAL, Token.PARI);
        }
    }

    // 26. Ep -> opas T Ep
    // 27. Ep -> epsilon
    public void Ep() {
        if (tokenActual.tipo == Token.OPAS) {
            regla(26);
            emparejar(Token.OPAS);
            T();
            Ep();
        } else if (tokenActual.tipo == Token.OPREL || tokenActual.tipo == Token.DOSP || 
                   tokenActual.tipo == Token.PARD || tokenActual.tipo == Token.PYC || 
                   tokenActual.tipo == Token.RBRA || tokenActual.tipo == Token.ELSE || 
                   tokenActual.tipo == Token.FI) {
            regla(27);
        } else {
            errorSintactico(Token.OPAS, Token.OPREL, Token.DOSP, Token.PARD, Token.PYC, Token.RBRA, Token.ELSE, Token.FI);
        }
    }

    // 28. T -> F Tp
    public void T() {
        if (tokenActual.tipo == Token.ID || tokenActual.tipo == Token.NUMENTERO || 
            tokenActual.tipo == Token.NUMREAL || tokenActual.tipo == Token.PARI) {
            regla(28);
            F();
            Tp();
        } else {
            errorSintactico(Token.ID, Token.NUMENTERO, Token.NUMREAL, Token.PARI);
        }
    }

    // 29. Tp -> opmul F Tp
    // 30. Tp -> epsilon
    public void Tp() {
        if (tokenActual.tipo == Token.OPMUL) {
            regla(29);
            emparejar(Token.OPMUL);
            F();
            Tp();
        } else if (tokenActual.tipo == Token.OPAS || tokenActual.tipo == Token.OPREL || 
                   tokenActual.tipo == Token.DOSP || tokenActual.tipo == Token.PARD || 
                   tokenActual.tipo == Token.PYC || tokenActual.tipo == Token.RBRA || 
                   tokenActual.tipo == Token.ELSE || tokenActual.tipo == Token.FI) {
            regla(30);
        } else {
            errorSintactico(Token.OPMUL, Token.OPAS, Token.OPREL, Token.DOSP, Token.PARD, Token.PYC, Token.RBRA, Token.ELSE, Token.FI);
        }
    }

    // 31. F -> id
    // 32. F -> numentero
    // 33. F -> numreal
    // 34. F -> pari Expr pard
    public void F() {
        if (tokenActual.tipo == Token.ID) {
            regla(31);
            emparejar(Token.ID);
        } else if (tokenActual.tipo == Token.NUMENTERO) {
            regla(32);
            emparejar(Token.NUMENTERO);
        } else if (tokenActual.tipo == Token.NUMREAL) {
            regla(33);
            emparejar(Token.NUMREAL);
        } else if (tokenActual.tipo == Token.PARI) {
            regla(34);
            emparejar(Token.PARI);
            Expr();
            emparejar(Token.PARD);
        } else {
            errorSintactico(Token.ID, Token.NUMENTERO, Token.NUMREAL, Token.PARI);
        }
    }

}
