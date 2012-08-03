#Works on Arch - not so sure about anything else
# pretty bad form for a makefile, but works well for this

$(MAKECMDGOALS):
	g++ -O3 -o bin/$@ $@.cpp `pkg-config --libs --cflags opencv`
