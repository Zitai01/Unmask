pushd "%~dp0"
mklink /j nvigi.models plugins\sdk\data\nvigi.models
mklink /j nvigi.test plugins\sdk\data\nvigi.test
popd
pushd "%~dp0\plugins\sdk"
mklink /j nvigi_core ..\..\nvigi_core
popd
pushd "%~dp0\sample"
mklink /j nvigi_core ..\nvigi_core
mklink /j nvigi_plugins ..\plugins\sdk
popd
pause
