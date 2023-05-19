# What does this line do?
#!/bin/bash

# This line just navigates to a folder inside vagrant once its launched
# Do not change
cd /home/vagrant/ss/sdk/RCM/StrategyStudio/examples/strategies/

REPO_DIR="group_01_project"

# Check if the repository directory exists
if [ -d "$REPO_DIR" ]; then
    # Repository directory exists, perform git pull
    cd "$REPO_DIR"
    git pull
    cd ..
    echo "We pulled the repo."
else
    # Repository directory doesn't exist, clone the repository
    git clone -b hariharan git@gitlab.engr.illinois.edu:ie421_high_frequency_trading_spring_2023/ie421_hft_spring_2023_group_01/group_01_project.git "$REPO_DIR"
    echo "We created the repo."
fi

# View the list of files. Used during debugging
# ls

# Navigate inside the folder once you clone the repo
# Change according to your file organization
# The final folder should contain the makefile, .h and .cpp file
cd group_01_project/1_SMA_strategy

# Call the python script which accesses the sqlite3 db and delete's the instance if it exists
# pypy3 delete_instance.py InstanceName
# This doesn't work. Table not found in db

# View the list of files. Used during debugging
# ls

# Create a directory to store our strategy
mkdir -p /home/vagrant/ss/bt/strategies_dlls

# View the list of files. Used during debugging
# ls

# Create a copy of our strategy???
make copy_strategy


# delete instance called InstanceName. 'InstanceName' is the name of our strategy
# cd /vagrant/provision_scripts
# Call the python script which accesses the sqlite3 db and delete's the instance if it exists
# pypy3 delete_instance.py InstanceName

# Navigate inside folder. Why this folder?
# Runs ./StrategyServerBacktesting as a background process. Then sleep 1 pauses the script for 1 second giving the Server process time to start up before any additional commands are executed
cd /home/vagrant/ss/bt/ ; ./StrategyServerBacktesting &
sleep 1
# Navigate inside utilities folder. Why this folder?
cd /home/vagrant/ss/bt/utilities

# Create an instance "InstanceName" for the strategy .cpp file "StrategyFileName". 
# What is "UIUC SIM-1001-101 dlariviere 1000000"???
# -symbols mean what all symbols we want to test our strategy on
./StrategyCommandLine cmd create_instance InstanceName2 SMA_Strategy UIUC SIM-1001-101 dlariviere 1000000 -symbols AAPL
# Where are all these created?
# Open the file manager on the booted VM. USe vagrant as username and password and create a ssession
# Navigate to the following path, home/vagrant/ss/bt/strategies_dlls
#  Your new strategy 

# View all the instances.
# Used to debug
./StrategyCommandLine cmd strategy_instance_list

# Start our backtest for the instance "InstanceName" we created
./StrategyCommandLine cmd start_backtest 2021-11-05 2021-11-05 InstanceName2 0

# Is this line needed? Does this quit backtesting the instance or quit Strategy studio completely?
./StrategyCommandLine cmd quit



# XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

# Below is the original build_strategy.sh file. Uncomment all lines below once. bin/bach line was commented in original file
# #!/bin/bash
# cd /home/vagrant/ss/sdk/RCM/StrategyStudio/examples/strategies/
# git clone git@gitlab.engr.illinois.edu:shared_code/example_trading_strategies/dia_index_arb_strategy.git
# cd dia_index_arb_strategy
# mkdir -p /home/vagrant/ss/bt/strategies_dlls
# make copy_strategy
# cd /home/vagrant/ss/bt/ ; ./StrategyServerBacktesting &
# sleep 1
# cd /home/vagrant/ss/bt/utilities
# ./StrategyCommandLine cmd create_instance TestOneDiaIndexArbStrategy DiaIndexArbStrategy UIUC SIM-1001-101 dlariviere 1000000 -symbols "DIA|UNH|GS|HD|MSFT|CRM|MCD|HON|BA|V|AMGN|CAT|MMM|NKE|AXP|DIS|JPM|JNJ|TRV|AAPL|WMT|PG|IBM|CVX|MRK|DOW|CSCO|KO|VZ|INTC|WBA|KD"
# ./StrategyCommandLine cmd strategy_instance_list
# ./StrategyCommandLine cmd quit