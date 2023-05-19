# What does this line do?
#!/bin/bash

# This line just navigates to a folder inside vagrant once its launched
# Do not change
cd /home/vagrant/ss/sdk/RCM/StrategyStudio/examples/strategies/

# We delete directory because we want te git repo to be cloned fresh everytime
rm -r group_01_project

# This line just clones the repo containing the strategy
# Change according to requirement
git clone -b hariharan git@gitlab.engr.illinois.edu:ie421_high_frequency_trading_spring_2023/ie421_hft_spring_2023_group_01/group_01_project.git
# This clone should be made once in total. This will not work the second time you run ./go.sh if you do not delete the directory created the first time. That's why the rm -r line is super important
# Is there a way to work around this without removing the git repo? maybe git pull or smth???
# If you want to run ./go.sh without restarting the VM, you can. You sould just comment this line and run everything as is. Else you will get error stating folder already exists

# View the list of files. Used during debugging
# ls

# Navigate inside the folder once you clone the repo
# Change according to your file organization
# The final folder should contain the makefile, .h and .cpp file
cd group_01_project/test_strategy

# View the list of files. Used during debugging
# ls

# Create a directory to store our strategy
mkdir -p /home/vagrant/ss/bt/strategies_dlls

# View the list of files. Used during debugging
# ls

# Create a copy of our strategy???
make copy_strategy

# Navigate inside folder. Why this folder?
# Runs ./StrategyServerBacktesting as a background process. Then sleep 1 pauses the script for 1 second giving the Server process time to start up before any additional commands are executed
cd /home/vagrant/ss/bt/ ; ./StrategyServerBacktesting &
sleep 1
# Navigate inside utilities folder. Why this folder?
cd /home/vagrant/ss/bt/utilities

# Create an instance "InstanceName" for the strategy .cpp file "StrategyFileName". 
# What is "UIUC SIM-1001-101 dlariviere 1000000"???
# -symbols mean what all symbols we want to test our strategy on
./StrategyCommandLine cmd create_instance InstanceName Test_Strategy UIUC SIM-1001-101 dlariviere 1000000 -symbols AAPL

# View all the instances.
# Used to debug
# ./StrategyCommandLine cmd strategy_instance_list

# Start our backtest for the instance "InstanceName" we created
./StrategyCommandLine cmd start_backtest 2021-11-05 2021-11-05 InstanceName 0

# Is this line needed? Does this quit backtesting the instance or quit Strategy studio completely?
# ./StrategyCommandLine cmd quit



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