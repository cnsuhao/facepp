#/bin/sh


unistall()
{
	cd $1
	del_dir_list=$(ls -l ./ |awk '/^d/ {print $NF}')
	for del_dir in $del_dir_list
	do
		if [ ! -d $del_dir ]; then
			echo "$del_dir not a directory"
			cd ..
			return
		fi
		if [ $2 -eq  1 ]; then
			if [ $del_dir == "lib" -o $del_dir == "include" ]; then
				continue
			fi
			echo "rm -fr $del_dir"
    		rm -fr $del_dir
		else
			echo "rm -fr $del_dir"
    		rm -fr $del_dir
		fi
	done
	cd ..
}


echo -e "are you remove the libs[Y/N]"
read options
echo $options
if [ $options"x" != "yx" -a $options"x" != "Yx" ]; then
	echo "you select No"
	exit
fi

dir_list="openssl curl iniParser sqlite3 jsoncpp zlog"
for dir in $dir_list
do
	if [ -d $dir ]; then
		echo "find a directory: $dir"
		rm -rf $dir
	fi
done
