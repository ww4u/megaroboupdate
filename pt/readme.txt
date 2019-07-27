工具介绍
1.该工具是用来给t4打包升级包的小工具，供专业人士使用。
2.config.xml为配置工具，packet可执行文件会调用该配置文件。
config.xml内容介绍：
<desc></desc>中为升级包描述，目前填写内容为本次升级包的版本定义：其格式为：MRX-T4_R0.0.0.0;
<mrq_path></mrq_path>中内容为MRQ的升级包的名字
<mrh_path></mrh_path>中内容暂时不需要修改，该内容是执行打包脚本时，MRH的压缩包名称
<output_file_name></output_file_name>中内容为合成的升级包的名称，请以.upd结尾。例：MRX-T4_R0.0.0.0.upd或MRX-T4_M.0.0.0.0.upd
3.packet.sh为打包升级包的脚本文件
4.update.txt为历史版本信息描述文件
5.packet为执行打包的可执行程序
6.update.xml为版本信息文件

7目前包的组成内容主要为两大类，一类是MRQ的升级文件，另一类为MRH的相关内容，MRH的内容包含
demo文件、update.txt、update.xml,本工具的工作就是将这些内容打包在一个文件中。

如何打包：
【使用环境】：请在本公司的MRH-T的编译环境中的虚拟机中使用，其他环境有可能不支持。
1、如果demo有更新，则替换demo文件夹中的内容【文件及以及子目录的文件名称不要修改】
2、每次打包都要修改update.txt 和update.xml文件。具体修改内容请参看本文件夹中的内容添加修改即可
3、清空本文件夹中的*.upd 和*.mrh文件。即清空MRQ和MRH的升级文件
4、把MRH的升级文件和MRQ的升级文件放到pt目录下；即以.mrh和.upd结尾的文件。
5、修改config.xml文件：
	<desc></desc>中写入本次升级包的升级版本格式为：MRX-T4_R0.0.0.0
	<mrq_path></mrq_path>中填入4步骤中的.upd文件的全名称
	<output_file_name></output_file_name>中填入输出文件名称。例如：MRX-T4_R0.0.0.0.upd，请一定要以.upd结尾
6、在本文件的所在的目录的父目录执行以下linux命令：
	chmod 777 pt -R
	cd pt
	./packet.sh
7、在pt目录下会生成目标文件，名称为5中设置的output_file_name
8、得到的升级包即可用MCT软件来升级了

