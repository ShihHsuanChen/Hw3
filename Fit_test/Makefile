######################################
#            C++ Makefile            #
#    2017.10.06 build by Jack Chen   #
#------------------------------------#
#                                    #
# link root-6.10 / Roofit            #
# basic directory configuration      #
# (directory)                        #
#   |__(main).cc                     #
#   |__include/(headers).h           #
#   |__src/(sources).cc              #
#   |__bin/                          #
#   |__lib/                          #
#                                    #
######################################

# Excuable file name
MAIN = Fit_test

# Define compiler and flags
CC     := g++
CFLAGS := -O2 -Wall

# Specify directories
TAR_DIR := ./bin
SRC_DIR := ./src .
LIB_DIR := ./lib/so
INC_DIR := ./include

# Define parameters for g++ compiler
TAR := $(foreach var, $(TAR_DIR), $(var)/$(MAIN)          )
SRC := $(foreach var, $(SRC_DIR), $(wildcard $(var)/*.cc) )
LIB := $(foreach var, $(LIB_DIR), -L $(var)               )
INC := $(foreach var, $(INC_DIR), -I $(var)               )

# Include ROOT
ROOTLIBS  = $(shell root-config --glibs ) 
ROOTFLAGS = $(shell root-config --cflags)

# RooFit Library
ROOFITLIBS = -lRooFit -lRooFitCore -lMinuit

# Extra Library
EXTLIBS =
EXTINCS =

# Define .phony
.PHONY: $(TAR)
.PHONY: clean

# Set all
all: $(TAR)

# Create binary
$(TAR): $(SRC)
	@mkdir -p bin lib
	@echo [INFO] Creating binary files ./bin/$(MAIN)
	$(CC) $(FLAGS) $(SRC) $(LIB) $(EXTLIBS) $(INC) $(EXTINCS) -o $(TAR) $(ROOTLIBS) $(ROOTFLAGS) $(ROOFITLIBS)

clean:
	@echo [Clean]
	@rm -rf ./bin/* ./lib/*
