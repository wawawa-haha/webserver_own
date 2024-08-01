#include"conf.h"
int main() {
    Config::lookup<int>("kind", "kind of vat", 123);
    Config::lookup<double>("smile", "smile_hahaha", 123.153);
    Config::lookup<std::string>("str", "str_test", "tttttt");
    // 创建一个整数类型的配置变量
    Config::tarvel();
    return 0;
}