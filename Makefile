tradutor:
	gcc -o output/tradutor -I lib/tradutor src/tradutor.c lib/tradutor/base.c

compile_bpl: 
	cat bpl/*.bpl > temp.bpl
	./output/tradutor < temp.bpl > temp.s
	gcc -c -o output/main.o temp.s
	
assembly: compile_bpl
	rm temp.bpl
	rm temp.s

main: assembly
	gcc -o output/main src/main.c output/main.o
	rm output/main.o