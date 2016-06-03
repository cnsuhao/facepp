#!/bin/bash
function manulInstall( )
{
   
    if [ ! -d "$1/include" ]; then
        cd $1 
      	echo "begin install: $1,Press Y to continue!"
      	read options
        if [ $options"x" != "Yx" -a $options"x" != "yx" ]; then
          	echo "root: skip install $1"
       	else
           	sh build.sh
			err=$?				# $?: return code of prev commandd execution results
			if [ $err -ne 0 ]; then
			   	echo "root: install fail $1 err=$err"
			   	exit
			fi	   
           	echo "root: install done $1"
       	fi
          
        cd .. 
        
    else
        echo "already install: $1"
    fi
}
 
function autoInstall( )
{
	if [ ! -d "$1/include" ]; then
		cd $1
		sh build.sh
		if [ $? -ne 0 ]; then
			echo "root: install fail: $1"
			exit
		fi
		echo "root: install done $1"
		cd ..	
	else
		echo "already install: $1"
	fi
}

## start in here 
echo "are you sure to install thirdpary [Y/N]"
read options
echo $options
if [ $options"x" != "Yx" -a $options"x" != "yx" ]; then
    echo "you choose No"
    exit
fi

#------------------------------------------------------
list_dir="openssl curl iniParser sqlite3"
#list_dir="iniParser sqlite3"

for dir in $list_dir
do
   if [ -d $dir ];
   then
     	echo "root: find thirdparty lib:"$dir
     	autoInstall $dir
   else
     	echo "root: $dir not a dir"
    	exit
   fi
done 


