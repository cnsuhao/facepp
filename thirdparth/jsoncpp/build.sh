# ffmpeg
echo "extract jsoncpp_src"
tar xvf jsoncpp_src.tar.bz2

echo "clean"
BASEDIR=`pwd`

cd jsoncpp_src
mkdir build
chmod 777 build -R
cd build

echo "install to $BASEDIR/jsoncpp/jsoncpp_src"
cmake -DCMAKE_INSTALL_PREFIX=../../../../libs/jsoncpp -DCMAKE_BUILD_TYPE=release -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DARCHIVE_INSTALL_DIR=../../../../libs/jsoncpp/lib -G "Unix Makefiles" ..
make 
make install
echo "make ok clean"
cd ../../
rm -fr jsoncpp_src
