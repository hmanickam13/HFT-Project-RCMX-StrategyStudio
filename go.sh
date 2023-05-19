#!/bin/bash

if [ -e iexdownloaderparser/parse_all.sh ]; then
	echo "Great! You properly cloned the repo using --recursive!"
else
	echo "ERROR! You didnt check out the repo correctly. You MUST use git clone --recursive (url); otherwise the sub repos dont get fetched too! (yes you can use additional commands instead but just do this instead)!"
	exit
fi

if [ -e ~/.ssh/id_rsa ]; then
	echo "You already have your ssh key! great!"
else
	echo "You need to run ssh-keygen -t rsa -b 4096 to generate a new public / private key and add to gitlab"
	exit
fi

if [ -e strategy_studio_ubuntu20_gcc940_sdk.3.4.0.0.tar.gz ]; then
	echo "Great! You already downloaded the Strategy Studio SDK"
else
	echo "You need to download strategy_studio_ubuntu20_gcc940_sdk.3.4.0.0.tar.gz and place it into the same directory as Vagrantfile before proceeding!"
	exit
fi

if [ -e strategy_studio_ubuntu20_gcc940_server_backtesting_upgrade.3.4.0.0.tar.gz ]; then
        echo "Great! You already downloaded the Strategy Studio Backtesting Engine!"
else
        echo "You need to download strategy_studio_ubuntu20_gcc940_server_backtesting_upgrade.3.4.0.0.tar.gz and place it into the same directory as Vagrantfile before proceeding!"
        exit
fi

if [ -e license.txt ]; then
	echo "Great! You already placed your license.txt file in this folder!"
else
	echo "ERROR! You need to place your personal license.txt file in the same folder as the Vagrantfile before proceeding!"
	exit
fi


# # Destroy the current VM if it exists
# if vagrant status | grep -q "default"; then
#     vagrant destroy -f
# 	echo "Destroyed VM because we want fresh state of sqlite dbs"
# fi

echo "All dependencies are met! Launching VM!!"
echo "Bringing up VM"

# the script sets specific environment variables related to Vagrant, such as disabling the checkpoint feature and defining the Vagrant home directory
source set_vagrant_env.sh

vagrant up
# The above command does the following things:
# 1. Reads the vagrant file
# 2. Checks the virtual machine status
# 3. Boots the VM if not running already
# 4. Configures the Virtual Machine

# Print the VMs which are currenty running
# vagrant global-status --prune
# vagrant global-status --prune | awk '/running/{print $2}'


if [ -e iexdownloaderparser/data/text_tick_data/tick_AAPL_20211105.txt.gz ]; then
	echo "Great! You've already generated the required market data!"
else
	echo "Market data has not yet been generated... generating now!"
	vagrant ssh -c 'cd /vagrant ; provision_scripts/generate_data.sh'
fi

if [ -e iexdownloaderparser/data/text_tick_data/tick_AAPL_20211105.txt.gz ]; then
        echo "Great! You've generated the required market data!"
else
        echo "ERROR! Something failed generating the marketdata; this can not be fixed automatically; consult the Professor"
	exit
fi

# vagrant ssh -c "pypy3 /vagrant/provision_scripts/delete_instance.py" 
vagrant ssh -c '/vagrant/provision_scripts/build_strategy.sh'
vagrant ssh -c '/vagrant/provision_scripts/run_backtest.sh'

