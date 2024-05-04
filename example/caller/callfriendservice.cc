#include "mprpcapplication.h"
#include "friend.pb.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

#include <iostream>

int main(int argc, char** argv){
    // 整个程序启动以后，想使用mprpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    fixbug::FriendServiceRpc_Stub stub(new MprpcChannel());

    fixbug::GetFriendsListRequest request;
    request.set_userid(1000);

    fixbug::GetFriendsListResponse response;

    MprpcController controller;
    stub.GetFriendsList(&controller, &request, &response, nullptr);

    // rpc调用完完成，读调用结果
    if(controller.Failed()){
        std::cout << controller.ErrorText() << std::endl;
    }
    else{
        if(response.result().errcode() == 0){
            std::cout << "rpc GetFriendsList response success!" << std::endl;
            int size = response.friends_size();
            for (int i = 0; i < size; i++){
                std::cout << "index:" << (i + 1) << " name:" << response.friends(i) << std::endl;
            }
        }
        else{
        std::cout << "rpc GetFriendsList response error : " << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}