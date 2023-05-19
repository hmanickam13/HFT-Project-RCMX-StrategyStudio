## What is in this directory?
- There is a provision_scripts folder which contain the provision scripts which generate data, build strategies, and run backtests for this specific ML_Strategy
- provision_scripts are key for everything to work, so ensure everything is correct
- There are three files: a makefile, a .cpp file, and a .h file.
- Together, the .cpp, .h, and Makefile define how the C++ code for this ML strategy should be built and executed.

## Files
1. makefile:
- This contains instructions for automating compilation of the source code and generating the shared object library.
- It defines various variables such as compiler and linker flags, library paths, and object files.
- It also includes targets for building the shared object library, cleaning up object files and the library file, and copying the library to a specific directory.
2. .cpp file:
- This contains the implementation of the ML_Strategy class.
- This is the main file that defines the logic of the strategy.
- It includes the necessary headers and defines the functions and methods of the class.
3. .h file: 
- This contains the declaration of the ML_Strategy class.
- This file is included in the .cpp file to provide the necessary interface to the class.
- It contains the class definition, including its public and private members, member functions, and variables.

## How does this strategy work?
- TBD
- TBD

## How to test this strategy?
- Do not start without fully understanding the files in the 0_provision_scripts and 1_test_strategy directory.
- Ideally we would want the correct set of provision_scripts to be automatically used when backtesting a specific strategy
- For now, manually copy paste these scripts inside the provision_scripts directory inside cygwin > ... > ... > ... > provision_scripts
- Once you make the right changes inside provision_scripts, you can just simply run this strategy just like how you ran 1_test_strategy

## In Progress
- Automate selection of provision_scripts
- Access, select, and prepare training data to build ML model.
- Basic ML strategy using indicators
