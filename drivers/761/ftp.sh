#/bin/bash
ftp -n<<!
open 192.168.1.136
user root root
biniry
hash
delete /opt/gpin.ko
put gpin.ko /opt/gpin.ko
cd /opt/
chmod 755 gpin.ko
bye
!
