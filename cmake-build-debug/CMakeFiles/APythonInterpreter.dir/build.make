# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cebastiansantiago/CLionProjects/CS450

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/APythonInterpreter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/APythonInterpreter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/APythonInterpreter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/APythonInterpreter.dir/flags.make

CMakeFiles/APythonInterpreter.dir/main.cpp.o: CMakeFiles/APythonInterpreter.dir/flags.make
CMakeFiles/APythonInterpreter.dir/main.cpp.o: ../main.cpp
CMakeFiles/APythonInterpreter.dir/main.cpp.o: CMakeFiles/APythonInterpreter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/APythonInterpreter.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/APythonInterpreter.dir/main.cpp.o -MF CMakeFiles/APythonInterpreter.dir/main.cpp.o.d -o CMakeFiles/APythonInterpreter.dir/main.cpp.o -c /Users/cebastiansantiago/CLionProjects/CS450/main.cpp

CMakeFiles/APythonInterpreter.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/APythonInterpreter.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cebastiansantiago/CLionProjects/CS450/main.cpp > CMakeFiles/APythonInterpreter.dir/main.cpp.i

CMakeFiles/APythonInterpreter.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/APythonInterpreter.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cebastiansantiago/CLionProjects/CS450/main.cpp -o CMakeFiles/APythonInterpreter.dir/main.cpp.s

CMakeFiles/APythonInterpreter.dir/Token.cpp.o: CMakeFiles/APythonInterpreter.dir/flags.make
CMakeFiles/APythonInterpreter.dir/Token.cpp.o: ../Token.cpp
CMakeFiles/APythonInterpreter.dir/Token.cpp.o: CMakeFiles/APythonInterpreter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/APythonInterpreter.dir/Token.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/APythonInterpreter.dir/Token.cpp.o -MF CMakeFiles/APythonInterpreter.dir/Token.cpp.o.d -o CMakeFiles/APythonInterpreter.dir/Token.cpp.o -c /Users/cebastiansantiago/CLionProjects/CS450/Token.cpp

CMakeFiles/APythonInterpreter.dir/Token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/APythonInterpreter.dir/Token.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cebastiansantiago/CLionProjects/CS450/Token.cpp > CMakeFiles/APythonInterpreter.dir/Token.cpp.i

CMakeFiles/APythonInterpreter.dir/Token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/APythonInterpreter.dir/Token.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cebastiansantiago/CLionProjects/CS450/Token.cpp -o CMakeFiles/APythonInterpreter.dir/Token.cpp.s

CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.o: CMakeFiles/APythonInterpreter.dir/flags.make
CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.o: ../Tokenizer.cpp
CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.o: CMakeFiles/APythonInterpreter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.o -MF CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.o.d -o CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.o -c /Users/cebastiansantiago/CLionProjects/CS450/Tokenizer.cpp

CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cebastiansantiago/CLionProjects/CS450/Tokenizer.cpp > CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.i

CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cebastiansantiago/CLionProjects/CS450/Tokenizer.cpp -o CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.s

CMakeFiles/APythonInterpreter.dir/Parser.cpp.o: CMakeFiles/APythonInterpreter.dir/flags.make
CMakeFiles/APythonInterpreter.dir/Parser.cpp.o: ../Parser.cpp
CMakeFiles/APythonInterpreter.dir/Parser.cpp.o: CMakeFiles/APythonInterpreter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/APythonInterpreter.dir/Parser.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/APythonInterpreter.dir/Parser.cpp.o -MF CMakeFiles/APythonInterpreter.dir/Parser.cpp.o.d -o CMakeFiles/APythonInterpreter.dir/Parser.cpp.o -c /Users/cebastiansantiago/CLionProjects/CS450/Parser.cpp

CMakeFiles/APythonInterpreter.dir/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/APythonInterpreter.dir/Parser.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cebastiansantiago/CLionProjects/CS450/Parser.cpp > CMakeFiles/APythonInterpreter.dir/Parser.cpp.i

CMakeFiles/APythonInterpreter.dir/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/APythonInterpreter.dir/Parser.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cebastiansantiago/CLionProjects/CS450/Parser.cpp -o CMakeFiles/APythonInterpreter.dir/Parser.cpp.s

CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.o: CMakeFiles/APythonInterpreter.dir/flags.make
CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.o: ../ExprNode.cpp
CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.o: CMakeFiles/APythonInterpreter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.o -MF CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.o.d -o CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.o -c /Users/cebastiansantiago/CLionProjects/CS450/ExprNode.cpp

CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cebastiansantiago/CLionProjects/CS450/ExprNode.cpp > CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.i

CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cebastiansantiago/CLionProjects/CS450/ExprNode.cpp -o CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.s

CMakeFiles/APythonInterpreter.dir/SymTab.cpp.o: CMakeFiles/APythonInterpreter.dir/flags.make
CMakeFiles/APythonInterpreter.dir/SymTab.cpp.o: ../SymTab.cpp
CMakeFiles/APythonInterpreter.dir/SymTab.cpp.o: CMakeFiles/APythonInterpreter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/APythonInterpreter.dir/SymTab.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/APythonInterpreter.dir/SymTab.cpp.o -MF CMakeFiles/APythonInterpreter.dir/SymTab.cpp.o.d -o CMakeFiles/APythonInterpreter.dir/SymTab.cpp.o -c /Users/cebastiansantiago/CLionProjects/CS450/SymTab.cpp

CMakeFiles/APythonInterpreter.dir/SymTab.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/APythonInterpreter.dir/SymTab.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cebastiansantiago/CLionProjects/CS450/SymTab.cpp > CMakeFiles/APythonInterpreter.dir/SymTab.cpp.i

CMakeFiles/APythonInterpreter.dir/SymTab.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/APythonInterpreter.dir/SymTab.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cebastiansantiago/CLionProjects/CS450/SymTab.cpp -o CMakeFiles/APythonInterpreter.dir/SymTab.cpp.s

CMakeFiles/APythonInterpreter.dir/Statements.cpp.o: CMakeFiles/APythonInterpreter.dir/flags.make
CMakeFiles/APythonInterpreter.dir/Statements.cpp.o: ../Statements.cpp
CMakeFiles/APythonInterpreter.dir/Statements.cpp.o: CMakeFiles/APythonInterpreter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/APythonInterpreter.dir/Statements.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/APythonInterpreter.dir/Statements.cpp.o -MF CMakeFiles/APythonInterpreter.dir/Statements.cpp.o.d -o CMakeFiles/APythonInterpreter.dir/Statements.cpp.o -c /Users/cebastiansantiago/CLionProjects/CS450/Statements.cpp

CMakeFiles/APythonInterpreter.dir/Statements.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/APythonInterpreter.dir/Statements.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cebastiansantiago/CLionProjects/CS450/Statements.cpp > CMakeFiles/APythonInterpreter.dir/Statements.cpp.i

CMakeFiles/APythonInterpreter.dir/Statements.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/APythonInterpreter.dir/Statements.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cebastiansantiago/CLionProjects/CS450/Statements.cpp -o CMakeFiles/APythonInterpreter.dir/Statements.cpp.s

# Object files for target APythonInterpreter
APythonInterpreter_OBJECTS = \
"CMakeFiles/APythonInterpreter.dir/main.cpp.o" \
"CMakeFiles/APythonInterpreter.dir/Token.cpp.o" \
"CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.o" \
"CMakeFiles/APythonInterpreter.dir/Parser.cpp.o" \
"CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.o" \
"CMakeFiles/APythonInterpreter.dir/SymTab.cpp.o" \
"CMakeFiles/APythonInterpreter.dir/Statements.cpp.o"

# External object files for target APythonInterpreter
APythonInterpreter_EXTERNAL_OBJECTS =

APythonInterpreter: CMakeFiles/APythonInterpreter.dir/main.cpp.o
APythonInterpreter: CMakeFiles/APythonInterpreter.dir/Token.cpp.o
APythonInterpreter: CMakeFiles/APythonInterpreter.dir/Tokenizer.cpp.o
APythonInterpreter: CMakeFiles/APythonInterpreter.dir/Parser.cpp.o
APythonInterpreter: CMakeFiles/APythonInterpreter.dir/ExprNode.cpp.o
APythonInterpreter: CMakeFiles/APythonInterpreter.dir/SymTab.cpp.o
APythonInterpreter: CMakeFiles/APythonInterpreter.dir/Statements.cpp.o
APythonInterpreter: CMakeFiles/APythonInterpreter.dir/build.make
APythonInterpreter: CMakeFiles/APythonInterpreter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable APythonInterpreter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/APythonInterpreter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/APythonInterpreter.dir/build: APythonInterpreter
.PHONY : CMakeFiles/APythonInterpreter.dir/build

CMakeFiles/APythonInterpreter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/APythonInterpreter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/APythonInterpreter.dir/clean

CMakeFiles/APythonInterpreter.dir/depend:
	cd /Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cebastiansantiago/CLionProjects/CS450 /Users/cebastiansantiago/CLionProjects/CS450 /Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug /Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug /Users/cebastiansantiago/CLionProjects/CS450/cmake-build-debug/CMakeFiles/APythonInterpreter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/APythonInterpreter.dir/depend

