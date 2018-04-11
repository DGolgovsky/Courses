/*
 * Создайте очередь сообщения SysV с ключем:
 *
 * key_t key = ftok("/tmp/msg.temp", 1);
 * Тестовая среда пошлет в нее сообщение.
 *
 * struct message {
 * 	long mtype;
 * 	char mtext[80];
 * }
 *
 * Получите его и сохраните в /home/box/message.txt
 */

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

constexpr int first_msg_in_queue = 1;
constexpr size_t msg_size = 80;

struct message {
    long mtype;
    char mtext[msg_size];
};

int main() {
  const std::string file_name{"/home/box/message.txt"};
  std::ofstream ofs{file_name};
  key_t key = ftok("/tmp/msg.temp", 1);
  auto msgid = msgget(key, IPC_CREAT | 0666);
  auto *msg = new message;
  auto msg_len = msgrcv(msgid, msg, msg_size, first_msg_in_queue, 0);

  ofs << msg->mtext;
  delete msg;

  return 0;
}
