sudoku: build/generator.o build/utils.o build/board.o build/pieces.o
	gcc -o generator build/generator.o build/utils.o build/board.o build/pieces.o -Wall -Wextra -Wpedantic -std=c23

build/generator.o: generator.c
	gcc -o build/generator.o -c generator.c -Wall -Wextra -Wpedantic -std=c23

build/utils.o: utils.c
	gcc -o build/utils.o -c utils.c -Wall -Wextra -Wpedantic -std=c23

build/board.o: board.c
	gcc -o build/board.o -c board.c -Wall -Wextra -Wpedantic -std=c23

build/pieces.o: pieces.c
	gcc -o build/pieces.o -c pieces.c -Wall -Wextra -Wpedantic -std=c23
