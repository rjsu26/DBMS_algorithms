cd LRU
g++ -c LRU.cpp -I ../
cd ..
g++ LRU/LRU.o client.cpp -o client -I LRU/. -I ./
./client