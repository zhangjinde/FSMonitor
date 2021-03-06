#ifndef __SERVERDEFINITIONS__
   #define __SERVERDEFINITIONS__

   #include <stdio.h>
   #include <stdlib.h>
   #include "common_definitions.h"
   #include "settings_parser.h"
   #include "mapping_structure.h"
   #include "mem_management.h"
   #include "mapping.h"
   #include "syncmapping.h"
   #include "client_register.h"
   #include "networking.h"
   #include "myfile.h"
   #include "thread.h"
   #include "time_utilities.h"
   #include "thread_lock.h"

   typedef struct _serverStructure{
       int ID;
       int timeout;                  //frequence by which the monitor must check for updates
       char **serverPaths;           //paths monitored by the server
       int serverPathsCount;         //number of server paths
       char *mapName;                //the name of the mapping
       pSyncMapping mapLock;         //the map Lock structure
       pMapping mapping;             //the mapping structure
       long long mapSize;            //the size of the mapping
       mappingStructure *structure;  //the logic structure of the mapping
       pToThread thread;             //object that points to the daemon thread, if this process owns it
       char *tcpPort;                //the tcp port the server is listening to
       char *udpPort;                //the udp port where the server sends uodates
       int maxClientConnections;     //the number of simultaneous client connections that the socket will handle
       unsigned long long startUpTime; //the time the server was started
       pThreadLock crLock;           //lock to sync accesses to shared resources inside the single process
       pThreadLock activeLock;       //lock used to guard over active variable
       pToThread tcpServer;                //server socket Descriptor
       clientRegister *clRegister;    //the data structure with client registrations.
   } serverStructure;


   // ===========================================================================
   //
   // terminate_server
   // Description: terminate the server execution, cleaning the mapping and
   // freeing the resources.
   // NOTE: this function MUST be called outside a critical section.
   // NOTE: this function calls cs_terminate_server
   //
   // ===========================================================================
   void terminate_server();

   // ===========================================================================
   //
   // cs1_terminate_server
   // NOTE: to use outside the critical section of syncmapping lock
   //
   // ===========================================================================
   void cs1_terminate_server();

   // ===========================================================================
   //
   // cs2_terminate_server
   // Description: terminate the server execution, cleaning the mapping and
   // freeing the resources.
   // Description:
   // NOTE: this function MUST be called inside a critical section
   //
   // ===========================================================================
   void cs2_terminate_server();
#endif
