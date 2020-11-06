<h1> Caching</h1>
<h4>To implement different types of caching and use them in a client-server system. The client and the server programmes will be communicating using sockets. </h4>

-----

#### Setup 
1. Install C++ connector for MySQL using the command: `sudo apt-get install libmysqlclient-dev libmysql++-dev libmysqlcppconn-dev`

#### Implementations: 
1. **_LRU_**: Least Recently Used cache eviction policy
2. **_LFU_** : [To be implemented] Least Frequently Used cache eviction policy
3. **_client_** : A dummy client putting requests on to the server
4. **_server_** : The programme taking requests from clients using socket listeners in localhost, and give options to either make a new profile or fetch profile with the help of UserIDs. 
5. **_compileRun. sh_** : Bash program to generate object files and link them to create the _my_server_ and _my_client_ programs. To run, use : `chmod +x compileRun.sh; ./compileRun.sh` . This will automatically start the server program too.


#### References
1. Socket programming codes: <a href="https://tldp.org/LDP/LG/issue74/tougher.html" target="_blank">tldp.org</a>