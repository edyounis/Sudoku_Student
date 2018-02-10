# ======================================================================
# FILE:        Makefile
#
# AUTHOR:      Abdullah Younis
#
# DESCRIPTION: This file contains useful commands for this project. You
#              may use the following commands:
#
#              - make            - compiles the project and places
#                                  the executable in the bin folder
#
#              - make submission - creates the the submission, you will
#                                  submit.
#
#              - Don't make changes to this file.
# ======================================================================

RAW_SOURCES = \
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
SOURCES = $(foreach s, $(RAW_SOURCES), $(SOURCE_DIR)/$(s))

all: $(SOURCES)
	@rm -rf $(BIN_DIR)
	@mkdir -p $(BIN_DIR)
	@javac $(SOURCES) -d $(BIN_DIR)
	@rm -f $(BIN_DIR)/Sudoku.jar
	@jar -cvfe bin/Sudoku.jar Main -C $(BIN_DIR) . > /dev/null
	@rm -f $(BIN_DIR)/*.class

submission: all
	@rm -f *.zip
	@echo ""
	@read -p "Enter Team Name (No spaces, '_', '/', '*'): " teamName; \
	 echo ""; \
	 zip -rqq s_$${teamName}.zip $(SOURCE_DIR) $(BIN_DIR)
