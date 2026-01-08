#include <pthread.h>
#include <stdio.h>

int i = 0;
pthread_mutex_t lock;

void* rutin(void* arg)
{
    pthread_mutex_lock(&lock);
    for (int j= 0; j<1000000; j++)
        i++;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    pthread_mutex_init(&lock,NULL);

    pthread_create(&t1, NULL, rutin, NULL);
    pthread_create(&t2, NULL, rutin, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("sonuç: %d(beklenen:2000000)\n",i);
    pthread_mutex_destroy(&lock);
    return 0;
}
