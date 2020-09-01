git clone https://github.com/spack/spack
git clone https://github.com/robertu94/spack_packages robertu94_packages
​
source /users/gfwilki/Compression_Energy_Experiment/install/spack/share/spack/setup-env.sh
spack repo add ./robertu94_packages
spack compiler find
spack external find
spack install libpressio+sz+zfp+lua
spack load libpressio