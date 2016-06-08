cd ..\service
tar zcf ..\package\package.tgz *
cd ..\package 
tar zcf ..\ulozto.spk INFO PACKAGE_ICON_256.PNG PACKAGE_ICON.PNG package.tgz
del ..\package\package.tgz
