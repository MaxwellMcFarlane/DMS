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

############### Recipes #################
all:
	@echo "example      :  Builds the DMS example (examples/scada_example)"
	@echo "run_example  :  Builds and runs the DMS example"
	@echo "scada        :  Builds and runs the full SCADA program (${SCADADIR}/scada)"
	@echo "example_clean:  Removes the example binary"

clean:
	@echo "Cleaning generated runtime artifacts"
	@rm -f examples/scada_example examples/dms.log log.txt scada.db data.csv data1.csv data2.csv

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
