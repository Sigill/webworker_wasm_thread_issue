all: test.js

clean:
	rm -rf test.wasm test.js test.worker.js

.PHONY : all clean

test.js: test.cpp
	em++ $< --bind -lpthread -sUSE_PTHREADS=1 -sPTHREAD_POOL_SIZE=3 -o $@
