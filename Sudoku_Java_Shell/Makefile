RAW_SOURCES = \
	Assignment.java\
	Main.java\
	BTSolver.java\
	Constraint.java\
	ConstraintNetwork.java\
	Domain.java\
	SudokuBoard.java\
	Trail.java\
	Variable.java

SOURCE_DIR = src
BIN_DIR = bin
DOC_DIR = doc
SOURCES = $(foreach s, $(RAW_SOURCES), $(SOURCE_DIR)/$(s))

all: $(SOURCES)
	@rm -rf $(BIN_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(DOC_DIR)
	@javac $(SOURCES) -d $(BIN_DIR)
	@rm -f $(BIN_DIR)/Sudoku.jar
	@jar -cvfe bin/Sudoku.jar Main -C $(BIN_DIR) . > /dev/null
	@rm -f $(BIN_DIR)/*.class

submission: all
	@rm -f *.zip
	@echo ""
	@read -p "Enter Team Name (No spaces, '_', '/', '*'): " teamName; \
	 echo ""; \
	 zip -rqq s_$${teamName}.zip $(SOURCE_DIR) $(BIN_DIR) $(DOC_DIR)