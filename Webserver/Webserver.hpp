#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP
# include "incl.hpp"
# include "Server.hpp"
# include "PollFD.hpp"

class Webserver {
    private:
        std::vector<Server*> servers;
        PollFD*     pfds;
        int         count;
        const std::string* OK_repl;
        const std::string* NotFound_repl;
        void*       getInetAddress(struct sockaddr* sa);
        void    serveReq(char* buf, int to, Server* server);
        void    sendFile(int to, const char* header, std::size_t hlen, const char* file);
        void    doGET_index(int sender);
        void    doGET(int sender, const char* req, Server* server);
        void    doPOST(int sender, const char* req, Server* server);
        void    doPUT(int sender, const char* req, Server* server);
        void    doDELETE(int sender, const char* req, Server* server);
        void    noneMethod(int sender, const char* req, Server* server);
    public:
        Webserver();
        ~Webserver();
        Webserver(const Webserver&);
        Webserver& operator=(const Webserver&);
        void    describe() const;
        int     invokeServer(int index);
        void    addServer(const std::string& port, const std::string& root = "./", const std::string& name = "N/A");
        void    setPFD();

        void    serverForever();

        class WebservExceptServFailed: public std::exception {
            private:
                std::string& port;
                std::string& name;
            public:
                WebservExceptServFailed(std::string& port, std::string& name);
                virtual const char* what() const throw();
        };
        class GETException: public std::exception {
            public:
                virtual const char* what() const throw();
        };
};

#endif