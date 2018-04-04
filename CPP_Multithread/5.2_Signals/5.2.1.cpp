/*
 * Задача на сигналы.
 *
 * Создайте процесс (сохраните его PID в
 * /home/box/pid), устойчивый к сигналам
 * SIGTERM и SIGINT (неубиваемый).
 */

#include <signal.h>
#include <unistd.h>

#include <fstream>

int main(int argc, char* argv[])
{
    std::ofstream f("/tmp/pid_stepik");
    f << getpid();
    f.close();
    
    signal(SIGTERM, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    while (true)
        sleep(1);
    
    return 0;
}

