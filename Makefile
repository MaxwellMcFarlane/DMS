#################################
## Date : 2026-04-25
## Author : Maxwell McFarlane
## Info : This makefile is meant to control basic maintenance of the SCADA system.
#################################

############### File/Directories Definitions ##################
PRJDIR=.
SRCDIR=${PRJDIR}/src
GUIDIR=${PRJDIR}/gui

.PHONY: all clean example run_example control_example run_control_example gui run_gui gui_clean

############### Recipes #################
all:
	@echo "example        :  Builds the DMS console example (examples/scada_example)"
	@echo "run_example    :  Builds and runs the DMS console example"
	@echo "control_example:  Builds the control-subsystem console example (examples/control_example)"
	@echo "run_control_example: Builds and runs the control-subsystem console example"
	@echo "gui            :  Builds the SCADA GUI (${GUIDIR}/scadagui.app)"
	@echo "run_gui        :  Builds and launches the SCADA GUI (same as bin/scada)"
	@echo "gui_clean      :  Removes GUI build artifacts"

clean: gui_clean
	@echo "Cleaning generated runtime artifacts"
	@rm -f examples/scada_example examples/control_example examples/dms.log \
	       log.txt control_log.txt control_error.txt scada.db data.csv data1.csv data2.csv

example:
	@echo "Building SCADA DMS example..."
	@cd examples && g++ -std=c++17 main.cpp ../src/dms.cpp ../src/table.cpp ../libs/log.cpp -I../src -I../libs -lsqlite3 -o scada_example
	@echo "Built examples/scada_example"

# Run from examples/ so the ../scada.db, ../configuration_files and ../testbench_files paths resolve
run_example: example
	@cd examples && ./scada_example

control_example:
	@echo "Building SCADA control-subsystem example..."
	@cd examples && g++ -std=c++17 control_main.cpp ../src/dms.cpp ../src/table.cpp \
		../src/control/branch.cpp ../src/control/state.cpp ../src/control/modemanager.cpp \
		../libs/log.cpp -I../src -I../libs -lsqlite3 -o control_example
	@echo "Built examples/control_example"

run_control_example: control_example
	@cd examples && ./control_example

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
