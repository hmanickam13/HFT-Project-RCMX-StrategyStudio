## What is in this directory?
- This directory contains the provision scripts used to automate the process of setting up and configuring the environment needed for backtesting a strategy.
- These provision scripts are used to generate data, build strategies, and run backtests. 
- They are also used to install any necessary libraries and dependencies required for these tasks.
- Read through all the files to fully understand what is going on here.

## Files
1. generate_data.sh:
- This script generates a synthetic dataset of stock prices using a Python script called generate_synthetic_data.py.
- The generated data includes price and volume information for a given set of tickers and a specified date range.
2. build_strategy.sh:
- This script compiles a C++ strategy code and creates a shared library file (.so) using a Makefile.
- The code is compiled using either the icc or g++ compiler based on the value of the INTEL flag.
- The generated library file is then copied to the strategies_dlls directory.
3. run_backtest.sh:
- This script runs a backtest using the generated synthetic data and the compiled C++ strategy.
- It uses the run_backtest command provided by the Strategy Studio application to run the backtest.
- The output(CRA file) of the backtest is saved to a directory named backtesting-results in the current directory.
- The CRA file is then exported using the StrategyCommandLine utility into a CSV format and saved in specified directory.