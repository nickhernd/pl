OPTS=-Wall -g -Wno-write-strings -Wno-unused-function -Wno-sign-compare -std=c++11 -Iinclude
SRC_DIR=src
INC_DIR=include
OBJ_DIR=obj
OBJS=$(OBJ_DIR)/lex.yy.o $(OBJ_DIR)/parser.tab.o $(OBJ_DIR)/TablaSimbolos.o $(OBJ_DIR)/TablaTipos.o
CC=g++

all: compiler

compiler: $(OBJS)
	$(CC) $(OPTS) $(OBJS) -o compiler

$(OBJ_DIR)/lex.yy.o: $(SRC_DIR)/lex.yy.c $(INC_DIR)/comun.h $(SRC_DIR)/parser.tab.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(OPTS) -c $(SRC_DIR)/lex.yy.c -o $(OBJ_DIR)/lex.yy.o

$(OBJ_DIR)/parser.tab.o: $(SRC_DIR)/parser.tab.c $(SRC_DIR)/lex.yy.c $(INC_DIR)/comun.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(OPTS) -c $(SRC_DIR)/parser.tab.c -o $(OBJ_DIR)/parser.tab.o

$(OBJ_DIR)/TablaSimbolos.o: $(SRC_DIR)/TablaSimbolos.cc $(INC_DIR)/TablaSimbolos.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(OPTS) -c $(SRC_DIR)/TablaSimbolos.cc -o $(OBJ_DIR)/TablaSimbolos.o

$(OBJ_DIR)/TablaTipos.o: $(SRC_DIR)/TablaTipos.cc $(INC_DIR)/TablaTipos.h $(INC_DIR)/TablaSimbolos.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(OPTS) -c $(SRC_DIR)/TablaTipos.cc -o $(OBJ_DIR)/TablaTipos.o

$(SRC_DIR)/lex.yy.c: $(SRC_DIR)/lexer.l $(INC_DIR)/comun.h
	flex -o $(SRC_DIR)/lex.yy.c $(SRC_DIR)/lexer.l
	
$(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.tab.h: $(SRC_DIR)/parser.y $(INC_DIR)/comun.h $(INC_DIR)/TablaSimbolos.h $(INC_DIR)/TablaTipos.h
	bison -d -o $(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.y

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.tab.h $(SRC_DIR)/lex.yy.c
	rm -f compiler
