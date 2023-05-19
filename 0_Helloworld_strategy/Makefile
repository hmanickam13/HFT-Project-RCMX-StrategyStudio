# This is a makefile that compiles a C++ program and performs some automated tasks.
# Read the comments. They explain the code
# When you create your own strategy, you need to create a makefile. You can copy this makefile, but you have to make a few changes.
# Total changes to make = 4
# 1. Change file name in 3 places
# 2. Instance Name in 1 place.

# Conditional settings based on passed in variables
# Set the compiler variable CC to icc if the INTEL flag is defined, otherwise it sets it to g++.
# What is INTEL flag?
ifdef INTEL
    CC=icc
else
    CC=g++
endif

# If the DEBUG flag is defined, it sets CFLAGS to -c -g -fPIC -fpermissive -std=c++11.
# Otherwise, it sets it to -c -fPIC -fpermissive -O3 -std=c++11.
# -c: Specifies that the compiler should compile the source code and generate an object file, but not perform the linking step. This is done to compile each source file independently, which can speed up the compilation process when changes are made to only a few source files.
# -g: Generates debug information for the object file. This information is used by debugging tools to associate source code with machine code.
# -fPIC: Generates position-independent code, which can be used to create shared libraries that can be loaded at any memory address. This is useful for creating portable code that can be run on different systems with different memory layouts.
# -fpermissive: Tells the compiler to be more lenient in enforcing some of the language rules. This can be useful when compiling legacy code that may not conform to the latest standards.
# -std=c++11: Specifies the version of the C++ language standard to use. In this case, it is set to C++11, which adds several new features to the language. Using this flag ensures that the compiler will check the code against the C++11 standard and issue warnings or errors if any non-conformances are found.
# You should understand the purpose behind every flag
ifdef DEBUG
    CFLAGS=-c -g -fPIC -fpermissive -std=c++11
else
    CFLAGS=-c -fPIC -fpermissive -O3 -std=c++11
endif

# Set the paths to the library and include files.
# Directory is found 4 levels up. Why?
LIBPATH=../../../../libs/x64
INCLUDEPATH=../../../../includes

# Set the include flags, which tells the compiler where to find the header files
INCLUDES=-I/usr/include -I$(INCLUDEPATH)

# The linker combines object files and libraries to create the final executable.
# Libraries contain precompiled code with useful functions and utilities.
# The LDFLAGS variable is used to specify which libraries to link with the object files.
# In this case, we are linking with multiple libraries located in the LIBPATH directory.
LDFLAGS=$(LIBPATH)/libstrategystudio_analytics.a $(LIBPATH)/libstrategystudio.a $(LIBPATH)/libstrategystudio_transport.a $(LIBPATH)/libstrategystudio_marketmodels.a $(LIBPATH)/libstrategystudio_utilities.a $(LIBPATH)/libstrategystudio_flashprotocol.a

# Define the names of the library, source, and header files.
LIBRARY=Helloworld_Strategy.so
SOURCES=Helloworld_Strategy.cpp
HEADERS=Helloworld_Strategy.h

# Object files contain compiled code of source files.
# Object files are linked to create the final executable file.
# Creating object files reduces compilation time for recompiling modified code.
# The OBJECTS variable is set to names of source files with .cpp extension replaced with .o.
# This tells the compiler to compile source files into object files with same names.
OBJECTS=$(SOURCES:.cpp=.o)

# We use targets in this makefile.
# targets are specific sections of the Makefile that define a set of commands to be executed when that target is invoked.
# Targets are typically used to build or clean specific parts of a project, or to execute specific commands.
# In this Makefile, we have targets such as all, clean, copy_strategy, launch_backtest, run_backtest, and output_results, each of which defines a specific set of commands to be executed. 
# Targets are invoked by running the make command followed by the target name, such as make clean to execute the commands defined in the clean target

# The first line specifies that the target all should be built, and it depends on $(HEADERS) and $(LIBRARY).
# The second line specifies that $(HEADERS) should be built. However, in this case, $(HEADERS) is just a list of header files and not actual build targets, so this line is only included for completeness and doesn't actually do anything.
# The third line specifies that $(LIBRARY) should be built. This is the actual target that generates the shared object library file from the object files in $(OBJECTS) using the linker.
# The $() syntax is used to reference a variable value in the makefile.
# The all target is typically the default target and is built when running make without any target specified.
all: $(HEADERS) $(LIBRARY)

# $(LIBRARY): A variable that holds the name of the library we want to build.
# $(OBJECTS): A variable that holds the names of the object files that the library should be built from.
# $(CC): A variable that holds the name of the compiler that should be used to build the library.
# -shared: An option passed to the linker that tells it to create a shared object library.
# -Wl,-soname,$(LIBRARY).1: An option passed to the linker that sets the soname of the library to $(LIBRARY).1.
# -o $(LIBRARY): An option passed to the linker that specifies the name of the output file to create.
# $(LDFLAGS): A variable that holds the linker flags that specify which libraries to link with the object files.
# The $(LIBRARY) target specifies the recipe for building the library using the object files. 
# The linker is called with the $(CC) variable to create a shared object library named $(LIBRARY).
# The soname of the library is set to $(LIBRARY).1 using the -Wl,-soname option. Finally, the linker is passed the $(LDFLAGS) variable, which specifies which libraries to link with the object files.
$(LIBRARY) : $(OBJECTS)
	$(CC) -shared -Wl,-soname,$(LIBRARY).1 -o $(LIBRARY) $(OBJECTS) $(LDFLAGS)
	
# This rule specifies how to build object files (.o files) from source files (.cpp files) using the headers and flags specified in the $(HEADERS) and $(CFLAGS) variables.
# The line begins with ".cpp.o:", which is a pattern rule that matches any file that ends in .cpp and produces a corresponding file that ends in .o.
# The dependency, $(HEADERS), specifies that any changes to the headers will trigger a rebuild of the object file.
# The rule contains a command that specifies how to build the object file from the source file. It uses the $(CC) variable, which contains the name of the C++ compiler to use, along with $(CFLAGS), $(INCLUDES), and $<, which is an automatic variable that contains the name of the first prerequisite, in this case the source file.
# The command compiles the source file and generates an object file using the specified compiler, compiler flags, and include paths, and saves the output to a file with the same name as the source file, but with the .o extension.
.cpp.o: $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

# The clean target is used to remove all the object files and the shared library file generated during the build process.
# The command rm -rf *.o $(LIBRARY) is executed when the clean target is invoked. The rm command is used to remove files and directories.
# The -r flag is used to remove directories recursively, and the -f flag is used to force removal without prompting for confirmation.
# The *.o pattern matches all files with the .o extension, which are the object files generated during the build process.
# The $(LIBRARY) variable expands to the name of the shared library file that was built, and it is also removed by the rm command.
clean:
	rm -rf *.o $(LIBRARY)

# This Makefile target copies the shared object library generated from the source code to a specified location on the file system.
# The copy_strategy target depends on the all target, which ensures that the library file $(LIBRARY) is built before being copied to the destination directory /home/vagrant/ss/bt/strategies_dlls/.
# The cp command is used to copy the $(LIBRARY) file to the specified directory /home/vagrant/ss/bt/strategies_dlls/.
# This target is useful for deploying the shared object library to a specific location on the file system, making it easier to access by other programs.
copy_strategy: all
	cp $(LIBRARY) /home/vagrant/ss/bt/strategies_dlls/.

# XXXXXXXXXXXXXXXXXXXXXXXX
# Change your instance name
# The launch_backtest target in the Makefile is a command that can be executed to start a backtest of the trading strategy.
# It changes directory to /home/vagrant/ss/bt/utilities and runs the StrategyCommandLine program with the arguments cmd start_backtest 2021-11-05 2021-11-05 InstanceName1 1.
# The cd command changes the current directory to /home/vagrant/ss/bt/utilities and the ./StrategyCommandLine command runs the StrategyCommandLine program located in the current directory.
# The program takes four arguments:
# - cmd: specifies the command to be executed, which in this case is start_backtest
# - start_backtest: specifies that we want to start a backtest
# - 2021-11-05: specifies the start date for the backtest
# - InstanceName1 1: specifies the name of the backtest instance and the number of threads to be used for the backtest.
# It is important to note that the start and end dates should be matching and the instance name should be changed to the appropriate name for the strategy being tested.
launch_backtest: 
	cd /home/vagrant/ss/bt/utilities ; ./StrategyCommandLine cmd start_backtest 2021-11-05 2021-11-05 InstanceName1 1

# This is a make target called run_backtest. 
# It has a dependency on the all target, meaning that the all target will be built before the run_backtest target is executed.
# When the run_backtest target is executed, it changes the current working directory to ~/Downloads/ss_backtesting, then it echoes the current working directory, and finally, it runs the run_backtest.sh shell script.
# The run_backtest.sh shell script is expected to be located in the ~/Downloads/ss_backtesting directory, and it presumably contains commands to run a backtest on the strategy that was compiled and built by the all target.
run_backtest: all
	cd ~/Downloads/ss_backtesting ; echo $PWD ; ./run_backtest.sh

# The output_results target defines two commands to be executed when the target is invoked.
# The first command sets the environment variable CRA_RESULT to the last modified file in the ~/Downloads/ss_backtesting/backtesting-results directory whose filename starts with "BACK" and ends with "cra".
# This is done using the find command to search for matching files, and tail -n 1 to select the last result.
# The result is then echoed to the console using the echo command.
# The second command sets the environment variable TEST_VAR to "hi", and then echoes its value to the console using the echo command.
output_results:
	export CRA_RESULT=`cd ~/Downloads/ss_backtesting ; find ./backtesting-results -name 'BACK*cra' | tail -n 1` ; \
	echo $$CRA_RESULT
	export TEST_VAR="hi" ; \
	echo $$TEST_VAR

