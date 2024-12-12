#pragma once
# include "Binding.hpp"
class Listen:public Binding
{
    private:
        int backlog;
        int listening;
    public:
        Listen(int domain, int service, int pprotocol, int por, u_long interface, int backlog);
        void start_listen();
};   