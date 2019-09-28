for (( ; ; ))
do
 /usr/local/bin/node generate.js
 /usr/local/bin/node ../tools/upload.js clock.tf1
 echo Upload done waiting 60 seconds...
 sleep 60
done