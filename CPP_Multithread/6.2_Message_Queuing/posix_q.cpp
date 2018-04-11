/*
 * Создайте очередь сообщения POSIX с именем:
 * /test.mq
 * Тестовая среда пошлет в нее сообщение.
 * Получите его и сохраните в /home/box/message.txt
 */

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int main() {
  const std::string file_name{"/home/box/message.txt"};
  std::ofstream ofs{file_name};
  mqd_t queue_id = mq_open("/test.mq", O_CREAT | O_NONBLOCK | O_RDONLY, 0666, nullptr);
  struct mq_attr *attr = new mq_attr;

  mq_getattr(queue_id, attr);

  const auto buf_len = attr->mq_msgsize;
  char buf[buf_len];
  // we don't need attr anymore
  delete attr;

  ssize_t msg_len = mq_receive(queue_id, buf, buf_len, nullptr);
  buf[msg_len] = '\0';
  ofs << buf;
  mq_close(queue_id);

  return 0;
}
