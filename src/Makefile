CC = gcc

DIR_THRIFT_INCLUDE = /home/realjin/install/thrift-0.8.0/lib/c_glib/src/
DIR_GLIB_64_INCLUDE = /usr/lib/x86_64-linux-gnu/glib-2.0/include/
DIR_GLIB_INCLUDE = /usr/include/glib-2.0/
DIR_CASSANDRA_INCLUDE = /home/realjin/install/apache-cassandra-1.0.7/interface/gen-c_glib/


all:
	gcc config.c el.c net.c server_sm.c main.c -I$(DIR_THRIFT_INCLUDE) -I$(DIR_GLIB_64_INCLUDE) -I$(DIR_GLIB_INCLUDE) -I$(DIR_CASSANDRA_INCLUDE) -o smserver
