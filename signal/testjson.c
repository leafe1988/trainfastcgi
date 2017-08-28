#include<iostream>
#include<json/json.h>
#include <fcgi_stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  
using namespace std;
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <alloca.h>
#include <fcgiapp.h>
#define LISTENSOCK_FILENO 0
#define LISTENSOCK_FLAGS 0

std::string gettestjsondata();
int main()
{
    

    int count;
    char* data;
    count = 0; 
    
    while (FCGI_Accept() >= 0){
     data = getenv("QUERY_STRING");
    char buf[17];  
    memset(buf,0,17);
   // for(int i =0 ;i < 16;i++)
	//buf[i] = fgetc(stdin);
     fread(buf, 1, 16, stdin);
     printf("Content-type:application/json\r\n\r\n");
     printf("{\"retcode2\":0, \"request\":{\"json data is\":%s, \"count\":%d, \"Query string is\" %s}}", gettestjsondata().c_str(), count++,data);
	printf("data is %s", buf);
        }
    return 0;
}

int main2(int argc, char** argv) {
  openlog("testfastcgi", LOG_CONS|LOG_NDELAY, LOG_USER);
  int err = FCGX_Init(); /* call before Accept in multithreaded apps */
  if (err) { syslog (LOG_INFO, "FCGX_Init failed: %d", err); return 1; }
  FCGX_Request cgi;
  err = FCGX_InitRequest(&cgi, LISTENSOCK_FILENO, LISTENSOCK_FLAGS);
  if (err) { syslog(LOG_INFO, "FCGX_InitRequest failed: %d", err); return 2; }

  while (1) {
    err = FCGX_Accept_r(&cgi);
    if (err) { syslog(LOG_INFO, "FCGX_Accept_r stopped: %d", err); break; }
    char** envp;
    int size = 200;
    for (envp = cgi.envp; *envp; ++envp) size += strlen(*envp) + 11;
    char*  result = (char*) alloca(size);
    strcpy(result, "Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");
    strcat(result, "<html><head><title>testcgi</title></head><body><ul>\r\n");

    for (envp = cgi.envp; *envp; ++envp) {
      strcat(result, "<li>"); 
      strcat(result, *envp); 
      strcat(result, "</li>\r\n");
    }

    strcat(result, "</ul></body></html>\r\n");
    FCGX_PutStr(result, strlen(result), cgi.out);
  }

  return 0;
}
std::string gettestjsondata()
{
   string test="{\"id\":1,\"name\":\"kurama\"}";
    Json::Reader  reader;
    Json::Value   value;

    if(reader.parse(test,value))
    {
        if(!value["id"].isNull())
        {
	 return value["name"].asString();
        }
    }
return "";
}
