# ffmpeg
echo "extract iniparser"
tar xvf iniparser.tar.bz2

echo "clean"
BASEDIR=`pwd`

cd iniparser
echo 'pwd'
echo "install to $BASEDIR"
make -j5
if [ $? -ne 0 ]; then
	echo "build iniparser fail err=2"
	cd ..
	rm -fr iniparser
	exit 2
fi

mkdir ../lib
mkdir ../include
cp -r libini* ../lib
cp -r src/*.h ../include
echo "make ok clean"
cd ..
rm -fr iniparser
