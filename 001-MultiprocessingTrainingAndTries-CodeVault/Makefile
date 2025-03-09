# FILE ?= Enter File Name





# FILE ?= 1_fork.c
# FILE ?= 2_waiting_processes_finishing.c
# FILE ?= 3_Process_IDs.c
# FILE ?= 5_Communicating_between_processes_using_pipes.c
# FILE ?= 6_Practical_use_case_for_fork_and_pipe.c
# FILE ?= 7_Introduction_to_FIFOs_aka_named_pipes.c
# FILE ?= 9_Two_way_communication_between_processes_using_pipes.c
# FILE ?= 10_execute_another_program.c
# FILE ?= 11_Executing_commands.c 
# FILE ?= 12_GettingExitStatusCode.c 
# FILE ?= 13_RedirectingStandardOutput.c
# FILE ?= 14_ExecutingProgramsVSExecutingScripts.c
# FILE ?= 15_introduction_to_signals.c 
# FILE ?= 16_StoppingAndContinuingTheExecutionOfAProcessUsingSIGCONT_SIGSTOP.c
# FILE ?= 17_BackgroundAndForegroundProcesses.c
# FILE ?= 18_HandlingSignals.c 
# FILE ?= 19_CommunicatingBetweenProcessesUsingSignals.c
# FILE ?=	20_SendAnArrayThroughPipe.c 
# FILE ?=	21_SendStringThroughPipe.c
# FILE ?=	22_SimulatingThePipeOperator.c
# FILE ?=	23_WorkingWithMultiplePipes.c
# FILE ?=	24_WhatForkActuallyReturn.c
# FILE ?=	25_WhatIsWaitpid.c
FILE ?=	26_CallingForkMultipleTimesWithPracticalExample.c





CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = $(FILE)
OBJ_DIR = objs
OBJ = $(OBJ_DIR)/$(FILE:.c=.o)
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

$(OBJ): $(SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: all
	./$(TARGET)

debug: CFLAGS += -DDEBUG
debug: all

clean:
	-rm -f $(OBJ)

fclean: clean
	-rm -rf $(TARGET) $(OBJ_DIR)

re: fclean all

.PHONY: all run debug clean fclean re
