#pragma once
# include "Binding.hpp"
class Listen:public Binding
{
    private:
        int backlog;
        int listening;
    public:
        Listen(int domain, int type, int protocol, int port, u_long interface, int backlog);
        void start_listen();
};   