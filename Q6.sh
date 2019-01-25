#!/bin/bash
echo -e "User Information" >1.txt
who -u >>1.txt

echo -e "Operating System Type" >>1.txt
uname -a >>1.txt

echo -e "OS distribution"
lsb release -a >>1.txt

echo -e "OS version"
cat /etc/os-release >>1.txt

echo -e "Kenrel Version"
uname -or >>1.txt

echo -e "Kernel GCC version Build"
cat /proc/version >>1.txt

echo -e "Kernel build time"
uname -v >>1.txt

echo -e "System Architecture Information"
uname -a >>1.txt

echo -e "Information on file system memory"
free -m >>1.txt


