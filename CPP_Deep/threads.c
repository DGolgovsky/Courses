#include <pthread.h>

void *thread_routine(void *arg)
{
    int errflag;
    // ...
    errflag = pthread_detach(pthread_self());
    if (errflag != 0) {
        //do something
    }

    return arg; // return NULL etc.
}

int main(int argc, char ** argv)
{
    int errflag;
    pthread_t thread;

    errflag = pthread_create(
            &thread,
            NULL,
            thread_routine,
            NULL);

    if (errflag != 0) {
        //make something
    }

    return EXIT_SUCCESS;
}
