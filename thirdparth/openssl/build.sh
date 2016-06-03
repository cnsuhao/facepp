# openssl
echo "extract openssl-1.0.1k"
tar xzvf openssl-1.0.1k.tar.gz 

echo "clean"
BASEDIR=`pwd`

cd openssl-1.0.1k

echo "install to $BASEDIR"
./config --prefix="$BASEDIR" shared
make -j1
if [ $? ne 0 ]; then
	echo "build openssl fail"
	cd ..
	rm -fr openssl-1.0k
	exit 2
fi

make install
echo "make ok clean"
cd ..
rm -fr openssl-1.0.1k
