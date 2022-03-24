hello:
	echo "Hello world!"

tradutor:
	gcc -o output/tradutor -I lib/tradutor src/tradutor.c lib/tradutor/base.c

main:
	gcc -o output/main src/main.c output/Assembly/*