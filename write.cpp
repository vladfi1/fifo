#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <iostream>
#include <cerrno>
#include <cstdio>

using namespace std;

int main() {
	int m_fd;
	sockaddr_un m_addr;
  
  string path = "fifo";  
  
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sun_family = AF_UNIX;
	strncpy(m_addr.sun_path, path.c_str(), sizeof(m_addr.sun_path) - 1);

	m_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	
	cout << "m_fd: " << m_fd << endl;
	
	string message = "FIFO";
	
	int result = sendto(
		m_fd,
		message.c_str(),
		message.size() + 1,
		0,
		reinterpret_cast<sockaddr*>(&m_addr),
		sizeof(m_addr));
  
  cout << "result: " << result << endl;
  
  //cout << "errno: " << errno << endl;
  perror("errno");
  
}
