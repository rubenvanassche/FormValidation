cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
# Above line indicates to Cmake that minimum version 2.8 is required.
# As you may have noted all lines beginning with hash symbol are treated as comments by Cmake.
SET(sampleName FormValidation)
# In the above line we declared a variable sampleName and assigned it a value MyApp. We will make use of the same later.project(PrjMyApp)
# here we define the project or solution (for visual studio) name

# The following line is very important.
# It specifies the executable name. Here the executable is the first parameter i.e. MyApp and a file MyApp.exe will be created on
# compilation in windows platform.
# Followed by the executable name come all your source and header files.
# All cpp fles will be clubbed into source folder and all .h files will be added to header files folder of the project.
add_executable (FormValidation common.h Component.h Component.cpp DFA.cpp DFA.h eNFA.cpp eNFA.h Field.cpp Field.h Form.cpp Form.h FormValidation.cpp RegexToNFA.cpp RegexToNFA.h SubsetConstruction.cpp SubsetConstruction.h Test.cpp Test.h FormTest.cpp FormTest.h DFATest.cpp DFATest.h)
