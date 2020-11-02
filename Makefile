LIBS=-lm
nn: nnetwork.cpp
	gcc -o $@ nnetwork.cpp -I. $(LIBS)
