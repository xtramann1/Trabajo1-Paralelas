OBJS = main.o 
BINARY = main
LDFLAGS = -lm
Flags = g++ -Wall -g3
ArchivosCSV = maximos.csv artistico.csv tecnicos.csv humanismo.csv
main: crear $(OBJS)
	$(Flags) -o $(BINARY) $(OBJS) $(LDFLAGS)

main.o: main.cpp funciones.cpp
	$(Flags) -c main.cpp

crear:
	mkdir -p al
	touch al/maximos.csv 
	touch al/artistico.csv
	touch al/humanismo.csv
	touch al/tecnicos.csv

.PHONY: clean 
clean: 
	rm -fr $(BINARY) $(OBJS) $(ArchivosCSV) al

