#!/usr/bin/env bash
set -e # if any command gives error, then exit
echo "Making object of LRU.cpp ..."
g++ -c LRU/LRU.cpp -I ./
echo "Done"

echo "Making object of socket.cpp ... "
g++ -c socket/socket.cpp 
echo "Done"

echo "Making object of serversocket.cpp ... "
g++ -c server/serversocket.cpp -I socket/.
echo "Done"

echo "Making object of clientsocket.cpp ... "
g++ -c  client/clientsocket.cpp -I socket/.
echo "Done"
# g++ LRU.o client.cpp -o client -I LRU/. -I ./

echo "Compiling server.cpp ... "
g++ -o my_server server/server.cpp serversocket.o socket.o LRU.o  -I LRU/. -I socket/. -I ./ -I /usr/include/mysql++ -I /usr/include/mysql -lmysqlpp -lmysqlclient -w
echo "Done"

echo "Compiling client.cpp ... "
g++ -o my_client client/client.cpp socket.o clientsocket.o -w -I socket/. -I ./ -I LRU/.
echo "Done"

echo "Removing object files ... "
rm -f *.o
echo "Done"
# ./client

echo 
echo "Starting server..."
sleep 1
./my_server