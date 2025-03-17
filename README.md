
# OOP

Programos versija, skirta ištestuoti skirtumus tarp skirtingų duomenų struktūrų tipų. (LIST, DEQUE, VECTOR)

Su DEQUE ir VECTOR struktūromis buvo naudojamas parallel computing funkcionalumas.


## Running Tests

Testing equipment:
```
Processor	    AMD Ryzen 7 7735U   8 cores/16 threads at 2.70 GHz
Installed RAM	16,0 GB (15,2 GB usable) LPDDR5
Disk            1TB M.2 NVMe PCIe 4.0 SSD
System type	    Windows 11 64x

```

To run tests, choose which container (LIST, DEQUE, VECTOR) you would like to use by going to one of the folders ("deque", "list", "vector") and enter the following commands:

```
mkdir build
cd build
cmake ..
cmake --build .
cd Debug
clear
./program
```

To launch the app again, go to build/Debug and launch program.exe

```
VECTOR test times (using average values)

Santrauka: (1000)
Skaitymas: 0.016 s
Rusiavimas: 0.001 s
Skaidymas: 0 s

Santrauka: (10000)
Skaitymas: 0.144 s
Rusiavimas: 0.012 s
Skaidymas: 0 s

Santrauka: (100000)
Skaitymas: 1.246 s
Rusiavimas: 0.147 s
Skaidymas: 0.002 s

Santrauka: (1000000)
Skaitymas: 12.143 s
Rusiavimas: 2.3 s
Skaidymas: 0.07 s

Santrauka: (10000000)
Skaitymas: 125.888 s
Rusiavimas: 29.741 s
Skaidymas: 0.74 s
```

```
LIST test times (using average values)

Santrauka: (1000)
Skaitymas: 0.016 s
Rusiavimas: 0.003 s
Skaidymas: 0 s

Santrauka: (10000)
Skaitymas: 0.15 s
Rusiavimas: 0.043 s
Skaidymas: 0.001 s

Santrauka: (100000)
Skaitymas: 1.271 s
Rusiavimas: 0.563 s
Skaidymas: 0.034 s

Santrauka: (1000000)
Skaitymas: 12.827 s
Rusiavimas: 8.536 s
Skaidymas: 0.431 s

Santrauka: (10000000)
Skaitymas: 131.641 s
Rusiavimas: 121.717 s
Skaidymas: 5.079 s
```

```
DEQUE test times (using average values)

Santrauka: (1000)
Skaitymas: 0.016 s
Rusiavimas: 0.001 s
Skaidymas: 0 s

Santrauka: (10000)
Skaitymas: 0.145 s
Rusiavimas: 0.013 s
Skaidymas: 0 s

Santrauka: (100000)
Skaitymas: 1.246 s
Rusiavimas: 0.169 s
Skaidymas: 0.004 s

Santrauka: (1000000)
Skaitymas: 12.44 s
Rusiavimas: 2.538 s
Skaidymas: 0.104 s

Santrauka: (10000000)
Skaitymas: 125.831 s
Rusiavimas: 34.058 s
Skaidymas: 1.265 s
```