public class AnalizadorSintacticoDR {
    private AnalizadorLexico lexico;
    private Token preanalisis;
    // StringBuilder to store the rule numbers for practice 3, as mentioned in the PDF.
    private StringBuilder ruleNumbers = new StringBuilder();
    // Flag to enable/disable printing rule numbers, as mentioned in the PDF.
    private boolean printRules = true;

    public AnalizadorSintacticoDR(AnalizadorLexico lexico) {
        this.lexico = lexico;
        // In a real scenario, you would get the first token here.
        // For now, let's just initialize it to null or get a token from the lexer.
        preanalisis = lexico.siguienteToken(); // Get the first token
    }

    public void S() {
        // This is a placeholder for the actual implementation of the S non-terminal.
        // It will involve checking the preanalisis token and calling other methods
        // corresponding to the grammar rules.
        System.out.println("Entering S()");
        // For now, let's just consume the token as a placeholder
        // In a proper implementation, this would match a production rule.
        // For example, if S -> class id lbra M rbra ...
        // We would check if preanalisis is Token.class_kw, consume it, then parse id, etc.
    }

    public void comprobarFinFichero() {
        // This method checks if the end of the file has been reached correctly.
        // If printRules is true and no errors occurred, it should print the accumulated rule numbers.
        System.out.println("Comprobando fin de fichero...");
        if (preanalisis == Token.EOF) {
            System.out.println("Fin de fichero alcanzado correctamente.");
            if (printRules && ruleNumbers.length() > 0) {
                System.out.println("Reglas aplicadas: " + ruleNumbers.toString());
            }
        } else {
            System.out.println("Error: Se esperaba fin de fichero pero se encontró: " + preanalisis);
            System.exit(-1);
        }
    }

    // Helper method to advance to the next token
    private void advance() {
        preanalisis = lexico.siguienteToken();
    }

    // Helper method to match an expected token
    private void match(Token expected) {
        if (preanalisis == expected) {
            advance();
        } else {
            // Error handling: unexpected token
            System.out.println("Error sintáctico: Se esperaba " + expected + " pero se encontró " + preanalisis);
            System.exit(-1);
        }
    }
}
