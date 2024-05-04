#include "test.pb.h"

#include <iostream>
#include <string>

using namespace fixbug;

int main(){
    LoginRequest req;
    req.set_name("Cloud");
    req.set_pwd("123456");

    std::string send_str;
    if(req.SerializeToString(&send_str)){
        std::cout << send_str << std::endl;
    }

    LoginRequest resp;
    if(resp.ParseFromString(send_str)){
        std::cout << resp.name() << std::endl;
        std::cout << resp.pwd() << std::endl;
    }
    

    return 0;
}