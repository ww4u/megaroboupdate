1.软件安装
①使用QT Creator 打开工程文件megaroboupdate.pro
②编译生成可执行文件
③使用windeployqt打包可执行文件

2.软件使用
①该软件是命令行软件
    使用./undo.exe -h可以查看命令行的参数帮助
②该软件有两种使用用途：将mrh文件和mrq文件进行打包、将打包的文件解出来生成mrh文件和mrq文件
    1.打包
	./undo.exe -c -q mrq_file_name -r mrh_file_name -o out_file_name
	-q之后的参数是mrq升级文件的源文件绝对路径名，-r后边跟的是mrh升级文件的绝对路径名，-o 后边跟的是输出文件的绝对路径文件名。升级的时候需要将out_file_name的名字以.p命名，不然使用mct升级的时候会找不到相应文件。
    2.解包
	./undo.exe -x -p package_name 
	-p之后的参数是包文件绝对路径名，执行成功之后会在package_name 相同目录下生成mrh和mrq的文件文件名以*.dat为后缀。