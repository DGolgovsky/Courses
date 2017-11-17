/ 20160605
// Эхо сервер TCP, получает строку от клиента, отправляет её обратно и разрывает соединение.

#include <iostream>
#include <string>

#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv) {
 int L_msoc = socket(
  // IPv4
  AF_INET,
  // TCP
  SOCK_STREAM,
  IPPROTO_TCP
 );
 if(L_msoc == -1) {
  std::cerr << "Ошибка при создании серверного сокета.\n" << std::endl;
  exit(EXIT_FAILURE);
 }
 // Назначаем адрес.
 struct sockaddr_in L_socaddr;
 L_socaddr.sin_family = AF_INET;
 L_socaddr.sin_port = htons(12345);
 // IP адрес = 0.0.0.0
 L_socaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 // Привязываем адрес.
 if(bind(L_msoc, (struct sockaddr *)(&L_socaddr), sizeof(L_socaddr)) == -1) {
  std::cerr << "Ошибка при привязки IP адреса серверному сокету.\n" << std::endl;
  close(L_msoc);
  exit(EXIT_FAILURE);
 }
 //
 if(listen(L_msoc, SOMAXCONN) == -1) {
  std::cerr << "Ошибка при активации режима прослушивания для серверного сокета.\n" << std::endl;
  close(L_msoc);
  exit(EXIT_FAILURE);  
 }
 printf("TCP эхо-сервер слушает\n");
 //
 bool l_flexit;
 int  l_len, l_len1, l_res, L_clsoc;
 char L_buf[1025];
 unsigned int l_count;
 l_len = 1024;
 //
 while(1) {
  // Получаем подключившийся клиентский сокет.
  L_clsoc = accept(L_msoc, 0, 0);
  if(L_clsoc < 0) {
   std::cerr << "Ошибка при получении клиентского сокета.\n" << std::endl;
   close(L_clsoc);
   //exit(EXIT_FAILURE);
  }
  // Получения запроса пользователя.
  l_count  = 0;
  l_flexit = false;  
  char *pstr;
  while(l_count < l_len) {
   l_res = recv(L_clsoc, L_buf + l_count, l_len - l_count, MSG_NOSIGNAL);
   if(l_res > 0) {
    l_count += l_res;   
   // Если ошибка.
   } else {    
    l_flexit = true;
    break;
   }
   // Если нашли разрыв строки.
   pstr = NULL;
   pstr = strstr(L_buf, "\n");
   if(pstr != NULL) {
    break;
   }   
  }
  if(!l_flexit) {
   L_buf[l_count] = 0;
   // Отправка данных пользователю.   
   l_len1 = l_count - 1;
   l_count  = 0;
   l_flexit = false;
   while(l_count < l_len1) {
    l_res = send(L_clsoc, L_buf + l_count, l_len1 - l_count, MSG_NOSIGNAL);
    if(l_res > 0) {
     l_count += l_res;
    // Если ошибка.
    } else {
     l_flexit = true;
     break;
    }
   }   
  }
  // Закрытие соединения на запись в сокет клиента (необходимо, чтобы клиент успел прочесть данные).
  shutdown(L_clsoc, SHUT_WR);
  // Закрытие соединения на чтение с сокета клиента.
  shutdown(L_clsoc, SHUT_RD);
  // Закрытие дескриптора сокета клиента.
  close(L_clsoc);
  //std::cout << L_buf << std::endl;
 }
 
 return 0;
}
