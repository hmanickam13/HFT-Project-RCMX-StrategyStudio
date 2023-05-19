## Testing Strategies on RCMX Strategy Studio
RCMX Strategy Studio is a software platform designed for developing and backtesting high-frequency trading (HFT) strategies. This Git repository provides instructions on how to install Strategy Studio and perform backtesting of HFT strategies. It also includes example strategies that can be used to gain a better understanding of the platform and develop trading strategies. The repository serves as a comprehensive guide for setting up and utilizing Strategy Studio for quantitative trading purposes.

## Introduction
- This repo contains all the files you need to run RCMX Strategy Studio.
- Note: You need a valid license. Contact Professor David for information about licenses.
- Note: Use ChatGPT, watch videos, consult the TA, only then you shall contact the Professor for any questions during completion of the first assignment.

## Installation - Windows
- Install vagrant
- Install virtualbox 6.1.40
- Install cygwin from link with string "rit" in it (installation should occur without any problems).
- Watch a video on youtube how to install cygwin and choose packages during installation. Althogh the version might be very old, the process is the same.
- Cygwin asks you to choose packages you want to install:
- Install git
- Install openssh
- Note: Don't worry if you missed any package, you can run the setup.exe file again, it will take you through the EXACT same steps, now, in the package manager page, you can uninstall, reinstall, modify version of current packages and install new packages. Just complete the installation exactly the way you did it the first time.

## Setup
- We need to generate 2 seperate SSH connections to Gitlab.
1. Host Machine to Gitlab:<br>
This connection is for you to create and modify HFT strategies on your local machine, push them to your repository so that the VM will fetch the strategy from the GitHub/Gitlab and backtest. For your first assignment, you will clone this repo: (insert link)
#### Steps:
- Generate SSH keys in .ssh folder inside your host machine's home directory.
- Don't set any password for the keys. Press "Enter" twice or thrice.
- Copy paste public key into Gitlab and authorize your machine (watch a video on youtube).
- Commands to generate keys: ssh-keygen -t rsa -b 4096
- By default, the keys are created into C:/Users/your-username/.ssh
- Create a test directory inside cygwin's home directory, C:/Users/your-username/home/testing_git
- Test connections using commands like clone, commit, add, push, pull, checkout, branch.

2. Virtual Machine to Gitlab:<br>
This connection is for your VM access your strategies from the repo on GitHub/Gitlab during backtesting.
- Generate SSH key inside .ssh folder inside cygwin64 in C-drive in your host machine.
- Follow the steps to generate SSH Key inside cygwin .ssh:
    - Change to the directory using cd command inside cygwin terminal.
    - Path should be 99% the same, but check.
    - Command: cd C:/cygwin64/home/your-username/.ssh
    - Note: If .ssh directory does not exists, use mkdir .ssh, then cd .ssh, then do the above command.
    - Generate the ssh key with file name 'id_rsa' in the current working directory.
    - Command: ssh-keygen -t rsa -b 4096 -f ./id_rsa
    - Don't set any password for the keys. Press "Enter" twice or thrice.
    - Note: If you use a different name, make sure cygwin knows to use that key whenever it uses SSH. You can do this using a config file(ChatGPT this point to get the cmd).
- The keys are created into C:/cygwin64/home/<your-username>/.ssh
- Copy paste public key into Gitlab and authorize your machine (watch a video on youtube).
- Create a test directory C:/cygwin64/home/your-username/home/test
- Test connections using commands like clone, commit, add, push, pull, checkout, branch.
<br>
- If above steps are done correctly, windows & cygwin should never ask you password username since it will automatically look for the ssh key in the .ssh file near your home directory inside cygwin folder.

## Launch
- Launch cygwin terminal.
- Enter the following commands to clone the required files to run strategy studio:
- Commands start --------
- git clone --recursive git@gitlab.engr.illinois.edu:shared_code/strategystudioubuntu2004.git
- Commands end --------
- After cloning, navigate to that folder in File Explorer (C: -> cygwin -> home -> strategystudioubuntu2004)
1. Copy license.txt into this folder.
2. Copy the 2 strategy studio tar balls(files) into this folder. Download ubuntu files(first 2) from this link: https://davidl.web.illinois.edu/dropbox
Note: You will need Professor to give you access for this link.
3. From the repo we cloned onto our host machine in Step 1 during Setup, copy go.sh and replace the go.sh inside strategystudioubuntu2004. The new go file has some additional features which would be useful during troubleshooting.

## Run Strategy Studio
- Launch cygwin. Navigate to folder. Run ./go.sh.
- DO NOT STOP THE INITIAL RUN BEFORE IT FULLY COMPLETES, IT WILL CAUSE ERRORS. YOU MIGHT HAVE TO UNINSTALL AND REINSTALL CYGWIN AGAIN. MAKE SURE YOU DELETE THE VM FROM VIRTUALBOX IF YOU ARE REINSTALLING CYGWIN AND STRATEGY STUDIO
- ./go.sh contains all scripts which launches VM, runs strategy studio. The last few lines of the go.sh builds and backtests the strategy. This can be done manually too. It is currently set to backtest strategy if launches.
- Commands start --------
- cd strategystudioubuntu2004/
- ./go.sh
- Commands end --------
- Everything should run perfectly if you performed all of the above steps correctly. You will get a bunch of outputs(trade signals) and the program should stop.
- You will be downloading IEX DEEP pcap files to run backtesting. The size of the download will vary depending on the range and the number of tickers you choose. Be patient, if you can see that download has started, take a short break, periodically check the status.
- After the download, an instance will be created using StrategyCommandLine for backtesting our 0_Helloworld_Strategy.
- The results which come in CRA file format are converted into CSV files to view easily.
- You will not get any result because the first time you run ./go.sh, you are cloning Professor's sample strategy from his git repo link which finds trade signals, but doesn't place any trade. 
- This conversion feature is not available in the default provision_scripts. It is added in all the provision_scripts inside each example strategy.

## Troubleshoot - Installation
- gitlab asks for password when logging in:<br>
Problem with SSH connection. Redo all steps.
- Permission denied:<br>
If your local machine is connecting properly to gitlab and able to clone, but VM is not, maybe firewall blocks port access. Either remove restriction, find ways online. Else, factory reset computer, reinstall windows. Factory reset because antivirus creates lots of extra files in root directory.
- pytz not installed:<br>
pytz is downloaded inside Professor's scripts inside the vagrantfile in iexdownloaderparser directory. This happens when you stop the VM during booting for the first time. Just uncomment the lines which destroy the VM in go.sh. It will create a new VM and everything will work fine.

## How do you run 0_Helloworld_Strategy?
- Recall we cloned a git repo onto our local machine in Step 1 during Setup.
- Using File explorer, navigate inside the repo and you will find a folder called provision_scripts_Helloworld inside 0_Helloworld_Strategy. Copy all the files inside that folder (generate_data, build_strategy, run_backtest, delete_instance) into C:/cygwin64/home/your-username/home/strategystudioubuntu2004/provision_scripts. You will be replacing the files that already exists.
- Now you can just run ./go.sh from the cygwin terminal and your new strategy will be tested.
- Go through 0_Helloworld_Strategy for more details.

# Working Examples
1. Helloworld
2. Simple Moving Average <br>
More examples will be added...

## Uninstallation:
1. Commands to delete cygwin from windows in windows cmd
- takeown /r /d y /f cygwin64
- icacls cygwin64 /t /grant everyone:f
- rmdir /s /q cygwin64
