ParadisEO_example
=================

First example using ParadisEO - A software framework for metaheuristics


This package contains the source code for ZDT problems.

# Step 1 - Build process
------------------------
ParadisEO is assumed to be compiled. In addition, we supposed you are using Unix makefiles or MinGW makefiles. 

To download ParadisEO or having further information about the installation and configuration, please visit http://paradiseo.gforge.inria.fr/.

Create a build directory :
> mkdir build
Go to the build/ directory and lunch cmake:
(Unix)       > cmake ..
(Windows)    > cmake .. -G "MinGW Makefiles"

# Step 2 - Compilation
----------------------
In the Example/build/ directory:
> make

# Step 3 - Execution
---------------------
A toy example is given to test the components. You can run these tests as following.
To define problem-related components for your own problem, please refer to the tutorials available on the website : http://paradiseo.gforge.inria.fr/.
In the Example/build/ directory:
> ctest

In the directory "application", there are three ".cpp" which instantiate NSGAII on ZDT problems.

(Unix) After compilation you can run the script "Example/run.sh" and see results in "NSGAII.out". Parameters can be modified in the script.

(Windows) Add argument "NSGAII.param" and execute the corresponding algorithms.

# Documentation
---------------
The API-documentation is available in doc/html/index.html 
