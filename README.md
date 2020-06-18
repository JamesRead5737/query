# query

Create user reader using mysql root user:

CREATE USER 'reader'@'localhost' IDENTIFIED BY '1q2w3e4r';

Grant read permission for user reader:

GRANT SELECT ON crawl.* TO 'reader'@'localhost';

GRANT SELECT ON indexes.* TO 'reader'@'localhost';

Compile with:

gcc -o query query.c -g -I/usr/include/mysql -lmysqlclient 
