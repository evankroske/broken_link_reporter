build/still_broken: src/still_broken.cc
	mkdir -p build
	c++ -std=c++14 -lcurl -o build/still_broken src/still_broken.cc

build/broken_link_finder: src/broken_link_finder.cc
	mkdir -p build
	c++ -std=c++14 -lcurl -o build/broken_link_finder src/broken_link_finder.cc
