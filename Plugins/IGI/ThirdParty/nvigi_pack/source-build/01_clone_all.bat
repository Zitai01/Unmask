pushd "%~dp0"
git clone git@github.com:NVIDIA-RTX/NVIGI-Core.git
git clone git@github.com:NVIDIA-RTX/NVIGI-Plugins.git
git clone  --recurse-submodules git@github.com:NVIDIA-RTX/NVIGI-3d-Sample.git
popd
