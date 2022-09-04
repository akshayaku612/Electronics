CC = g++
OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = -std=c++11 $(OPT) $(WARN) $(INC) $(LIB)

# List all your .cc/.cpp files here (source files, excluding header files)
SIM_SRC = src/sim_bp.cc src/config/BranchPredictor.cpp ./src/util/csv_write.cpp

# List corresponding compiled object files here (.o files)
SIM_OBJ = sim_bp.o BranchPredictor.o csv_write.cpp
 
#################################

# default rule

#all: sim
#	@echo "my work is done here..."

all:
	g++ -std=c++11 -O3 -Wall -c ./src/sim_bp.cc ./src/config/BranchPredictor.cpp ./src/util/csv_write.cpp	
	g++ -o sim -O3 -Wall *.o -lm


# rule for making sim

sim: $(SIM_OBJ)
	$(CC) -o sim $(CFLAGS) $(SIM_OBJ) -lm
	@echo "-----------DONE WITH sim-----------"


# generic rule for converting any .cpp file to any .o file
 
.cc.o:
	$(info  hello)
	$(CC) $(CFLAGS)  -c $*.cc

.cpp.o:
	$(info  hello)
	$(CC) $(CFLAGS)  -c $*.cpp


# type "make clean" to remove all .o files plus the sim binary

clean:
	rm -f *.o sim


# type "make clobber" to remove all .o files (leaves sim binary)

clobber:
	rm -f *.o


