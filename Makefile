OBJETOS = ICollectible.o IKey.o OrderedKey.o IIterator.o ICollection.o \
ListNode.o ListIterator.o List.o IDictionary.o OrderedDictionaryEntry.o \
OrderedDictionary.o String.o StringKey.o IntKey.o \
Game.o Record.o User.o \
Controller.o \


FUENTES = ICollection/interfaces/ICollectible.cpp ICollection/interfaces/ICollectible.h \
ICollection/interfaces/IKey.cpp ICollection/interfaces/IKey.h \
ICollection/interfaces/OrderedKey.cpp ICollection/interfaces/OrderedKey.h \
ICollection/String.cpp ICollection/String.h \
ICollection/StringKey.cpp ICollection/StringKey.h \
ICollection/Integer.cpp ICollection/Integer.h \
ICollection/IntKey.cpp ICollection/IntKey.h \
ICollection/interfaces/IIterator.cpp ICollection/interfaces/IIterator.h \
ICollection/interfaces/ICollection.cpp ICollection/interfaces/ICollection.h \
ICollection/collections/ListNode.cpp ICollection/collections/ListNode.h \
ICollection/collections/ListIterator.cpp ICollection/collections/ListIterator.h \
ICollection/collections/List.cpp ICollection/collections/List.h \
ICollection/interfaces/IDictionary.cpp ICollection/interfaces/IDictionary.h \
ICollection/collections/OrderedDictionaryEntry.cpp ICollection/collections/OrderedDictionaryEntry.h \
ICollection/collections/OrderedDictionary.cpp ICollection/collections/OrderedDictionary.h \
ICollection/String.cpp ICollection/String.h \
IColection/StringKey.cpp ICollection/StringKey.h \
IColection/IntKey.cpp ICollection/IntKey.h \
classes/sources/Game.cpp classes/headers/Game.h \
classes/sources/Record.cpp classes/headers/Record.h \
classes/sources/User.cpp classes/headers/User.h \
controller/Controller.cpp controller/Controller.h \



CC = g++
OPCIONES = -std=c++11 -g -Wall -Werror
JSON = -ljsoncpp

main: $(OBJETOS) Main.cpp Makefile
	$(CC) $(OPCIONES) $(OBJETOS) Main.cpp -o Main $(JSON)

ICollectible.o: ICollection/interfaces/ICollectible.h ICollection/interfaces/ICollectible.cpp
	$(CC) $(OPCIONES) -c ICollection/interfaces/ICollectible.cpp -o ICollectible.o

IKey.o: ICollection/interfaces/IKey.h ICollection/interfaces/IKey.cpp
	$(CC) $(OPCIONES) -c ICollection/interfaces/IKey.cpp -o IKey.o

OrderedKey.o: ICollection/interfaces/OrderedKey.h ICollection/interfaces/OrderedKey.cpp IKey.o
	$(CC) $(OPCIONES) -c ICollection/interfaces/OrderedKey.cpp -o OrderedKey.o

IIterator.o: ICollection/interfaces/IIterator.h ICollection/interfaces/IIterator.cpp ICollectible.o
	$(CC) $(OPCIONES) -c ICollection/interfaces/IIterator.cpp -o IIterator.o

ICollection.o: ICollection/interfaces/ICollection.h ICollection/interfaces/ICollection.cpp IIterator.o
	$(CC) $(OPCIONES) -c ICollection/interfaces/ICollection.cpp -o ICollection.o

ListNode.o: ICollection/collections/ListNode.h ICollection/collections/ListNode.cpp ICollection.o
	$(CC) $(OPCIONES) -c ICollection/collections/ListNode.cpp -o ListNode.o

ListIterator.o: ICollection/collections/ListIterator.h ICollection/collections/ListIterator.cpp ListNode.o
	$(CC) $(OPCIONES) -c ICollection/collections/ListIterator.cpp -o ListIterator.o

List.o: ICollection/collections/List.h ICollection/collections/List.cpp ListNode.o ListIterator.o
	$(CC) $(OPCIONES) -c ICollection/collections/List.cpp -o List.o

IDictionary.o: ICollection/interfaces/IDictionary.h ICollection/interfaces/IDictionary.cpp IKey.o ICollectible.o IIterator.o
	$(CC) $(OPCIONES) -c ICollection/interfaces/IDictionary.cpp -o IDictionary.o

OrderedDictionaryEntry.o: ICollection/collections/OrderedDictionaryEntry.h ICollection/collections/OrderedDictionaryEntry.cpp OrderedKey.o ICollectible.o
	$(CC) $(OPCIONES) -c ICollection/collections/OrderedDictionaryEntry.cpp -o OrderedDictionaryEntry.o

OrderedDictionary.o: ICollection/collections/OrderedDictionary.h ICollection/collections/OrderedDictionary.cpp OrderedDictionaryEntry.o ListNode.o IDictionary.o ListIterator.o
	$(CC) $(OPCIONES) -c ICollection/collections/OrderedDictionary.cpp -o OrderedDictionary.o

String.o: ICollection/String.h ICollection/String.cpp
	$(CC) $(OPCIONES) -c ICollection/String.cpp -o String.o

StringKey.o: ICollection/StringKey.h ICollection/StringKey.cpp
	$(CC) $(OPCIONES) -c ICollection/StringKey.cpp -o StringKey.o
IntKey.o: ICollection/IntKey.h ICollection/IntKey.cpp
	$(CC) $(OPCIONES) -c ICollection/IntKey.cpp -o IntKey.o

Game.o:  classes/headers/Game.h classes/sources/Game.cpp
	$(CC) $(OPCIONES) -c classes/sources/Game.cpp -o Game.o

Record.o: classes/headers/Record.h classes/sources/Record.cpp
	$(CC) $(OPCIONES) -c classes/sources/Record.cpp -o Record.o

User.o: classes/headers/User.h classes/sources/User.cpp
	$(CC) $(OPCIONES) -c classes/sources/User.cpp -o User.o

Controller.o: controller/Controller.h controller/Controller.cpp
	$(CC) $(OPCIONES) -c controller/Controller.cpp -o Controller.o $(JSON)

clean:
	rm -f $(OBJETOS) main

rebuild:
	make clean
	make