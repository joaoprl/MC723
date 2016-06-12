all:
	make -f Makefile.archc clean
	make -f Makefile.archc -j4
run:
	make all
	mips-newlib-elf-gcc -specs=archc $(file).c -o $(file).mips
	./mips.x --load=$(file).mips
