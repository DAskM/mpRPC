#include "friend.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include "logger.h"

#include <iostream>
#include <string>
#include <vector>

class FriendService : public fixbug::FriendServiceRpc{
public:
    std::vector<std::string> GetFriendsList(uint32_t userid){
        std::cout << "do GetFriendsList service！" << std::endl;
        std::vector<std::string> vec;
        vec.push_back("Lee");
        vec.push_back("Cloud");
        vec.push_back("West");
        return vec;
    }

    void GetFriendsList(::google::protobuf::RpcController* controller,
                        const ::fixbug::GetFriendsListRequest* request,
                        ::fixbug::GetFriendsListResponse* response,
                        ::google::protobuf::Closure* done)
    {
        uint32_t userid = request->userid();
        std::vector<std::string> friendList = GetFriendsList(userid);
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for(std::string& name : friendList){
            std::string *p = response->add_friends();
            *p = name;
        }
        done->Run();
    }
};

int main(int argc, char** argv){
    LOG_INFO("first log message!");
    LOG_ERR("%s:%s:%d", __FILE__, __FUNCTION__, __LINE__);

    MprpcApplication::Init(argc, argv);

    RpcProvider provider;
    provider.NotifyService(new FriendService());

    provider.Run();
    return 0;
}