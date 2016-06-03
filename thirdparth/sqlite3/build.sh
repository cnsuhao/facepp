# ffmpeg
echo "extract sqlite-autoconf-3130000"
tar xzvf sqlite-autoconf-3130000.tar.gz 

echo "clean"
BASEDIR=`pwd`

cd sqlite-autoconf-3130000

echo "install to $BASEDIR"
./configure --prefix="$BASEDIR"
make -j1
if [ $? ne 0 ]; then
	echo "build sqlite3 fail"
	cd .. 
	rm -fr sqlite-autoconf-3130000
	exit 2
fi
make install
echo "make ok clean"
cd ..
rm -fr sqlite-autoconf-3130000
