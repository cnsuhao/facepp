# ffmpeg
echo "extract curl-7.48.0"
tar xvf curl-7.48.0.tar.bz2 

echo "clean"
BASEDIR=`pwd`

cd curl-7.48.0 

echo "install to $BASEDIR"
./configure --prefix="$BASEDIR"/curl --disable-shared --enable-static --without-libidn --without-librtmp --without-gnutls --without-nss --without-libssh2 --without-zlib --without-winidn --disable-rtsp --disable-ldap --disable-ldaps --disable-ipv6 --with-ssl=../../../libs/openssl 
make -j5
make install
echo "make ok clean"
cd ..
rm -fr curl-7.48.0
mv curl ../../libs 
