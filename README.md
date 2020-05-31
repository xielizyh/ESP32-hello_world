# ESP32+VSCODE+CMake

#   安装CMake
    下载后缀为.msi的文件安装，并添加至系统环境变量，如C:\Program Files\CMake\bin

#   安装CMake Tools插件
    在vscode里搜索安装CMake Tools，它是vscode中编译工程的工具

#   配置settings.json
    配置CMake路径和CMake generator，如
    {
        "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
        "C_Cpp.errorSquiggles": "Disabled",

        "cmake.cmakePath": "C:/Program Files/CMake/bin/cmake",
        "cmake.configureOnOpen": true,
        "cmake.generator": "MinGW Makefiles"
    }

#   安装MinGW
    去官网下载安装器，并安装相应的组件

#   设置编译工具链
    下载xtensa-esp32-elf编译工具链，并添加至环境变量
    设置xtensa-esp32-elf为cmake tools的kits(套件)
    CTRL+SHIFT+P -> 输入框CMake: Edit User-Local CMake Kits -> 添加工具链路径，如
    {
        "name": "xtensa-esp32-elf",
        "compilers": {
        "C": "F:\\5---esp\\tools\\tools\\xtensa-esp32-elf\\esp-2019r2-8.2.0\\xtensa-esp32-elf\\bin\\xtensa-esp32-elf-gcc.exe",
        "CXX": "F:\\5---esp\\tools\\tools\\xtensa-esp32-elf\\esp-2019r2-8.2.0\\xtensa-esp32-elf\\bin\\xtensa-esp32-elf-g++.exe"
        }
    }

#   下载esp-idf
    去乐鑫官网下载SDK，并设置IDF_PATH环境变量，如IDF_PATH="F:/esp/esp-idf-v4.0.1"

#   安装esp-idf相关工具
    下载构建工具Ninja，并添加至环境变量
    下载配置工具mconf-idf，并添加到环境变量

#   安装python及需求包
    安装python3.7，如果提示The following Python requirements are not satisfied，则cmd中执行
    python -m pip install --user -r F:\\5---esp\\esp-idf-v4.0.1\\requirements.txt，即执行IDF_PATH下的需求文档

#   编译
    点击CMake工具栏中的Build即可，完成后生成hello-world.bin文件

#   工程中查看SDK中的API原型
    如果想实现Go to Definition，须设置"c_cpp_properties.json"，添加IDF头文件路径，如"${IDF_PATH}/**"

#  参考链接
    https://docs.espressif.com/projects/esp-idf/zh_CN/v4.0/get-started/windows-setup-scratch.html
    https://blog.csdn.net/MakerCloud/article/details/93545513
    https://blog.csdn.net/qq_36275734/article/details/84112095