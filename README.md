
# OOP

Programos versija, skirta ištestuoti skirtumus tarp skirtingų duomenų struktūrų tipų. (LIST, DEQUE, VECTOR)

Su DEQUE ir VECTOR struktūromis buvo naudojamas parallel computing funkcionalumas.

To run tests, choose which container (LIST, DEQUE, VECTOR) you would like to use by going to one of the folders ("deque", "list", "vector") and run "run.bat".

## Running Tests

Testing equipment:
```
Processor	    AMD Ryzen 7 7735U   8 cores/16 threads at 2.70 GHz
Installed RAM	16,0 GB (15,2 GB usable) LPDDR5
Disk            1TB M.2 NVMe PCIe 4.0 SSD
System type	    Windows 11 64x
```

```
VECTOR test times (using average values)

Santrauka: (1000)
Skaitymas: 0.024 s
Rusiavimas: 0.001 s
Skaidymas: 0 s

Santrauka: (10000)
Skaitymas: 0.085 s
Rusiavimas: 0.006 s
Skaidymas: 0 s

Santrauka: (100000)
Skaitymas: 0.509 s
Rusiavimas: 0.102 s
Skaidymas: 0.009 s

Santrauka: (1000000)
Skaitymas: 3.913 s
Rusiavimas: 0.88 s
Skaidymas: 0.196 s

Santrauka: (10000000)
Skaitymas: 30.363 s
Rusiavimas: 7.862 s
Skaidymas: 1.662 s
```

```
LIST test times (using average values)

Santrauka: (1000)
Skaitymas: 0.005 s
Rusiavimas: 0.004 s
Skaidymas: 0 s

Santrauka: (10000)
Skaitymas: 0.053 s
Rusiavimas: 0.077 s
Skaidymas: 0.003 s

Santrauka: (100000)
Skaitymas: 0.545 s
Rusiavimas: 1.346 s
Skaidymas: 0.102 s

Santrauka: (1000000)
Skaitymas: 4.346 s
Rusiavimas: 12.331 s
Skaidymas: 0.718 s

Santrauka: (10000000)
Skaitymas: 32.58 s
Rusiavimas: 152.558 s
Skaidymas: 7.395 s
```

```
DEQUE test times (using average values)

Santrauka: (1000)
Skaitymas: 0.006 s
Rusiavimas: 0.001 s
Skaidymas: 0 s

Santrauka: (10000)
Skaitymas: 0.054 s
Rusiavimas: 0.007 s
Skaidymas: 0.001 s

Santrauka: (100000)
Skaitymas: 0.485 s
Rusiavimas: 0.119 s
Skaidymas: 0.021 s

Santrauka: (1000000)
Skaitymas: 3.631 s
Rusiavimas: 1.275 s
Skaidymas: 0.193 s

Santrauka: (10000000)
Skaitymas: 30.93 s
Rusiavimas: 10.29 s
Skaidymas: 2.631 s
```
