build/bin/still_broken: bin/still_broken.cc
	mkdir -p build/bin
	c++ -std=c++14 -lcurl -o build/bin/still_broken bin/still_broken.cc

run: build/bin/still_broken
	./build/bin/still_broken < input/broken_links
