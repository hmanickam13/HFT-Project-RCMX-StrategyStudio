#!/bin/bash

# Enter the dates you want to backtest
startDate='2021-11-05'
endDate='2021-11-05'

# Enter the name of the instance you created
instanceName='InstanceName2'

# Putting the code in parenthesis ( ... ) creates a subshell environment. Read what subshell env is and how it works
(cd /home/vagrant/ss/bt && ./StrategyServerBacktesting&)

# echo means print
echo "Sleeping for 2 seconds while waiting for strategy studio to boot"
sleep 2

# Start the backtest
(cd /home/vagrant/ss/bt/utilities/ && ./StrategyCommandLine cmd start_backtest $startDate $endDate $instanceName 0)

# Get the line number which ends with finished. 
foundFinishedLogFile=$(grep -nr "finished.$" /home/vagrant/ss/bt/logs/main_log.txt | gawk '{print $1}' FS=":"|tail -1)

# DEBUGGING OUTPUT
echo "Last line found:",$foundFinishedLogFile

# If the line ending with finished. is less than the previous length of the log file, then strategyBacktesting has not finished, 
# once its greater than the previous, it means it has finished.
while ((logFileNumLines > foundFinishedLogFile))
do
    foundFinishedLogFile=$(grep -nr "finished.$" /home/vagrant/ss/bt/logs/main_log.txt | gawk '{print $1}' FS=":"|tail -1)

    #DEBUGGING OUTPUT
    echo "Waiting for strategy to finish"
    sleep 1
done

echo "Sleeping for 10 seconds..."

sleep 10

echo "run_backtest.sh: Strategy Studio finished backtesting"


# Read about CRA file format
# List all the files in the specific directory and matches the pattern/format BACK_TestOldStrategy*.cra
# Then -t sorts the file by modification time, newest first. head -n1 chooses the first file in the list
# Assign the file to a variable to convert into a csv format
latestCRA=$(ls /home/vagrant/ss/bt/backtesting-results/BACK_*.cra -t | head -n1)

# Print the path of the craFile
echo "CRA file found:", $latestCRA

# Navigate to utilities directory
cd /home/vagrant/ss/bt/utilities/

# Use the StrategyCommandLine utility to eport the CRA file to CSV format
# Name of file should be the latest craFile created
./StrategyCommandLine cmd export_cra_file $latestCRA ~/ss/bt/backtesting-results/csv_files

# echo 
# Run the export command to generate csv files
# /home/vagrant/ss/bt/utilities/./StrategyCommandLine cmd export_cra_file backtesting-results/$latestCRA backtesting-cra-exports

# We get our results in a cra file format.
# We export it to a specific path inside VM diretory
# This file will be converted to csv file to a new directory next to the directory the cra file is being created. This is done in the last few lines of run_backtest.sh
# ./StrategyCommandLine cmd export_cra_file ~/ss/bt/backtesting-results/BACK_InstanceName_2023-04-25_012556_start_11-05-2021_end_11-05-2021.cra ~/ss/bt/backtesting-results/backtesting-cra-exports

