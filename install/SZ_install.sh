SZ_FILES_PATH="/users/gfwilki/Compression_Energy_Experiment/compressors/SZ_Files"
SZ_PATH="/users/gfwilki/Compression_Energy_Experiment/compressors/SZ_Files/SZ"
cd $SZ_FILES_PATH
pwd
wait
pwd
git clone https://github.com/disheng222/SZ.git
wait
cd $SZ_PATH
wait
./configure --prefix=$SZ_FILES_PATH
wait
make clean
make
make install
