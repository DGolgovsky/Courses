/*
 * Задача на зомби.
 *
 * Создайте два процесса - родитель и потомок 
 * (сохраните их PIDы в /home/box/pid_parent и /home/box/pid_child).
 *
 * Потомок должен убиваться по SIGTERM.
 * При убийстве потомка не должно остаться процессов-зомби.
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE * fd;
    pid_t cpid;
    int status;
    
    cpid = fork();
    if (cpid == -1)
        return 1;
    
    if (cpid == 0) {
        fd = fopen("/home/box/pid_child","a");
        fprintf(fd,"%d",getpid());
        fclose(fd);
        
        signal(SIGTERM, SIG_DFL);
        signal(SIGABRT, SIG_IGN);
        while (1)
            sleep(1);
    } else {
        fd = fopen("/home/box/pid_parent","a");
        fprintf(fd,"%d",getpid());
        fclose(fd);
        
        signal(SIGTERM, SIG_IGN);
        signal(SIGABRT, SIG_IGN);
        
        wait(&status);
    }
    
    return 0;
}

