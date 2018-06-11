# Makefile

# make test = compilation + affichage des tests
# make afficher =  affichage des tests
# make main = compilation des jeux
# make clean = suppression executable dossier
# make valgrind = utilisation valgrind
main:
	@echo "\n COMPILATION BASE"
	@make -C base base

	@echo "\n COMPILATION VERSION1"
	@make -C version1 version1

	@echo "\n COMPILATION VERSION2"
	@make -C version2 version2

	@echo "\n COMPILATION VERSION3"
	@make -C version3 version3

	@echo "\n COMPILATION VERSION4"
	@make -C version4 version4

	@echo "\n COMPILATION VERSION5"
	@make -C version5 version5
	
	@echo "\n COMPILATION VERSION6"
	@make -C version6 version6


test:
	@echo "\n COMPILATION TEST BASE"
	@make -C base test-1

	@echo "\n COMPILATION TEST VERSION1"
	@make -C version1 test-1

	@echo "\n COMPILATION TEST VERSION2"
	@make -C version2 test-1

	@echo "\n COMPILATION TEST VERSION3"
	@make -C version3 test-1

	@echo "\n COMPILATION TEST VERSION4"
	@make -C version4 test-1

	@echo "\n COMPILATION TEST VERSION5"
	@make -C version5 test-1
	
	@echo "\n COMPILATION TEST VERSION6"
	@make -C version6 test-1


afficher:
	./base/test-1
	./version1/test-1
	./version2/test-1
	./version3/test-1
	./version4/test-1
	./version5/test-1
	./version6/test-1



valgrind:
	valgrind ./base/test-1
	valgrind ./version1/test-1
	valgrind ./version2/test-1
	valgrind ./version3/test-1
	valgrind ./version4/test-1

clean:
	@echo "\nCLEAN BASE"
	@make -C base clean

	@echo "\nCLEAN VERSION1"
	@make -C version1 clean

	@echo "\nCLEAN VERSION2"
	@make -C version2 clean

	@echo "\nCLEAN VERSION3"
	@make -C version3 clean

	@echo "\nCLEAN VERSION4"
	@make -C version4 clean

	@echo "\nCLEAN VERSION5"
	@make -C version5 clean
	
	@echo "\nCLEAN VERSION6"
	@make -C version6 clean
