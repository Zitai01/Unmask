pushd "%~dp0"
setlocal enableextensions enabledelayedexpansion
IF NOT exist nvigi.models (
    echo "nvigi.models directory not found.  Please run the setup_links.bat script before running this script"
    pause
    goto :eof
)
pushd nvigi.models
for /r %%x in ("*.bat") do (
    call %%x
)
popd
 
:eof

