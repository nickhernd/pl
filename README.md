# JavaSubset Compiler — Java → x86-64

A compiler for a statically-typed Java subset that translates source code to native x86-64 assembly via a three-address code intermediate representation, with optional formal verification using Hoare Logic and the Z3 SMT solver. Built with Flex + Bison, C++11.

## Architecture

```
Source (.java)
     │
     ▼
┌──────────────┐
│  Lexer       │  Flex — tokenization, annotation tokens
│  (lexer.l)   │
└──────┬───────┘
       │ token stream
       ▼
┌──────────────┐
│  Parser      │  Bison LALR(1) — grammar + AST construction
│ (parser.y)   │
└──────┬───────┘
       │ AST
       ▼
┌──────────────────┐
│ SemanticVisitor  │  Type checking, symbol resolution,
│                  │  @pre/@post/@invariant annotation binding
└──────┬───────────┘
       │ typed AST + TablaSimbolos
       ├──────────────────────────────────────────────┐
       ▼                                              │ --verify
┌──────────────┐                               ┌─────▼──────────┐
│  IRBuilder   │  AST → 3-address quadruples   │  VCGenerator   │
└──────┬───────┘                               │  WPCalculus    │
       │ IR quadruples                         └─────┬──────────┘
       ▼                                            │ VCs
┌──────────────┐                               ┌────▼───────────┐
│ IROptimizer  │  Dead-code, const folding,    │  SMTExporter   │
│              │  copy propagation             │  (.smt2 + Z3)  │
└──────┬───────┘                               └────┬───────────┘
       │ optimised IR                               │ unsat/sat/unknown
       ▼                                            ▼
┌──────────────────┐                         [OK] / [BUG] report
│ RegisterAllocator│  Chaitin-Briggs graph coloring
│                  │  (liveness → interference graph → K=6 colors)
└──────┬───────────┘
       │ register map (temp → %reg | spill)
       ▼
┌──────────────┐
│ X86Generator │  IR → AT&T x86-64 assembly (System V ABI)
└──────┬───────┘
       │ .s file
       ▼
   gcc -no-pie → native ELF binary
```

## Language Features

| Feature | Support |
|---|---|
| Types: `int`, `double`, `boolean` | ✓ |
| Arithmetic: `+`, `-`, `*`, `/`, `%` | ✓ |
| Comparison and logical operators | ✓ |
| `if` / `else`, `while` | ✓ |
| `final` constants | ✓ |
| Static methods, `return` | ✓ |
| `System.out.print` / `println` | ✓ |
| `Scanner.nextInt()` / `nextDouble()` | ✓ |
| Formal annotations: `@pre`, `@post` | ✓ |
| Loop annotations: `@invariant`, `@variant` | ✓ |
| Implication operator `==>` in specs | ✓ |
| Division-by-zero safety VCs | ✓ |
| Termination VCs via `@variant` | ✓ |

## Building

**Dependencies:** `make`, `g++`, `flex`, `bison`

For formal verification: `z3`

```bash
# Arch Linux
sudo pacman -S base-devel flex bison z3

# Debian / Ubuntu
sudo apt install build-essential flex bison z3
```

```bash
make          # build ./compiler
make clean    # remove generated files
```

## Usage

### Compile to assembly and link

```bash
./compiler program.java            # emits program.s
gcc -no-pie -o program program.s   # link to binary
./program
```

### Compiler flags

| Flag | Output | Description |
|---|---|---|
| *(none)* | `program.s` | Compile to AT&T x86-64 assembly |
| `--ir` | stderr | Print IR quadruples (3-address code) |
| `--reg-alloc` | stderr | Print register allocation map |
| `--dot` | stdout | DOT graph of the AST |
| `--verify` | `program.smt2` | Formal verification via Z3 |

### Visualise the AST

```bash
./compiler --dot program.java | dot -Tpng -o ast.png
```

### Formal verification

```bash
./compiler --verify tests/verification/demo_verified.java
```

Output:
```
[OK]  [absValue] correctitud (unsat)
[OK]  [sumLoop] iniciacion del invariante (unsat)
[OK]  [sumLoop] preservacion del invariante (unsat)
[OK]  [sumLoop] uso del invariante (unsat)
[OK]  [sumLoop] correctitud (unsat)
[OK]  [sumLoop] terminacion (unsat)
[BUG] [wrongMethod] correctitud (sat)   <-- bug detectado
```

## Formal Verification

The `--verify` flag activates the Hoare Logic verification pipeline. Annotate your methods and loops with formal specifications:

```java
@pre  true
@post result >= 0
public static int absValue() {
    int x;
    x = -5;
    if (x < 0) return -x;
    return x;
}

@post result >= 0
public static int sumLoop() {
    int i; int s;
    i = 1; s = 0;
    while (i <= 5)
    @invariant s >= 0 && i >= 1
    @variant   6 - i
    {
        s = s + i;
        i = i + 1;
    }
    return s;
}
```

### How it works

1. **`WPCalculus.h`** — Weakest Precondition calculus with continuation-passing semantics for early `return` statements inside `if` branches. The naive reverse-iteration approach fails for early returns; the CPS approach threads the continuation into each branch so every `return e` always has access to the original postcondition `Q`.

2. **`VCGenerator.h`** — Generates four types of Verification Conditions:
   - *Correctness*: `P ==> WP(body, Q)`
   - *Loop initiation*: `P ==> WP(stmts_before, I)`
   - *Loop preservation*: `(I && B) ==> WP(body, I)`
   - *Loop use*: `(I && !B) ==> WP(stmts_after, Q)`
   - *Termination*: `(I && B) ==> variant >= 0`
   - *Division safety*: `P ==> divisor != 0`

3. **`SMTExporter.h`** — Serialises each VC to SMT-Lib2 format, invokes Z3, and reports coloured results. A `UNSAT` response from Z3 means the VC is valid (the program is correct at that point). A `SAT` response means Z3 found a counterexample — a bug.

### Annotation syntax

| Annotation | Placement | Meaning |
|---|---|---|
| `@pre expr` | Before method | Precondition on entry |
| `@post expr` | Before method | Postcondition on exit (`result` = return value) |
| `@invariant expr` | Before `while` body | Loop invariant |
| `@variant expr` | Before `while` body | Termination measure (must decrease) |

### Loop invariant strength

Invariants must be **strong enough** to prove preservation. A weak invariant allows Z3 to find counterexamples:

```java
// Weak: Z3 finds (i = -1, s = 0) satisfying (s >= 0 && i <= 5)
// but (s + i) = -1 < 0 — preservation fails
@invariant s >= 0

// Strong: (s >= 0 && i >= 1 && i <= 5) ==> (s + i) >= 0  -- UNSAT
@invariant s >= 0 && i >= 1
```

## Test Suite

```bash
bash tests/run_tests.sh
```

### Backend tests (5)

End-to-end: compile `.java` → `.s` → binary, run, compare stdout.

| Test | What it covers |
|---|---|
| `t01_print.java` | `System.out.println` of integers |
| `t02_arithmetic.java` | Arithmetic, precedence, modulo |
| `t03_if_else.java` | Nested conditionals |
| `t04_while.java` | Loop with accumulator, return |
| `t05_functions.java` | Inter-method calls |

### Semantic error tests (10)

The compiler must reject these with a non-zero exit code.

```
err01_const_assign       err06_return_missing_val
err02_return_mismatch    err07_unreachable_after_if
err03_missing_return     err08_const_double_assign
err04_unreachable_code   err09_incompatible_types_assign
err05_void_return_val    err10_if_cond_not_bool
```

### Verification tests (1)

```bash
./compiler --verify tests/verification/demo_verified.java
```

Verifies `absValue` (correct), `wrongMethod` (intentional bug, detected), and `sumLoop` (loop invariant + termination).

## Project Structure

```
.
├── include/
│   ├── ASTNodes.h            AST node hierarchy (all node types)
│   ├── IR.h                  IR opcodes and quadruple format
│   ├── Predicate.h           Logical predicate hierarchy (Hoare logic)
│   ├── Visitor.h             Visitor interface (GoF pattern)
│   ├── TablaSimbolos.h       Symbol table (lexical scoping)
│   └── TablaTipos.h          Type system
├── src/
│   ├── lexer.l               Flex lexer (with annotation tokens)
│   ├── parser.y              Bison grammar + semantic actions
│   ├── SemanticVisitor.h     Type checker + annotation binding
│   ├── IRBuilder.h           AST → IR translation
│   ├── IROptimizer.h         Dead-code, constant folding, copy propagation
│   ├── RegisterAllocator.h   Chaitin-Briggs graph coloring (K=6)
│   ├── X86Generator.h        IR → x86-64 AT&T assembly
│   ├── WPCalculus.h          WP calculus with CPS for early returns
│   ├── VCGenerator.h         VC generation (correctness + invariants)
│   └── SMTExporter.h         SMT-Lib2 export + Z3 invocation + reporting
├── tests/
│   ├── backend/              End-to-end compilation tests (5)
│   ├── semantic_errors/      Semantic error detection tests (10)
│   ├── verification/         Formal verification demos (1)
│   └── run_tests.sh          Test runner
├── docs/
│   └── latex/
│       ├── main.tex          Full technical report (58 pages)
│       ├── main.pdf          Compiled report PDF
│       ├── presentation.tex  Beamer slide deck (18 slides)
│       ├── presentation.pdf  Compiled presentation PDF
│       ├── chapters/         One chapter per compiler phase (cap01–cap10)
│       ├── apendices/        BNF grammar + x86-64 instruction reference
│       └── referencias.bib   Bibliography (Hoare, Dijkstra, Dragon Book, …)
└── Makefile
```

## Milestones

| # | Milestone | Key components | Status |
|---|---|---|---|
| 1 | Front-end | Flex lexer, Bison LALR(1) parser, C++ AST | Complete |
| 2 | Semantic analysis | `TablaSimbolos`, type checking, `SemanticVisitor` | Complete |
| 3 | IR + optimisation | 3-address quadruples, dead-code, folding, copy-prop | Complete |
| 4 | Backend x86-64 | System V ABI, Chaitin-Briggs register allocation | Complete |
| 5 | Formal verification | Hoare Logic, WP-CPS calculus, VCGenerator, Z3 | Complete |

## References

- Aho, Lam, Sethi, Ullman — *Compilers: Principles, Techniques, and Tools* (Dragon Book, 2006)
- Hoare — *An Axiomatic Basis for Computer Programming*, CACM 1969
- Dijkstra — *A Discipline of Programming*, Prentice-Hall, 1976
- Chaitin et al. — *Register Allocation via Coloring*, Computer Languages, 1981
- de Moura & Bjørner — *Z3: An Efficient SMT Solver*, TACAS 2008
- System V AMD64 ABI — [gitlab.com/x86-psABIs/x86-64-ABI](https://gitlab.com/x86-psABIs/x86-64-ABI)
