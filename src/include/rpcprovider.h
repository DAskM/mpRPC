#pragma once

#include "google/protobuf/service.h"
#include "logger.h"

#include <memory>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <string.h>
#include <functional>
#include <google/protobuf/descriptor.h>
#include <unordered_map>

class RpcProvider{
public:
    void NotifyService(::google::protobuf::Service *service);

    void Run();

private:
    // 组合了TcpServer
    std::unique_ptr<muduo::net::TcpServer> m_tcpsercerPtr;
    // 组合了EventLoop
    muduo::net::EventLoop m_eventLoop;

    struct ServiceInfo{
        google::protobuf::Service *m_service;
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor *> m_methodMap;
    };

    std::unordered_map<std::string, ServiceInfo> m_serviceMap;

    void OnConnection(const muduo::net::TcpConnectionPtr &conn);

    void OnMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp);

    void SendRpcResponse(const muduo::net::TcpConnectionPtr &, google::protobuf::Message *);
};