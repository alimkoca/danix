.PHONY: all clean run kernel

all:
	@./Make.py

clean:
	@./Make.py clean

run:
	@./Make.py run

kernel:
	@./Make.py kernel
