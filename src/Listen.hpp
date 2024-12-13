#pragma once
# include "Binding_from_server.hpp"
class Listen:public Binding_from_server
{
    private:
        int backlog;
        int listening;
    public:
        Listen(int domain, int type, int protocol, int port, u_long interface, int backlog);
        int  get_backlog();
};   