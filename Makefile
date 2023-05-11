CC=gcc
CFLAGS  =  -Wall
EXECUTABLE_NAME = interpret
BIN_DIR = ./bin
SRC_DIR = ./src
INC_DIR = ./include
BUILD_DIR = ./build
SOURCE_FILES=main.c interpreter.c lexer.c token.c parser.c AST.c
OBJECT_FILES=$(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)
EXECUTABLE_FILES=$(EXECUTABLE_NAME:%=$(BIN_DIR)/%) 

build: $(EXECUTABLE_FILES)

$(EXECUTABLE_FILES) : $(OBJECT_FILES)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "Build successfully finished."


$(OBJECT_FILES) : $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o : $(INC_DIR)/token.h $(INC_DIR)/AST.h $(INC_DIR)/lexer.h $(INC_DIR)/interpreter.h
$(BUILD_DIR)/parser.o : $(INC_DIR)/token.h $(INC_DIR)/AST.h $(INC_DIR)/lexer.h 
$(BUILD_DIR)/interpreter.o : $(INC_DIR)/token.h $(INC_DIR)/AST.h $(INC_DIR)/lexer.h
$(BUILD_DIR)/lexer.o : $(INC_DIR)/token.h $(INC_DIR)/AST.h
$(BUILD_DIR)/token.o : $(INC_DIR)/token.h

.PHONY : build clean
clean:
	rm interpret $(EXECUTABLE_FILES) $(OBJECT_FILES)