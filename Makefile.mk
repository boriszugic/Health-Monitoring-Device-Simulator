CC = gcc
CFLAGS = -Wall -lm
DEPS = simulator_presentation_functions.h simulator_prep_functions.h simulator_helper_functions.h
OBJ = test.c simulator_presentation_functions.c simulator_prep_functions.c simulator_helper_functions.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
