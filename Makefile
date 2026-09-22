#################################
## Date : 2026-04-25
## Author : Maxwell McFarlane
## Info : This makefile is meant to control basic maintenance of the SCADA system.
#################################

############### File/Directories Definitions ##################
PRJDIR=.
SRCDIR=${PRJDIR}/src
# Full 2017 SCADA system (DMS + control subsystem)
SCADADIR=${SRCDIR}/scada_repo/scada_repo
RUNDIR=${PRJDIR}/run # Work Directory
############### Parameter Definitions ##################
FPU = $(shell basename $$(pwd) | cut -d"_" -f2)
TOOL = "gcc"
ARGS = "-std=c++11 -I./src -lsqlite3"

############### Recipes #################
all:
	@echo "example      :  Builds the DMS example (examples/scada_example)"
	@echo "run_example  :  Builds and runs the DMS example"
	@echo "scada        :  Builds and runs the full SCADA program (${SCADADIR}/scada)"
	@echo "example_clean:  Removes the example binary"

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
	@cd examples && g++ -std=c++17 main.cpp ../src/dms.cpp ../src/table.cpp ../libs/log.cpp -I../src -I../libs -lsqlite3 -o scada_example
	@echo "Built examples/scada_example"

# Run from examples/ so the ../scada.db, ../configuration_files and ../testbench_files paths resolve
run_example: example
	@cd examples && ./scada_example

scada:
	@${SCADADIR}/run_scada.sh

example_clean:
	@echo "Removing example binary..."
	@rm -f examples/scada_example
