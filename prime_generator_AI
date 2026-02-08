#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

// Optimized prime check: skips even numbers and uses O(sqrt(n)) complexity
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Function executed by each child process
void run_child_process(int id, int start, int end) {
    char filename[32];
    sprintf(filename, "temp_prime_%d.txt", id);

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Failed to open temp file");
        exit(1);
    }

    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            fprintf(fp, "%d\n", i);
        }
    }

    fclose(fp);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <start> <end> <num_processes>\n", argv[0]);
        return 1;
    }

    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    int n_procs = atoi(argv[3]);

    // Validate inputs
    if (start > end || n_procs <= 0) {
        fprintf(stderr, "Invalid range or process count.\n");
        return 1;
    }

    struct timespec t_start, t_end;
    clock_gettime(CLOCK_MONOTONIC, &t_start);

    // 1. Distribute work and Fork
    int range = end - start + 1;
    int chunk_size = range / n_procs;
    int remainder = range % n_procs;
    int current_start = start;

    for (int i = 0; i < n_procs; i++) {
        // Distribute remainder evenly among the first few processes
        int current_chunk = chunk_size + (i < remainder ? 1 : 0);
        int current_end = current_start + current_chunk - 1;

        pid_t pid = fork();
        
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process
            if (current_start <= end) {
                run_child_process(i, current_start, current_end);
            } else {
                exit(0); // Handle case where processes > range
            }
        }

        current_start += current_chunk;
    }

    // 2. Wait for all children
    for (int i = 0; i < n_procs; i++) {
        wait(NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &t_end);

    // 3. Merge results and clean up temp files
    FILE *final_out = fopen("prime.txt", "w");
    if (!final_out) {
        perror("Failed to open output file");
        return 1;
    }

    for (int i = 0; i < n_procs; i++) {
        char filename[32];
        sprintf(filename, "temp_prime_%d.txt", i);

        FILE *temp_in = fopen(filename, "r");
        if (temp_in) {
            int num;
            while (fscanf(temp_in, "%d", &num) != EOF) {
                fprintf(final_out, "%d\n", num);
            }
            fclose(temp_in);
            remove(filename); // CLEANUP: Delete the temporary file
        }
    }
    fclose(final_out);

    // 4. Calculate and print time to console
    double time_taken = (t_end.tv_sec - t_start.tv_sec) + 
                        (t_end.tv_nsec - t_start.tv_nsec) / 1e9;
    
    printf("Done. Found primes in range [%d, %d] using %d processes.\n", start, end, n_procs);
    printf("Execution Time: %.6f seconds\n", time_taken);
    printf("Output saved to: prime.txt\n");

    return 0;
}
