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


echo -e "input value:\n1:     retait lib and include;\nother: delete all install file"
read options
echo $options

dir_list="openssl curl iniParser sqlite3"
for dir in $dir_list
do
	if [ -d $dir ]; then
		echo "find a directory: $dir"
		unistall $dir $options
	fi
done
