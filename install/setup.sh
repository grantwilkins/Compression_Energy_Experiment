COMPRESSOR_PATH = "/users/gfwilki/compressors"

apt-get update
apt-get install g++ cmake perl python3 libssl-dev git curl xz-utils tar gzip pkg-config bzip2 zstd patch snapd python-pip cpufrequtils linux-tools-common linux-tools-generic linux-cloud-tools-generic linux-tools-4.15.0-101-generic linux-cloud-tools-4.15.0-101-generic msr-tools
snap install cmake
pip install numpy
bash libpressio_install.sh

cd 
mkdir $COMPRESSOR_PATH
cd $COMPRESSOR_PATH
bash SZ_install.sh
#bash SZ_test.sh
cd "/users/gfwilki/compressors"
bash ZFP_install.sh
bash ZFP_test.sh
cd