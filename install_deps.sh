LIBCURL=libcurlpp-dev
LIBGUMBO=libgumbo-dev
LIBMYSQL=libmysqlcppconn-dev
MYSQL_SERVER=mysql-server
MYSQL_CLIENT=mysql-client

sudo apt update
sudo apt-get install $LIBCURL $LIBGUMBO $LIBMYSQL $MYSQL_SERVER $MYSQL_CLIENT -y