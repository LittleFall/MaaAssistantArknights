#include "AsstCaller.h"

#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <string>

int main([[maybe_unused]] int argc, char** argv)
{
    const auto cur_path = std::filesystem::path(argv[0]).parent_path().string();

    // 可以将日志、调试图片等存到别的目录下，需要在最一开始调用。不调用默认保存到资源同目录
    // AsstSetUserDir(cur_path.c_str());

    // 这里默认读取的是可执行文件同目录下 resource 文件夹里的资源
    bool loaded = AsstLoadResource(cur_path.c_str());

    // 增量更新国际服的资源
    //const auto en_path = cur_path / "resource" / "global" / "YoStarEN";
    //loaded &= AsstLoadResource(en_path.string().c_str());

    if (!loaded) {
        std::cout << "load resource failed" << std::endl;
        return -1;
    }

    auto ptr = AsstCreate();
    if (ptr == nullptr) {
        std::cerr << "create failed" << std::endl;
        return -1;
    }

    bool connected = AsstConnect(ptr, "adb", "127.0.0.1:5555", nullptr);
    if (!connected) {
        std::cerr << "connect failed" << std::endl;
        AsstDestroy(ptr);
        ptr = nullptr;

        return -1;
    }

    /* 详细参数可参考 docs / 集成文档.md */

    //AsstAppendTask(ptr, "StartUp", nullptr);

    //AsstAppendTask(ptr, "Fight", R"(
    //{
    //    "stage": "1-7"
    //}
    //)");

    //AsstAppendTask(ptr, "Recruit", R"(
    //{
    //    "select":[4],
    //    "confirm":[3,4],
    //    "times":4
    //}
    //)");

    //AsstAppendTask(ptr, "Infrast", R"(
    //{
    //    "facility": ["Mfg", "Trade", "Power", "Control", "Reception", "Office", "Dorm"],
    //    "drones": "Money"
    //}
    //)");

    //AsstAppendTask(ptr, "Visit", nullptr);

    //AsstAppendTask(ptr, "Mall", R"(
    //{
    //    "shopping": true,
    //    "buy_first": [
    //        "许可"
    //    ],
    //    "black_list": [
    //        "家具",
    //        "碳"
    //    ]
    //}
    //)");

    //AsstAppendTask(ptr, "Award", nullptr);

//    AsstAppendTask(ptr, "Roguelike", R"(
//{
//    "squad": "突击战术分队",
//    "roles": "先手必胜",
//    "core_char": "棘刺"
//}
//)");

    //AsstAppendTask(ptr, "Copilot", R"(
    //{
    //    "stage_name": "如帝国之影",
    //    "formation": true
    //}
    //)");

    AsstAppendTask(ptr, "Debug", nullptr);

    AsstStart(ptr);

    std::ignore = getchar();

    AsstStop(ptr);
    AsstDestroy(ptr);
    ptr = nullptr;

    return 0;
}
