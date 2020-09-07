COMPRESSOR_PATH="/users/gfwilki/Compression_Energy_Experiment/compressors"

apt-get update
apt-get install g++ cmake perl python3 libssl-dev git curl xz-utils tar gzip pkg-config bzip2 zstd patch gfortran snapd python-pip cpufrequtils linux-tools-common linux-tools-generic linux-cloud-tools-generic linux-tools-4.15.0-101-generic linux-cloud-tools-4.15.0-101-generic msr-tools
modprobe msr
snap install cmake --classic
pip install numpy
bash libpressio_install.sh

cd 
mkdir $COMPRESSOR_PATH
cd $COMPRESSOR_PATH
bash "${COMPRESSOR_PATH}/SZ_install.sh"
#bash SZ_test.sh
cd "/users/gfwilki/Compression_Energy_Experiment/compressors"
bash "${COMPRESSOR_PATH}/ZFP_install.sh"
bash "${COMPRESSOR_PATH}/ZFP_test.sh"
cd
source /users/gfwilki/Compression_Energy_Experiment/install/spack/share/spack/setup-env.sh
spack load libpressio