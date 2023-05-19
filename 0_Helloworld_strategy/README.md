## What is in this directory?
1. makefile:
- This contains instructions for automating compilation of the source code and generating the shared object library.
- It defines various variables such as compiler and linker flags, library paths, and object files.
- It also includes targets for building the shared object library, cleaning up object files and the library file, and copying the library to a specific directory.
2. .cpp file:
- This contains the implementation of the Helloworld_Strategy class.
- This is the main file that defines the logic of the strategy.
- It includes the necessary headers and defines the functions and methods of the class.
3. .h file: 
- This contains the declaration of the Helloworld_Strategy class.
- This file is included in the .cpp file to provide the necessary interface to the class.
- It contains the class definition, including its public and private members, member functions, and variables.
4. provision_scripts directory:
- This folder contains provision scripts which should be manually copied inside the below path:
- C:\cygwin64\home\user-name\strategystudioubuntu2004\provision_scripts
5. .py file:
- This file helps in deleting the instance that exists from the sqlite strategy.db
- This would help the user to not change the InstanceName everytime they run a backtest.
- This file is placed along with the strategy because it is called inside the provision script, build_strategy.sh.
- The file is currenty not working so it has been commented
- Will be updated soon

## How to view results of your backtest?
- You need to know how and where the csv files are being created
- To extract the csv files, you need to go to File manager inside your VM, navigate to vagrant > bt > backtesting-results
- Then we can directly extract it to a directory inside cygwin. We can't extract to our host machine because the results are inside a VM
- After extracting, we can view the csv files however we want.

## How to run the same strategy multiple times?
- This would not require below steps if the .py file worked. I'm working on that...
- Currently, we have to keep changing the InstanceName in 3 files, build_strategy.sh & run_backtest.sh & makefile
- Use CTRL+F and replace all to new InstanceName
- You can keep changing the numbers at the end like this: InstanceName1 to InstanceName2
- I tried using different terms like the strategy file name itself but I wasn't able to get it working.
- For now just keep incrementing the numbers.
- Occassionally, you could uncomment the lines which destroy the VM to wipe out all instances and you could restart with 1.
- Keep in mind booting a new VM takes some time

## How to run your own strategy?
- File name should be yourstrategyname_Strategy
- Inside makefile, .cpp and .h, use CTRL+F and replace all to yourstrategyname_Strategy.
- Example: Helloworld_Strategy to SMA_Strategy
- Double check if you changed it in all 3 files

## What you have to submit on canvas
- There will be 3 files which you will extract as results. You will need to upload a single screenshot which contains the following:
    - Final CUMULATIVE P&L displayed
    - cygwin terminal showing "export successful"
    - your cmd prompt showing that you are inside when you display CWD
- VIEW THE SAMPLE SCREENSHOT (will be uploaded)