#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <iostream>
#include <cerrno>
#include <cstdio>
#include <unistd.h>

using namespace std;

int main() {
  string path = "fifo";

  int m_file = socket(AF_UNIX, SOCK_DGRAM, 0);
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  unlink(path.c_str());
  strncpy(addr.sun_path, path.c_str(), sizeof(addr.sun_path) - 1);
  bind(m_file, (struct sockaddr*) &addr, sizeof(addr));
  
  char buf[128];
  
  while(true) {
    memset(buf, '\0', 128);
  
    struct sockaddr remaddr;
    socklen_t addr_len;
    recvfrom(m_file, buf, sizeof(buf), 0, &remaddr, &addr_len);
    string s(buf);
    
    cout << s << endl;
  }
}
