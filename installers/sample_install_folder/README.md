# How to create an installer

* Build application in Release mode in the QtCreator.
* copy the sample_install_folder to somewhere.
* delete everything from `sample_install_folder/packages/QuestioningApp/data`.
* rename the `sample_install_folder/packages/QuestioningApp` folder on demand. (To QAStudent for example)
* edit the following files (and insert QAStudent for example instead of QuestioningApp everywhere.)
	* `sample_install_folder/packages/QuestioningApp/meta/installscript`
	* `sample_install_folder/packages/QuestioningApp/meta/package.xml`
	* `sample_install_folder/config/config.xml`
* Copy the executable from the `<Release build folder>/src` and place it into `sample_install_folder/packages/QuestioningApp/data`
* Now we are going to copy all the dependencies there:
	* `cd sample_install_folder/packages/QuestioningApp/data`
	* `C:\Qt\5.15.1\mingw81_32\bin\windeployqt.exe <name of the exe>`
	* Try running the exe. There will still be some missing dependencies. Copy these from `C:\Qt\5.15.1\mingw81_32\bin`
	* If you can run the exe, then every dependency is copied and we can build the installer.
* Build the installer by executing: 
	* `cd ../../..` (cd into `sample_install_folder`)
	* `C:\Qt\Tools\QtInstallerFramework\3.2\bin\binarycreator.exe --offline-only -c config/config.xml -p packages <installer name>.exe` 