#/bin/bash
ftp -n<<!
open 192.168.1.136
user root root
biniry
hash
delete /opt/gpout-test
put test/gpout-test /opt/gpout-test
cd /opt/
chmod 755 gpout-test
bye
!
