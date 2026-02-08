import subprocess
import os

ranges = [
    (1, 500000),
    (1, 1000000),
    (1, 2000000)
]

n_values = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]

if os.path.exists("time.txt"):
    os.remove("time.txt")

print("Testing...\n")

for start,end in ranges:
    print(f"Testing with range {start} to {end}...")
    
    for n in n_values:
        print(f"Testing with n = {n}")
        
        subprocess.run(["./primes", str(start), str(end), str(n)])

print("\nTesting completed. Results saved in time.txt")