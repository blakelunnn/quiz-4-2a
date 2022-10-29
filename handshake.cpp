#include <iostream>
// include additional necessary headers
#include <thread>
#include <vector>
#include <semaphore.h>
#include <string>

sem_t querySemaphore{0};
sem_t responseSemaphore{0};

void query(int count, std::string s) {
    // Should print: the print number (starting from 0), "SYN", and the three dots "..."
    for(int x = 0; x < count; x++)
    {
        sem_wait(&querySemaphore);
        std::cout << "[" << x << "]" << s << "...";
        sem_post(&responseSemaphore);
    }
}

void response(int count, std::string s) {
    // Should print "ACK"
    for(int x = 0; x < count; x++)
    {
        sem_wait(&responseSemaphore);
        std::cout << s << std::endl;
        sem_post(&querySemaphore);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: ./handshake <count>\n");
        exit(1);
    }

    /**
     * Steps to follow:
     * 1. Get the "count" from cmd args
     * 2. Create necessary synchronization primitive(s)
     * 3. Create two threads, one for "SYN" and the other for "ACK"
     * 4. Provide the threads with necessary args
     * 5. Update the "query" and "response" functions to synchronize the output
    */
   
    int count = atoi(argv[1]);

    sem_post(&querySemaphore);
    std::thread queryAction(query, count, "SYN");
    std::thread responseAction(query, count, "ACK");

    queryAction.join();
    responseAction.join();

    sem_destroy(&querySemaphore);
    sem_destroy(&responseSemaphore);
   
    return 0;
}
