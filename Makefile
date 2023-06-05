lib/lib2drenderer.so: build/image.o build/renderer.o build/sprite.o
	gcc -shared -o lib2drenderer.so build/*.o

build/image.o: image.c
	gcc -fPIC -o build/image.o -c image.c

build/renderer.o: build/image.o renderer.c
	gcc -fPIC -o build/renderer.o -c renderer.c

build/sprite.o: sprite.c
	gcc -fPIC -o build/sprite.o -c sprite.c

clean:
	rm build/* renderer lib/lib2drenderer.so