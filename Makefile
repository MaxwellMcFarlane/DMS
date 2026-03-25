#################################
## Date : 2025-05-27 08:22:16
## Author : Maxwell McFarlane
## Info : This Makefile manages all process used during the 2025 FPU Stage
#################################
############### File/Directories Definitions ##################
PRJDIR=~/Projects/Ganymede/digital
SCRIPTSDIR=${PRJDIR}/fpu_scripts
DDIR=${PRJDIR}/design
TDIR=${PRJDIR}/testcases
BDIR=${PRJDIR}/backend
CDIR=${PRJDIR}/constraints

MAKEDIR=${WDIR}/.make

############### Parameter Definitions ##################
# openhwgroup # pulp # khalidmamdou # nishthaparashar # dawsonjon # akilm # taneroksuz 
FPU = $(shell basename $$(pwd) | cut -d"_" -f2)
# PWD = $(shell pwd)
BLK_DDIR=${DDIR}/fpu_${FPU}
BLK_TDIR=${TDIR}/fpu_${FPU}
BLK_BDIR=${BDIR}/fpu_${FPU}
BLK_CDIR=${CDIR}/fpu_${FPU}
CONFIG=benchmark

############### Verification Definitions #################
WORK_DIR=${BLK_TDIR}/${CONFIG}/.work/sim

############### Synthesis Definitions #################
SDC_FILE=${BLK_CDIR}/timing/functional/clock_settings.tcl
SYN_RAWDIR=${BLK_BDIR}/.work/reports/syn_opt/
START_CLKPER=150
STOP_CLKPER=150
SYN_STEP=1

############### Tool Arguements Definitions #################
# SPECTRE_ARGS=\
# 	+config /comelec/softs/opt/Cadence/releases/SPECTRE211/tools.lnx86/spectre/etc/configs/spectre.cfg \
# 	-raw ${BLOCKDIR} \
# 	-format psfascii  \
# 	-outdir ${BLOCKDIR}

############### Recipes #################
all:
	@echo "compile  :  Compiles VHDL Code"
	@echo "gen_lib  :  Generates Timing Libraries"

test:
	@echo -e "\033[92mRunning Test \033[0m"
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

pre_plot:
	@echo "Plotting ${BLOCK} PreSynthesis Verification Results..."
	@today=$$(date -d today +"%Y%m%d");\
		mkdir -vp data/$$today;\
		cp ${WORK_DIR}/*csv data/$$today;\
		python3 ${SCRIPTSDIR}/presynth/plot.py ${FPU} ${BLK_TDIR}/plot.json data/$$today data/$$today 

post_plot:
	@echo "Plotting ${BLOCK} PostSynthesis Results..."
	@today=$$(date -d today +"%Y%m%d");\
		output_dir=data/$$today;\
		mkdir -vp $$output_dir;\
		cp ${WORK_DIR}/*csv data/$$today;\
		python3 ${SCRIPTSDIR}/postsynth/plot.py ${FPU} data/$$today data/$$today 

run_auto_syn:
	@echo "Running Auto-Synthesis [${BLOCK}] ..."
	@today=$$(date -d today +"%Y%m%d");\
		output_dir=data/$$today;\
		mkdir -vp $$output_dir;
	@echo "Script finished."

gen_tc:
	@echo "Generating Test Cases for ${BLOCK} ..."
	@cd ${TDIR}/testcases;\
		python3 ${SCRIPTSDIR}/generate_testcases.py ;
	@echo "Script finished."

$(MAKEDIR):
	@mkdir $(MAKEDIR) 

$(SETUP_FILE):
	@echo "ERROR:: Missing Setup File. Download from git repo..."

clean: 
	@echo "Cleaning Files/Directories"
	@rm -rf $(MAKEDIR) 
