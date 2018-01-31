# ======================================================================
# FILE:        Makefile
#
# AUTHOR:      Abdullah Younis
#
# DESCRIPTION: This file contains useful commands for this project. You
#              may use the following commands:
#
#              - make            	- Generate a set of boards.
# ======================================================================

all:
	@-rm -rf Boards
	@-mkdir Boards
	@echo ""
	@read -p "Enter p: " rDim; \
	 echo ""; \
	 read -p "Enter q: " cDim; \
	 echo ""; \
	 read -p "Enter given values: " vDim; \
	 echo ""; \
	 read -p "How many boards created?: " count; \
	 echo ""; \
	 python3 board_generator.py Boards/board $${count} $${rDim} $${cDim} $${vDim}
