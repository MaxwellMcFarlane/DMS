#################################
## Date : 2026-04-25
## Author : Maxwell McFarlane
## Info : This makefile is meant to control basic maintenance of the SCADA system.
#################################

############### File/Directories Definitions ##################
PRJDIR=.
SRCDIR=${PRJDIR}/src
RUNDIR=${PRJDIR}/run # Work Directory
############### Parameter Definitions ##################
FPU = $(shell basename $$(pwd) | cut -d"_" -f2)
TOOL = "gcc"
ARGS = "-std=c++11 -I./src -lsqlite3"

############### Recipes #################
all:
	@echo "compile  :  Compiles VHDL Code"
	@echo "gen_lib  :  Generates Timing Libraries"

test:
	@echo -e "\033[92m Running Test \033[0m"
	@today=$$(date -d today +"%Y%m%d"); echo "Todays Date : $$today"
	@echo -e "\
		Current FPU : ${FPU}\n\
		Working Design Dir. : ${BLK_DDIR}\n\
		Working Test Dir. : ${BLK_TDIR}\n\
		Working Backend Dir. : ${BLK_BDIR}\n\
		Working Constraints Dir. : ${BLK_CDIR}\
	";
	@echo -e "\033[91mFinished Test \033[0m"
	@echo ${WORK_DIR}

clean: 
	@echo "Cleaning Files/Directories"
	@rm -rf $(MAKEDIR) 

example:
	@echo "Building SCADA example..."
	@cd examples && g++ -std=c++17 main.cpp ../src/dms.cpp ../src/table.cpp ../tools/log.cpp -I../src -I../tools -lsqlite3 -o scada_example
	@echo "Built examples/scada_example"

example_clean:
	@echo "Removing example binary..."
	@rm -f examples/scada_example
