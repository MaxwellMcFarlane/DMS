#################################
## Date : 2026-04-25
## Author : Maxwell McFarlane
## Info : This makefile is meant to control basic maintenance of the SCADA system.
#################################

############### File/Directories Definitions ##################
PRJDIR=.
SRCDIR=${PRJDIR}/src
# Full 2017 SCADA system (DMS + control subsystem)
SCADADIR=${PRJDIR}/legacy/scada_2017
GUIDIR=${SCADADIR}/scadagui

############### Recipes #################
all:
	@echo "example      :  Builds the DMS example (examples/scada_example)"
	@echo "run_example  :  Builds and runs the DMS example"
	@echo "scada        :  Builds and runs the full SCADA program (${SCADADIR}/scada)"
	@echo "example_clean:  Removes the example binary"
	@echo "gui          :  Builds the SCADA GUI (${GUIDIR}/scadagui.app)"
	@echo "run_gui      :  Builds and launches the SCADA GUI (same as bin/scada)"
	@echo "gui_clean    :  Removes GUI build artifacts"

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

# qmake's macx-clang mkspec links a -framework AGL that no longer ships with
# modern macOS SDKs; strip it from the generated Makefile before building.
gui:
	@echo "Building SCADA GUI..."
	@cd ${GUIDIR} && qmake scadagui.pro
	@cd ${GUIDIR} && sed -i.bak 's/ -framework AGL//' Makefile && rm -f Makefile.bak
	@cd ${GUIDIR} && $(MAKE)
	@echo "Built ${GUIDIR}/scadagui.app"

# cwd must be GUIDIR so the app's "../scada.db" etc. paths resolve correctly
run_gui: gui
	@cd ${GUIDIR} && ./scadagui.app/Contents/MacOS/scadagui

gui_clean:
	@echo "Removing GUI build artifacts..."
	@cd ${GUIDIR} && rm -rf *.o moc_* ui_* qrc_* Makefile .qmake.stash scadagui.app
