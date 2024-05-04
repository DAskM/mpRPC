#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"

#include <iostream>

int main(int argc, char** argv){
    // 整个程序启动以后，想使用mprpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());

    fixbug::LoginRequest request;
    request.set_name("Cloud");
    request.set_pwd("123456");

    fixbug::LoginResponse response;

    stub.Login(nullptr, &request, &response, nullptr);

    // rpc调用完完成，读调用结果
    if(response.result().errcode() == 0){
        std::cout << "rpc login response : " << response.success() << std::endl;
    }
    else{
        std::cout << "rpc login response error : " << response.result().errmsg() << std::endl;
    }

    fixbug::RegisterRequest req;
    req.set_id(2000);
    req.set_name("mprpc");
    req.set_pwd("123123");

    fixbug::RegisterResponse rsp;

    stub.Register(nullptr, &req, &rsp, nullptr);

    if(0 == rsp.result().errcode()){
        std::cout << "rpc register response success:" << rsp.success() << std::endl;
    }
    else{
        std::cout << "rpc register response error: " << response.result().errmsg() << std::endl;
    }

    return 0;
}