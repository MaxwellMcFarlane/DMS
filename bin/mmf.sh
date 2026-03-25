#!/bin/bash
#################################
## Date : 2025-05-27 08:22:16
## Author : Maxwell McFarlane
## Info : This Makefile manages all process used during the 2025 FPU Stage
#################################

# ############## Starting Message             ##################
# echo -e "Running Script"

############## File/Directories Definitions ##################
prjdir=~/Projects/Ganymede/digital
scriptsdir=${prjdir}/fpu_scripts
ddir=${prjdir}/design
tdir=${prjdir}/testcases
bdir=${prjdir}/backend
cdir=${prjdir}/constraints

############### parameter definitions ##################
# openhwgroup # pulp # khalidmamdou # nishthaparashar # dawsonjon # akilm # taneroksuz 
basename=$(basename $(pwd))
fpu=$(basename $(pwd) | cut -d"_" -f2)
blk_ddir=${ddir}/fpu_${fpu}
blk_tdir=${tdir}/fpu_${fpu}
blk_bdir=${bdir}/fpu_${fpu}
blk_cdir=${cdir}/fpu_${fpu}

############### Function Definitions  ##################

# Test Example Code - Greets User
greet_user() {
  local name="$1" # 'local' makes the variable scope limited to the function
  if [[ -z "$name" ]]; then
    echo "Hello there! Please provide a name."
  else
    echo "Hello, $name! Welcome."
  fi
}

# This function descibes the script functionality 
help_user() {
    echo -e "Usage: 
    [-v|--verbose] 
    [-h|--help] 
    [-n|--new] 
    [-r <pre|post>|--report <pre|post>] 
    [-d|--describe] 
    [-g|--gentest] 
    [-t|--test] 
    [-c <dirname>|--config <dirname>]
    [-a |--autosyn : --max <max_clk_period> --min <min_clk_period> --step <sim_step_size>]"
}

# This function pauses the script before further use and with confirmation
ask_yes_no() {
  local question="$1" # Store the question string
  local reply         # Variable to store user's reply

  while true; do # Loop indefinitely until a valid reply is given
    # Prompt the user for input
    read -p "$question (y/n): " reply

    # Convert the reply to lowercase for case-insensitive comparison
    case "${reply,,}" in # Use "${reply,,}" for bash 4+, otherwise convert manually
      y|yes)
        echo "Reply: Yes. Continuing script."
        return 0 # Exit the function, allowing the script to proceed
        ;;
      n|no)
        echo "Reply: No. Exiting script."
        exit 0 # Exit the entire script with a success status
        ;;
      *) # Default case for invalid input
        echo "Invalid input. Please answer 'y' or 'n'."
        ;;
    esac
  done
}

# This function checks if path is valid
check_fpu_path() {
    local path="$1" # 'local' makes the variable scope limited to the function
    if [[ ! -d $path ]]; then
      	echo -e "$path does not exist."
      	echo -e "Not a valid FPU directory. Please use script in \"fpu_*\" directory."
		exit 1
    fi
}

# Get latest valid data for either (pre|post) analysis
get_latest_data() {
    local path="$1" # 'local' makes the variable scope limited to the function
    check_fpu_path $blk_ddir
    check_fpu_path $path
    latest_data=$(ls -d $path/*/ | sort | tail -n1)
    echo $latest_data
}

# Describes FPU Working Directory
describe_fpu() {
    check_fpu_path $blk_ddir

    # Execution
    echo -e "\
    Current fpu              : ${fpu}\n\
    Config(s)                : ${config}\n\
    working design dir.      : ${blk_ddir}\n\
    working test dir.        : ${blk_tdir}\n\
    working backend dir.     : ${blk_bdir}\n\
    working constraints dir. : ${blk_cdir}\
    ";

}

# Add check for if this command is used in the correct directory (if not break the execution)
# Arguements should include whether to create a new directory (date-stamped) or to use latest for plotting (default)
rpt_presynth() {
    local n_flag="$1" # 'local' makes the variable scope limited to the function
    check_fpu_path $blk_tdir
    cd $blk_tdir

    today=$(date -d today +"%Y%m%d");
    dpath="$(get_latest_data $blk_tdir/$config/data)" # Check for the latest data set in testcases directory
    if [[ "$n_flag" == true || "$dpath" == "" ]]; then
        echo -e "Creating New Data Set"
        mkdir -vp $blk_tdir/$config/data/$today;
        # cp -v ${blk_tdir}/$config/.work/sim/*csv $blk_tdir/$config/data/$today;
        cp -v ${blk_tdir}/.work/$config/sim/*csv $blk_tdir/$config/data/$today;
    fi
    dpath="$(get_latest_data $blk_tdir/$config/data)" # Check for the latest data set in testcases directory
    
    # Execution
    echo -e "Generating Report Configuration : $config"
    echo -e "Reporting PreSynthesis Verification Results:\n\t$fpu -> $dpath"
    python3 ${scriptsdir}/presynth/plot.py ${fpu} ${blk_tdir}/${config}/plot.json $dpath $dpath
}

# Add check for if this command is used in the correct directory (if not break the execution)
# Arguements should include whether to create a new directory (date-stamped) or to use latest for plotting (default)
rpt_postsynth() {
    local n_flag="$1" # 'local' makes the variable scope limited to the function
    local fpus="$2"
    echo -e "Generating Post Sythesis Reports for : $fpus"
    # check_fpu_path $blk_bdir
    # cd $blk_bdir
    cd $scriptsdir/postsynth
    path=$(pwd)/data

    today=$(date -d today +"%Y%m%d");
    dpath=$(ls -d $path/*/ | sort | tail -n1)
    if [[ "$n_flag" == true  || "$dpath" == "" ]]; then
        echo -e "Creating New Data Set"
        mkdir -vp $path/$today;
        # cp -v ${blk_bdir}/.work/$config/sim/*csv $blk_bdir/$config/data/$today;
    fi
    dpath=$(ls -d $path/*/ | sort | tail -n1)
    
    # Execution
    echo -e "Generating Report Configuration : $config"
    echo -e "Reporting PostSynthesis Verification Results:\n\t$fpu -> $dpath"
    areas="TotalArea(um^2) AdderArea(um^2) SubtractorArea(um^2) MultiplierArea(um^2) DividerArea(um^2) SquareRootArea(um^2) FmacArea(um^2)"
    python3 ${scriptsdir}/postsynth/plot.py "${fpus}" ${scriptsdir}/postsynth/plot.json $dpath "${areas}"
    # python3 ${scriptsdir}/postsynth/plot.py ${fpu} ${blk_bdir}/${config}/plot.json $dpath $dpath
}

# Add check for if this command is used in the correct directory (if not break the execution)
# Arguements should include whether to create a new directory (date-stamped) or to use latest for plotting (default)
gen_testcases() {
    local n_flag="$1" # 'local' makes the variable scope limited to the function
    check_fpu_path $blk_tdir/testcases/outputs
    # cd $blk_tdir/testcases/outputs

    today=$(date -d today +"%Y%m%d");
    
    # Execution
    echo -e "Generating TestCases Vectors for Verification:\n\t$fpu "
    python3 ${scriptsdir}/presynth/generate_testcase.py ${fpu} ${blk_tdir}/${config}/plot.json $blk_tdir/testcases/outputs/
}

# This function runs the synthesis steps automatically to generate the reports required for post-synthesis analysis  
auto_syn() {
    local n_flag="$1" # 'local' makes the variable scope limited to the function
    check_fpu_path $blk_bdir
    cd $blk_bdir

    # Create new directory if prompted
    today=$(date -d today +"%Y%m%d");
    dpath="$(get_latest_data $blk_tdir/$config/data)" # Check for the latest data set in testcases directory
    if [[ "$n_flag" == true || "$dpath" == "" ]]; then
        echo -e "Creating New Data Set"
        mkdir -vp $blk_bdir/$config/data/$today;
        cp -v ${blk_bdir}/.work/$config/sim/*csv $blk_bdir/$config/data/$today;
    fi
    dpath="$(get_latest_data $blk_bdir/$config/data)" # Check for the latest data set

    # Execution
    settings_file="$blk_cdir/timing/functional/clock_settings.tcl"
    results_dir=".work/reports/syn_opt/"
    run_log="$blk_bdir/auto_syn.log"

    # Loop through the specified number of cycles
    num_cycles=$(echo "($max_clk_period-$min_clk_period)/$step" | bc)
    echo -e "Auto Synthesis Settings (Constraint File) : $settings_file"
    echo -e "Auto Synthesis Settings (Max Clock Period) : $max_clk_period"
    echo -e "Auto Synthesis Settings (Min Clock Period) : $min_clk_period"
    echo -e "Auto Synthesis Settings (Step Size) : $step"
    echo -e "Auto Synthesis Settings (Number of Steps) : $num_cycles"
    ask_yes_no "Would you like to continue to synthesis?"

    base_command="run syn"
    for i in $(seq 1 "$num_cycles"); do
        clock_period=$(echo "$max_clk_period - ($i-1) * $step" | bc) # Calculate the clock period for this cycle (you can adjust the logic here)
        sed -ir "s/\(set clock_period\) .*/\1 $clock_period/g" $settings_file # Construct the command with the current clock period
        # output_file="${dpath}output_${clock_period}.txt" # Construct the output filename

        echo "Running: $base_command"
        $base_command # Run the command and redirect the output to the file
        sleep 10 # In case is is a latency issue in the network
        cp -vr $results_dir "${dpath}clk_${clock_period}_ns" # Copy results to directory
        echo "Output saved to: ${dpath}clk_${clock_period}_ns"
    done
}

# This function creates a summary file of all the synthesis generated reports before compilation  
# It is required that a data directory already exists in the fpu folder
scrape_synrpt() {
    local n_flag="$1" # 'local' makes the variable scope limited to the function
    check_fpu_path $blk_bdir
    cd $blk_bdir
    
    dpath="$(get_latest_data $blk_bdir/$config/data)" # Check for the latest data set

    # Execution
    results_dir=".work/reports/syn_opt/"
    search_path="${dpath}"
    today=$(date -d today +"%Y%m%d");
    
    # Generate CSV File
    csv_report="${dpath}/postsyn_${fpu}.csv"
    if [ ! -f "$csv_report" ]; then
      touch $csv_report 
    fi
    
    ## Execution
    # Initialize Report : Table Columns
    echo -e "Constraints,Version,Snapshot,Setup(WNS[ps]),Insts,TotalArea(um^2),AdderArea(um^2),SubtractorArea(um^2),MultiplierArea(um^2),DividerArea(um^2),SquareRootArea(um^2),FmacArea(um^2),ClockPeriod(ns),ClockSpeed(MHz),Wall(s),OperandWidth,Parameters,Database,Reports?" > $csv_report
    constraints="v1.1"
    version=$constraints
    snapshot="syn_opt"
    wallt=""
    operandwidth=$(jq ".${fpu}.operand_width" ${config}/plot.json )
    params=""
    dbs=""
    reportsq=""

    # Area Summary Report Variables
    top_module=$(jq ".${fpu}.top_module_name" ${config}/plot.json )
    adder_module=$(jq ".${fpu}.adder_module_name" ${config}/plot.json )
    subtractor_module=$(jq ".${fpu}.subtractor_module_name" ${config}/plot.json )
    multiplier_module=$(jq ".${fpu}.multiplier_module_name" ${config}/plot.json )
    divider_module=$(jq ".${fpu}.divider_module_name" ${config}/plot.json )
    squareroot_module=$(jq ".${fpu}.squareroot_module_name" ${config}/plot.json )
    fmac_module=$(jq ".${fpu}.fmac_module_name" ${config}/plot.json )

    # Use find to locate directories within the specified path
    find "$search_path" -type d -print0 | while IFS= read -r -d $'\0' directory; do
        if [[ "${directory}" == "${search_path}" ]]; then
          echo "Found Search Path"
          continue
        fi
        echo "Generating Report for : ${directory}"
        # basename=$(echo ${directory} | cut -d"/" -f2)
        basename=$(echo ${directory} | cut -d'/' -f1- | awk -F'/' '{print $NF}')
        clock_period=$(echo ${basename} | cut -d"_" -f2)
        freq=$(echo "scale=3; 1000/${clock_period}" | bc)
        timingfile="${directory}/setup.worst.rpt"
        areafile="${directory}/area.gates.rpt"
        areapartsfile="${directory}/area.summary.rpt"
        echo -e "$basename -> $clock_period \n\t|-->Search Files : ($timingfile, $areafile)"

        # Parse Timing Report
        setup=$(grep -r "Slack" ${timingfile} | sed 's/ \+/ /g' | sed 's/:=/,/g' | cut -d',' -f2)

        # Parse Area Report
        raw_row=$(grep "total" ${areafile} | tail -n 1 | sed 's/ \+/,/g')
        total_insts=$(echo $raw_row| cut -d',' -f2)
        # total_area=$(echo $raw_row | cut -d',' -f3)
        total_leakage=$(echo $raw_row | cut -d',' -f5)
        total_internal=$(echo $raw_row | cut -d',' -f7)

        # Parse Area Summary Report
        total_area=$(eval "grep ${top_module} ${areapartsfile} | tail -n 1 | sed 's/ \+/,/g' | cut -d',' -f5")
        adder_area=$(eval "grep ${adder_module} ${areapartsfile} | head -n 1 | sed 's/ \+/,/g' | cut -d',' -f7")
        subtractor_area=$(eval "grep ${subtractor_module} ${areapartsfile} | head -n 1 | sed 's/ \+/,/g' | cut -d',' -f7")
        multiplier_area=$(eval "grep ${multiplier_module} ${areapartsfile} | head -n 1 | sed 's/ \+/,/g' | cut -d',' -f7")
        divider_area=$(eval "grep ${divider_module} ${areapartsfile} | head -n 1 | sed 's/ \+/,/g' | cut -d',' -f7")
        squareroot_area=$(eval "grep ${squareroot_module} ${areapartsfile} | head -n 1 | sed 's/ \+/,/g' | cut -d',' -f7")
        fmac_area=$(eval "grep ${fmac_module} ${areapartsfile} | head -n 1 | sed 's/ \+/,/g' | cut -d',' -f7")

        #Add row to table
        row="$constraints,$version,$snapshot,\
          $setup,$total_insts,$total_area,\
          $adder_area,$subtractor_area,$multiplier_area,$divider_area,$squareroot_area,$fmac_area,\
          $clock_period,\
          $freq,$wallt,$operandwidth,\
          $params,$dbs,$reportsq"
        echo -e "${row}" >> $csv_report

    done

    sed -i 's/ \+//g' $csv_report #Remove any spaces
}

############### Parse Arguements (getopt) #############
# Initialize variables
VERBOSE=0
REPORT_TYPE=""
HELP=0
n_flag=false
RPT_FLAG=false
SYN_FLAG=false
config=benchmark

# Auto Synthesis Default Settings
max_clk_period=0
min_clk_period=0
step=0

# Default FPUs for post synthesis reporting
fpus="openhwgroup chipware pulp dawsonjon dinneshannayya"

# Define short and long options
# Short: v (no arg), f: (requires arg), h (no arg)
# Long: verbose (no arg), file: (requires arg), help (no arg)
OPTIONS="vhnr:dgtc:as"
LONGOPTIONS="verbose,help,new,report:,describe,gentest,test,config:,autosyn,max:,min:,step:,scrape,fpus:"

# Parse options using getopt
# The 'eval set --' is crucial for correctly handling spaces and quotes
# in arguments after getopt processes them.
PARSED_OPTIONS=$(getopt -o "$OPTIONS" --long "$LONGOPTIONS" -n "$0" -- "$@")

# Check for parsing errors
if [ $? -ne 0 ]; then
    echo "Terminating..." >&2
    exit 1
fi

# Set the positional parameters to the parsed options
eval set -- "$PARSED_OPTIONS"

# Loop through the parsed options
while true; do
  case "$1" in
    -v|--verbose)
        VERBOSE=1
        echo "Verbose mode enabled."
        shift
        ;;
    -h|--help)
        HELP=1
        help_user
        exit 0
        ;;
    -n|--new)
        n_flag=true # New flag means that the script generates a new directory for data/plotting
        shift
        ;;
    -r|--report)
        REPORT_TYPE="$2"
        RPT_FLAG=true
        shift 2 # Shift twice: once for the option, once for its argument
        ;;
    -d|--describe)
        describe_fpu
        shift
        ;;
    -g|--gentest)
        gen_testcases
        shift
        ;;
    -t|--test)
        greet_user $(echo -e $USER)
        shift
        ;;
    -c|--config)
        config="$2"
        shift 2 # Shift twice: once for the option, once for its argument
        ;;
    -a|--autosyn)
        SYN_FLAG=true
        shift
        ;;
    --max)
        max_clk_period="$2"
        shift 2 # Shift twice: once for the option, once for its argument
        ;;
    --min)
        min_clk_period="$2"
        shift 2 # Shift twice: once for the option, once for its argument
        ;;
    --step)
        step="$2"
        shift 2 # Shift twice: once for the option, once for its argument
        ;;
    --fpus)
        fpus="$2"
        shift 2 # Shift twice: once for the option, once for its argument
        ;;
    -s|--scrape)
        scrape_synrpt
        shift
        ;;
    --) # End of options
        shift
        break
        ;;
    *) # Should not happen
        echo "Internal error!" >&2
        exit 1
        ;;
  esac
done

# Now, process any remaining non-option arguments
if [ -n "$1" ]; then
  echo "Remaining arguments: $@"
fi

# Example of using the processed options
if [ "$VERBOSE" -eq 1 ]; then
  echo "Script is running in verbose mode."
fi

# if [ -n "$FILENAME" ]; then
#   echo "Processing file: $FILENAME"
#   # Add your file processing logic here
# fi

############### Reporting and Plotting Proc ##############
# Execute Reporting/Plotting if option is selected
if [[ "$RPT_FLAG" == "true" ]]; then
    if [[ "$REPORT_TYPE" =~ "pre" ]]; then
        rpt_presynth $n_flag
    fi
    if [[ "$REPORT_TYPE" =~ "post" ]]; then
        # echo -e "Generating Post Sythesis Reports for : $fpus"
        rpt_postsynth $n_flag "$fpus"
    fi
fi

# Auto Synthesis Procedure
if [[ "$SYN_FLAG" == "true" ]]; then
    # defining variables correctly
    if (( $max_clk_period <= 0 )); then
        echo -e "Max Clock Period Improperly Defined"
        help_user
        exit 1
    elif (( $min_clk_period <= 0 )); then
        echo -e "Min Clock Period Improperly Defined"
        help_user
        exit 1
    elif (( $step <= 0 )); then
        echo -e "Simulation Step Improperly Defined"
        help_user
        exit 1
    fi

    # max_clk_period cannot be less than min_clk_period
    if (( $max_clk_period <= $min_clk_period )); then
        echo -e "Max clock period cannot be less than min clk period"
        help_user
        exit 1
    fi

    auto_syn
fi


# if [[ ! "$REPORT_TYPE" == "" ]]; then # If reporting isn't invoked don't report invalid option
#   	echo -e "invalid arguement used for reporting"
#     exit 1
# fi

# ############### Verification Definitions #################
# WORK_DIR=${BLK_TDIR}/${CONFIG}/.work/sim

# ############### Synthesis Definitions #################
# SDC_FILE=${BLK_CDIR}/timing/functional/clock_settings.tcl
# SYN_RAWDIR=${BLK_BDIR}/.work/reports/syn_opt/
# START_CLKPER=150
# STOP_CLKPER=150
# SYN_STEP=1
# # SYN_RPTS=\
# #     ${BDIR}/fpu_dineshannayya/data/20250527
# # ${BDIR}/fpu_openhwgroup/data/20250527

# run_auto_syn:
#   @echo "Running Auto-Synthesis [${BLOCK}] ..."
#   @today=$$(date -d today +"%Y%m%d");\
#       output_dir=data/$$today;\
#       mkdir -vp $$output_dir;
#   @echo "Script finished."