# UI界面
1、保存项目到本地后编译，修改CMakeLists.txt中第四行的qt目录，改成自己的qt地址，再点击Cmake配置

2、点击Cmake生成后会在build/debug文件夹下生成exe文件

3、此时点击exe文件会显示缺少dll文件，在终端debug文件夹下运行命令`H:/qt6/6.8.3/msvc2022_64/bin/windeployqt.exe shared_screen.exe`，前面的是你自己的qt目录位置。然后就可以运行。
