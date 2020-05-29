# ESP32+VSCODE+CMake

1.  须设置IDF_PATH环境变量，如IDF_PATH="F:/esp/esp-idf-v4.0.1"

2.  设置"c_cpp_properties.json"，添加IDF头文件路径，如"${IDF_PATH}/**"

3.  设置编译工具链，xtensa-esp32-elf
    CTRL+SHIFT+P -> 输入框CMake: Edit User-Local CMake Kits -> 添加工具链路径，如
    {
        "name": "xtensa-esp32-elf",
        "compilers": {
        "C": "F:\\esp\\tools\\tools\\xtensa-esp32-elf\\esp-2019r2-8.2.0\\xtensa-esp32-elf\\bin\\xtensa-esp32-elf-gcc.exe",
        "CXX": "F:\\esp\\tools\\tools\\xtensa-esp32-elf\\esp-2019r2-8.2.0\\xtensa-esp32-elf\\bin\\xtensa-esp32-elf-g++.exe"
        }
    }