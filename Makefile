hello:
	echo "Hello world!"

tradutor:
	gcc -o output/tradutor -I lib/tradutor src/tradutor.c lib/tradutor/base.c

assembly:


bpl:
	cat bpl/*.bpl > temp.bpl
	./output/tradutor < temp.bpl > temp.s
	gcc -o output/main temp.s

	rm temp.bpl
	rm temp.s

main:
	gcc -o output/main src/main.c output/Assembly/*