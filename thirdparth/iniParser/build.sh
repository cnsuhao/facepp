# ffmpeg
echo "extract iniparser"
tar xvf iniparser.tar.bz2

echo "clean"
BASEDIR=`pwd`

cd iniparser
echo 'pwd'
echo "install to $BASEDIR"
make -j5
if [ $? -ne 0 ]; then	# if make return value is not 0
	echo "build iniparser fail err=2"
	cd ..
	rm -fr iniparser
	exit 2
fi

mkdir iniParser
mkdir iniParser/lib
mkdir iniParser/include

cp -r libini* iniParser/lib
cp -r src/*.h iniParser/include

#copy to libs in project dir 
cp  -r iniParser ../../../libs

echo "make ok clean"
cd ..
rm -fr iniparser
