SOURCE_DIR=src
SOURCE_CLIENT=clients
TESTS_DIR=tst

BIN=server client_basique client_jalon1
TEST= test_deck test_board test_card

CC=gcc
CPPFLAGS=-I ${SOURCE_DIR} -I ${SOURCE_CLIENT} -I ${TESTS_DIR}
CFLAGS=-Wall -Wextra -std=c99 -g -O0

build: ${BIN}

install: ${BIN}
	mv *.so server ./install

run:	install
	./install/server ./install/client_basique.c ./PROJET_des_autres_groupes/clients/client4410.so

test: ${TEST}
	@for e in ${TEST}; do \
	echo $${e}; ./$${e}; \
	done

clean:
	rm -rf *.o *.so ${BIN} ${TEST} ./install/*


###################################################################
#server
server:	${SOURCE_DIR}/server.c ${SOURCE_DIR}/player.c client_basique client_jalon1
	${CC} ${CPPFLAGS} ${CFLAGS} -o server ${SOURCE_DIR}/server.c ${SOURCE_DIR}/deck.c ${SOURCE_DIR}/card.c ${SOURCE_DIR}/board.c ${SOURCE_DIR}/player.c -ldl -g


###################################################################
all.o:
	${CC} ${CPPFLAGS} ${CFLAGS} -fpic -c ${SOURCE_DIR}/deck.c ${SOURCE_DIR}/card.c ${SOURCE_DIR}/board.c ${SOURCE_DIR}/player.c

###################################################################
#clients
client_basique.o: ${SOURCE_DIR}/${SOURCE_CLIENT}/client_basique.c ${SOURCE_DIR}/interface.h ${SOURCE_DIR}/board.h ${SOURCE_DIR}/player.h ${SOURCE_DIR}/deck.h
	${CC} ${CPPFLAGS} ${CFLAGS} -fpic ${SOURCE_DIR}/${SOURCE_CLIENT}/client_basique.c -c

client_basique: client_basique.o all.o
	${CC} -shared -o client_basique.so client_basique.o deck.o board.o player.o card.o


client_jalon1.o: ${SOURCE_DIR}/${SOURCE_CLIENT}/client_jalon1.c ${SOURCE_DIR}/interface.h
	${CC} ${CPPFLAGS} ${CFLAGS} -fpic ${SOURCE_DIR}/${SOURCE_CLIENT}/client_jalon1.c -c

client_jalon1: client_jalon1.o all.o
	${CC} -shared -o client_jalon1.so client_jalon1.o deck.o board.o player.o card.o

###################################################################
#board
test_board: board.o test_board.o card.o
	${CC} -o test_board test_board.o board.o card.o

test_board.o: ${TESTS_DIR}/test_board.c ${SOURCE_DIR}/board.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${TESTS_DIR}/test_board.c -c

board.o: ${SOURCE_DIR}/board.c ${SOURCE_DIR}/board.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SOURCE_DIR}/board.c -c


#deck
test_deck: deck.o test_deck.o
	${CC} -o test_deck test_deck.o deck.o

test_deck.o: ${TESTS_DIR}/test_deck.c ${SOURCE_DIR}/deck.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${TESTS_DIR}/test_deck.c -c

deck.o: ${SOURCE_DIR}/deck.c ${SOURCE_DIR}/deck.h ${SOURCE_DIR}/interface.h
	${CC} ${CPPFLAGS} ${CFLAGS} -fpic ${SOURCE_DIR}/deck.c -c


#card
test_card: card.o test_card.o
	${CC} -o test_card test_card.o card.o

test_card.o: ${TESTS_DIR}/test_card.c ${SOURCE_DIR}/card.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${TESTS_DIR}/test_card.c -c

card.o:  ${SOURCE_DIR}/card.c ${SOURCE_DIR}/card.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SOURCE_DIR}/card.c -c
