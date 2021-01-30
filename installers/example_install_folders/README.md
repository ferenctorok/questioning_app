# How to create an installer

* Build application in Release mode in the QtCreator.
* copy the student or the teacher example install folders somewhere.
* delete everything from `<path to install folder>/packages/<App name>/data`.
* adjust the version numbers in the following files:
	* `<path to install folder>/packages/QuestioningApp/meta/package.xml`
	* `<path to install folder>/config/config.xml`
* Copy the executable from the `<Release build folder>/src` and place it into `<path to install folder>/packages/App name/data`
* Now we are going to copy all the dependencies there:
	* `cd <path to install folder>/packages/QuestioningApp/data`
	* `C:\Qt\5.15.1\mingw81_32\bin\windeployqt.exe <name of the exe>.exe`
	* Try running the exe. If there are still some missing dependencies. Copy these from `C:\Qt\5.15.1\mingw81_32\bin`
	* If you can run the exe, then every dependency is copied and we can build the installer.
* Build the installer by executing: 
	* `cd ../../..` (cd into `<path to install folder>`)
	* `C:\Qt\Tools\QtInstallerFramework\3.2\bin\binarycreator.exe --offline-only -c config/config.xml -p packages <installer name>.exe` 