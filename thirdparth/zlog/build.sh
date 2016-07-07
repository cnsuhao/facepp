# ffmpeg
echo "extract zlog"
tar xvf zlog.tar.gz 

echo "clean"
BASEDIR=`pwd`

cd zlog

echo "install to $BASEDIR/zlog/zlog"
make PREFIX=$BASEDIR/zlog/zlog
make PREFIX=$BASEDIR/zlog/zlog install
mv zlog ../../../libs
echo "make ok clean"
cd ..
rm -fr zlog
