SZ_FILES_PATH="/users/gfwilki/Compression_Energy_Experiment/compressors/SZ_Files"
SZ_PATH="/users/gfwilki/Compression_Energy_Experiment/compressors/SZ_Files/SZ"
mkdir $SZ_FILES_PATH
cd $SZ_FILES_PATH
git clone https://github.com/disheng222/SZ.git
cd $SZ_PATH
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=$SZ_FILES_PATH
make
make install
