#include <pthread.h>
#include <stdio.h>

int expansive_function() { return 42; }

void *expansive_function_w(void* arg) {
    puts("expansive_function_w");
    int *out = (int *)arg;
    *out = expansive_function();
    return arg;
}

int parallel_sum_expansive_functions() {
    int         result[2];
    pthread_t   thread[2];

    puts("parallel_sum_expansive_functions::pthread_create");
    for(int i = 0; i < 2; ++i) {
        if (pthread_create(&thread[i], NULL, expansive_function_w, &result[i])) {
            perror("Thread create failed");
            return -1;
        }
    }

    puts("parallel_sum_expansive_functions::pthread_join");
    for(int i = 0; i < 2; ++i) {
        if (pthread_join(thread[i], NULL)) {
            perror("Thread join failed");
            return -2;
        }
    }
    puts("parallel_sum_expansive_functions::pthread_join successful");

    return result[0] + result[1];
}

#include <emscripten/bind.h>
EMSCRIPTEN_BINDINGS(mymodule)
{
    emscripten::function("expansive_function", &expansive_function);
    emscripten::function("parallel_sum_expansive_functions", &parallel_sum_expansive_functions);
}
