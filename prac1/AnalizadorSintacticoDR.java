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

    // Algoritmo para mostrar errores en el orden que exige el PDF (Independiente de los IDs del Token.java)
    private void errorSintactico(int... tokensEsperados) {
        // Mapeo manual del orden visual exigido por el PDF
        int[] ordenPDF = {
            Token.CLASS, Token.ID, Token.LBRA, Token.RBRA, Token.FUN, Token.PYC,
            Token.INT, Token.FLOAT, Token.ASIG, Token.IF, Token.DOSP, Token.ELSE,
            Token.FI, Token.PRINT, Token.OPREL, Token.OPAS, Token.OPMUL,
            Token.NUMENTERO, Token.NUMREAL, Token.PARI, Token.PARD
        };

        if (tokenActual.tipo == Token.EOF) {
             System.out.print("Error sintactico: encontrado fin de fichero, esperaba");
        } else {
             System.out.print("Error sintactico (" + tokenActual.fila + "," + tokenActual.columna + "): encontrado '" + tokenActual.lexema + "', esperaba");
        }
        
        // Intersección de conjuntos: (TokensEsperados U OrdenPDF)
        for (int tipoOrden : ordenPDF) {
            for (int esperado : tokensEsperados) {
                if (tipoOrden == esperado) {
                    System.out.print(" " + Token.nombreToken.get(tipoOrden));
                    break;
                }
            }
        }
        System.out.println();
        System.exit(-1);
    }

    private void regla(int n) {
        reglas.append(n).append(" ");
    }

    // --- REGLAS GRAMÁTICALES (LL1) ---

    // 1. S -> class id { M }
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
    // 3. M -> lambda
    public void M() {
        if (tokenActual.tipo == Token.FUN) {
            regla(2);
            Fun();
            M();
        } 
        // Follow(M) = { } } -> RBRA
        else if (tokenActual.tipo == Token.RBRA) {
            regla(3);
        } else {
            errorSintactico(Token.FUN, Token.RBRA);
        }
    }

    // 5. Fun -> fun id A { M Cod }
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
    public void A() {
        if (tokenActual.tipo == Token.INT || tokenActual.tipo == Token.FLOAT) {
            regla(6);
            DV();
            Ap();
        } else {
            errorSintactico(Token.INT, Token.FLOAT);
        }
    }

    // 7. Ap -> ; DV Ap
    // 8. Ap -> lambda
    public void Ap() {
        if (tokenActual.tipo == Token.PYC) {
            regla(7);
            emparejar(Token.PYC);
            DV();
            Ap();
        } 
        // Follow(Ap) = { { } -> LBRA
        else if (tokenActual.tipo == Token.LBRA) {
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

    // 11. Cod -> I Codp
    public void Cod() {
        if (tokenActual.tipo == Token.LBRA || tokenActual.tipo == Token.ID || 
            tokenActual.tipo == Token.IF || tokenActual.tipo == Token.PRINT) {
            regla(11);
            I();
            Codp();
        } else {
            errorSintactico(Token.LBRA, Token.ID, Token.IF, Token.PRINT);
        }
    }

    // 13. Codp -> ; I Codp
    // 14. Codp -> lambda
    public void Codp() {
        if (tokenActual.tipo == Token.PYC) {
            regla(13);
            emparejar(Token.PYC);
            I();
            Codp();
        } 
        // Follow(Codp) = { } } -> RBRA
        else if (tokenActual.tipo == Token.RBRA) {
            regla(14);
        } else {
            errorSintactico(Token.PYC, Token.RBRA);
        }
    }

    // 15. I -> { Cod }
    // 16. I -> id = Expr
    // 17. I -> if Expr : I Ip
    // 18. I -> print Expr
    public void I() {
        if (tokenActual.tipo == Token.LBRA) {
            regla(15);
            emparejar(Token.LBRA);
            Cod();
            emparejar(Token.RBRA);
        } else if (tokenActual.tipo == Token.ID) {
            regla(16);
            emparejar(Token.ID);
            emparejar(Token.ASIG);
            Expr();
        } else if (tokenActual.tipo == Token.IF) {
            regla(17);
            emparejar(Token.IF);
            Expr();
            emparejar(Token.DOSP);
            I();
            Ip();
        } else if (tokenActual.tipo == Token.PRINT) {
            regla(18);
            emparejar(Token.PRINT);
            Expr();
        } else {
            errorSintactico(Token.LBRA, Token.ID, Token.IF, Token.PRINT);
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

    // 21. Expr -> E Exprp
    public void Expr() {
        if (tokenActual.tipo == Token.ID || tokenActual.tipo == Token.NUMENTERO || 
            tokenActual.tipo == Token.NUMREAL || tokenActual.tipo == Token.PARI) {
            regla(21);
            E();
            Exprp();
        } else {
            errorSintactico(Token.ID, Token.NUMENTERO, Token.NUMREAL, Token.PARI);
        }
    }

    // 22. Exprp -> oprel E
    // 23. Exprp -> lambda
    public void Exprp() {
        if (tokenActual.tipo == Token.OPREL) {
            regla(22);
            emparejar(Token.OPREL);
            E();
        } 
        else if (tokenActual.tipo == Token.PARD || tokenActual.tipo == Token.PYC || 
                 tokenActual.tipo == Token.DOSP || tokenActual.tipo == Token.ELSE || 
                 tokenActual.tipo == Token.FI || tokenActual.tipo == Token.PRINT || 
                 tokenActual.tipo == Token.RBRA) {
            regla(23);
        } else {
            errorSintactico(Token.OPREL, Token.PARD, Token.PYC, Token.DOSP, Token.ELSE, Token.FI, Token.PRINT, Token.RBRA);
        }
    }

    // 24. E -> T Ep
    public void E() {
        if (tokenActual.tipo == Token.ID || tokenActual.tipo == Token.NUMENTERO || 
            tokenActual.tipo == Token.NUMREAL || tokenActual.tipo == Token.PARI) {
            regla(24);
            T();
            Ep();
        } else {
            errorSintactico(Token.ID, Token.NUMENTERO, Token.NUMREAL, Token.PARI);
        }
    }

    // 25. Ep -> opas T Ep
    // 26. Ep -> lambda
    public void Ep() {
        if (tokenActual.tipo == Token.OPAS) {
            regla(25);
            emparejar(Token.OPAS);
            T();
            Ep();
        } 
        else if (tokenActual.tipo == Token.OPREL || tokenActual.tipo == Token.PARD || 
                 tokenActual.tipo == Token.PYC || tokenActual.tipo == Token.DOSP || 
                 tokenActual.tipo == Token.ELSE || tokenActual.tipo == Token.FI || 
                 tokenActual.tipo == Token.PRINT || tokenActual.tipo == Token.RBRA) {
            regla(26);
        } else {
            errorSintactico(Token.OPAS, Token.OPREL, Token.PARD, Token.PYC, Token.DOSP, Token.ELSE, Token.FI, Token.PRINT, Token.RBRA);
        }
    }

    // 27. T -> F Tp
    public void T() {
        if (tokenActual.tipo == Token.ID || tokenActual.tipo == Token.NUMENTERO || 
            tokenActual.tipo == Token.NUMREAL || tokenActual.tipo == Token.PARI) {
            regla(27);
            F();
            Tp();
        } else {
            errorSintactico(Token.ID, Token.NUMENTERO, Token.NUMREAL, Token.PARI);
        }
    }

    // 28. Tp -> opmul F Tp
    // 29. Tp -> lambda
    public void Tp() {
        if (tokenActual.tipo == Token.OPMUL) {
            regla(28);
            emparejar(Token.OPMUL);
            F();
            Tp();
        } 
        else if (tokenActual.tipo == Token.OPAS || tokenActual.tipo == Token.OPREL || 
                 tokenActual.tipo == Token.PARD || tokenActual.tipo == Token.PYC || 
                 tokenActual.tipo == Token.DOSP || tokenActual.tipo == Token.ELSE || 
                 tokenActual.tipo == Token.FI || tokenActual.tipo == Token.PRINT || 
                 tokenActual.tipo == Token.RBRA) {
            regla(29);
        } else {
            errorSintactico(Token.OPMUL, Token.OPAS, Token.OPREL, Token.PARD, Token.PYC, Token.DOSP, Token.ELSE, Token.FI, Token.PRINT, Token.RBRA);
        }
    }

    // 30. F -> id
    // 31. F -> numentero
    // 32. F -> numreal
    // 33. F -> ( Expr )
    public void F() {
        if (tokenActual.tipo == Token.ID) {
            regla(30);
            emparejar(Token.ID);
        } else if (tokenActual.tipo == Token.NUMENTERO) {
            regla(31);
            emparejar(Token.NUMENTERO);
        } else if (tokenActual.tipo == Token.NUMREAL) {
            regla(32);
            emparejar(Token.NUMREAL);
        } else if (tokenActual.tipo == Token.PARI) {
            regla(33);
            emparejar(Token.PARI);
            Expr();
            emparejar(Token.PARD);
        } else {
            errorSintactico(Token.ID, Token.NUMENTERO, Token.NUMREAL, Token.PARI);
        }
    }

}
