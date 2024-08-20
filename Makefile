cbm2bmp: src/main.o src/cbm_info.o src/bmp_info.o
	gcc -o cbm2bmp src/main.o src/cbm_info.o src/bmp_info.o

src/main.o: src/main.c src/common.h
	gcc -c src/main.c -o src/main.o

src/cbm_info.o: src/cbm_info.c src/common.h
	gcc -c src/cbm_info.c -o src/cbm_info.o

src/bmp_info.o: src/bmp_info.c src/common.h
	gcc -c src/bmp_info.c -o src/bmp_info.o

clean:
	rm -f src/*.o cbm2bmp