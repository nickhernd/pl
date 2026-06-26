# JavaSubset Compiler — Java → x86-64

A compiler for a statically-typed Java subset that translates source code to native x86-64 assembly via a three-address code intermediate representation. Built with Flex + Bison, C++11.

## Architecture

```
Source (.java)
    │
    ▼
┌─────────────┐
│  Lexer      │  Flex — tokenization
│  (lexer.l)  │
└─────┬───────┘
      │ token stream
      ▼
┌─────────────┐
│  Parser     │  Bison — grammar + AST construction
│ (parser.y)  │
└─────┬───────┘
      │ AST
      ▼
┌──────────────────┐
│ SemanticVisitor  │  Type checking, symbol resolution,
│                  │  @pre/@post annotation parsing
└─────┬────────────┘
      │ typed AST
      ▼
┌─────────────┐
│  IRBuilder  │  AST → 3-address code quadruples (IR)
└─────┬───────┘
      │ IR quadruples
      ▼
┌──────────────┐
│ IROptimizer  │  Constant folding, dead-code elimination,
│              │  copy propagation
└─────┬────────┘
      │ optimised IR
      ▼
┌──────────────────┐
│ RegisterAllocator│  Chaitin-Briggs graph coloring
│                  │  (liveness analysis → interference graph)
└─────┬────────────┘
      │ register map
      ▼
┌──────────────┐
│ X86Generator │  IR → AT&T syntax x86-64 assembly
└─────┬────────┘
      │ .s file
      ▼
    gcc/as → native ELF binary
```

## Language Features

| Feature | Status |
|---|---|
| `int`, `double`, `boolean` types | ✓ |
| Arithmetic: `+`, `-`, `*`, `/`, `%` | ✓ |
| Comparison & logical operators | ✓ |
| `if`/`else`, `while` | ✓ |
| `final` constants | ✓ |
| Static methods, `return` | ✓ |
| `System.out.print` / `println` | ✓ |
| `Scanner.nextInt()` / `nextDouble()` | ✓ |
| `@pre` / `@post` annotations | ✓ |
| `@invariant` / `@variant` on loops | ✓ |
| `==>` (logical implication in specs) | ✓ |

## Building

**Dependencies:** `make`, `g++`, `flex`, `bison`

```bash
make          # build ./compiler
make clean    # remove generated files
```

On Arch Linux:
```bash
sudo pacman -S base-devel flex bison
```

## Usage

### Compile to assembly and link

```bash
./compiler program.java          # emits program.s
gcc -no-pie -o program program.s # link to binary
./program
```

### Compiler flags

| Flag | Description |
|---|---|
| *(none)* | Compile to `.s` file |
| `--ir` | Print IR quadruples to stderr |
| `--reg-alloc` | Print register allocation map to stderr |

### Produce a DOT AST visualisation

```bash
./compiler --dot program.java | dot -Tpng -o ast.png
```

## Running the test suite

```bash
bash tests/run_tests.sh
```

Tests compile each `.java` → `.s` → binary, run it, and compare stdout against `.expected`.

```
PASS: t01_print.java
PASS: t02_arithmetic.java
PASS: t03_if_else.java
PASS: t04_while.java
PASS: t05_functions.java

Resultados: 5 PASS, 0 FAIL, 0 ERROR
```

To run semantic-error tests:
```bash
for f in tests/semantic_errors/*.java; do
    echo "=== $f ==="; ./compiler "$f" 2>&1; echo
done
```

## Formal Verification (Milestone 5 — in progress)

The compiler includes infrastructure for Hoare-logic verification using the **Z3 SMT solver**.

### Annotation syntax

```java
// @pre  — precondition on method entry
// @post — postcondition on method exit (use 'result' for the return value)
public static int abs(int x)
@pre  x != 0
@post result > 0
{
    if (x > 0) return x;
    return -x;
}

// @invariant / @variant on while loops
while (i < n)
@invariant sum == i * (i + 1) / 2
@variant   n - i
{
    sum = sum + i;
    i = i + 1;
}
```

### How it works

1. `Predicate.h` — logical predicate hierarchy (VarPred, BinaryPred, ImpliesPred, …)
2. `WPCalculus.h` — Weakest Precondition calculus (VER-4 through VER-6, skeleton)
3. `VCGenerator.h` — generates Verification Conditions `P ==> WP(body, Q)` (VER-7, skeleton)
4. `SMTExporter.h` — serialises VCs to SMT-Lib2 for Z3 (VER-8, skeleton)

Install Z3:
```bash
sudo pacman -S z3    # Arch
sudo apt install z3  # Debian/Ubuntu
```

Implemented so far: predicate hierarchy, annotation parsing, AST storage, `result` keyword.  
Pending (intentional — learning exercise): WP rules, VC generation, SMT export, Z3 integration.

## Project Structure

```
.
├── include/
│   ├── ASTNodes.h          AST node hierarchy
│   ├── IR.h                IR opcodes and quadruples
│   ├── Predicate.h         Logical predicate types (Hoare logic)
│   ├── Visitor.h           Visitor interface
│   ├── TablaSimbolos.h     Symbol table
│   └── TablaTipos.h        Type system
├── src/
│   ├── lexer.l             Flex lexer
│   ├── parser.y            Bison grammar
│   ├── SemanticVisitor.h   Type checker
│   ├── IRBuilder.h         AST → IR translation
│   ├── IROptimizer.h       IR optimisation passes
│   ├── RegisterAllocator.h Chaitin-Briggs register allocator
│   ├── X86Generator.h      IR → x86-64 code generator
│   ├── WPCalculus.h        Weakest precondition calculus (skeleton)
│   ├── VCGenerator.h       Verification condition generator (skeleton)
│   └── SMTExporter.h       SMT-Lib2 exporter for Z3 (skeleton)
├── tests/
│   ├── backend/            End-to-end compilation tests
│   ├── semantic_errors/    Semantic error detection tests
│   └── run_tests.sh        Test runner script
└── Makefile
```

## Milestones

| Milestone | Description | Status |
|---|---|---|
| 1 — Frontend | Lexer, parser, AST | Complete |
| 2 — Semantics | Type checking, symbol tables | Complete |
| 3 — IR | 3-address code, optimiser | Complete |
| 4 — Backend x86-64 | Code gen, register alloc, calling convention, scanf | Complete |
| 5 — Formal Verification | Hoare logic, WP calculus, Z3 integration | In progress |

## References

- Aho, Lam, Sethi, Ullman — *Compilers: Principles, Techniques, and Tools* (Dragon Book)
- Hoare — *An Axiomatic Basis for Computer Programming* (1969)
- Dijkstra — *A Discipline of Programming* (1976)
- Chaitin, Briggs — *Register Allocation via Coloring* (1982)
- System V AMD64 ABI — [refspecs.linuxbase.org](https://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf)
