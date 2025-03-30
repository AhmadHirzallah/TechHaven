SRCS := $(wildcard *.cpp *.c)


#BINS := $(SRCS:%.cpp=%)	# FAILED! Only will do the cpp without c
#BINS := $(basename $(SRCS))	# Works Perfectly
 
# Using Pattern Substitution 
BINS := $(SRCS:.cpp=)		# Replaces/Change Every ".cpp" -> "" (Empty)-(NULL)
BINS := $(BINS:.c=)		# Change/Replaces Every ".c" -> "" NOTHING-EMPTY-NULL


OBJS := $(SRCS:%.cpp=%.o)	
OBJS := $(OBJS:%.c=%.o)	
#OBJS := $(addsuffix .o, $(basename $(SRCS)))	#This is addsuffix will work on $(base ...)

#OBJS := $(SRCS:.cpp=.o)		# Using Pattern Substitution :  replacing .cpp with .o 
#OBJS := $(OBJS:.c=.o)			# replacing .c with .o on the resulting list.

all :  $(BINS) all.stamp $(OBJS)

%: %.o
	@echo "Generating Binaries."
	g++ $< -o $@

%.o: %.cpp
	@echo "Generating Object Files if .cpp"
	g++ -o $@ -c $<
%.o: %.c
	@echo "Generating Object Files of .c"
	gcc -o $@ -c $<

all.stamp: $(BINS) $(OBJS)
	@echo "SRCS ARE : $(SRCS)"
	@echo "OBJS ARE : $(OBJS)"
	@echo "BINS ARE : $(BINS)"
	@touch $@

clean:
	@-rm -rf $(BINS) all.stamp $(OBJS)
	@echo "Deleted Successfully"

.PHONY: all clean
