projet.out: projet.cpp
	g++ projet.cpp -o projet.out

projet: projet.out
	./projet.out