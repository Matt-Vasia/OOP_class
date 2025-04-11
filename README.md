
# OOP

Programos versija, skirta ištestuoti skirtumus tarp CLASS ir STRUCT duomenų struktūrų tipų.

Su VECTOR struktūra naudojamas parallel computing funkcionalumas.

<mark>CLASS duomenų struktūra realizuota TIK VECTOR versijoje<mark>

To run tests, choose which container (LIST, DEQUE, VECTOR) you would like to use by going to one of the folders ("deque", "list", "vector") and run "run.bat".

![Instructions](https://github.com/Matt-Vasia/OOP/blob/v1.0/instructions.gif?raw=true)

![Menu example](https://github.com/Matt-Vasia/OOP/blob/v1.0/menu.png?raw=true)

## Running Tests

Testing equipment:
```
Processor	    AMD Ryzen 7 7735U   8 cores/16 threads at 2.70 GHz
Installed RAM	16,0 GB (15,2 GB usable) LPDDR5
Disk            1TB M.2 NVMe PCIe 4.0 SSD
System type	    Windows 11 64x
```

```
VECTOR test times with CLASS structure (No compile flags)

Santrauka: (1000)
Skaitymas: 0.006 s
Rusiavimas: 0.001 s
Skaidymas: 0 s

Santrauka: (10000)
Skaitymas: 0.058 s
Rusiavimas: 0.0012 s
Skaidymas: 0 s

Santrauka: (100000)
Skaitymas: 0.579 s
Rusiavimas: 0.154 s
Skaidymas: 0 s

Santrauka: (1000000)
Skaitymas: 5.886 s
Rusiavimas: 1.328 s
Skaidymas: 0 s

Santrauka: (10000000)
Skaitymas: 59.7582 s
Rusiavimas: 10.422 s
Skaidymas: 0 s
```
```
VECTOR test times with CLASS structure (Compile flag -O1)

Santrauka: (1000)
Skaitymas: 0.007 s
Rusiavimas: 0.001 s
Skaidymas: 0 s

Santrauka: (10000)
Skaitymas: 0.052 s
Rusiavimas: 0.009 s
Skaidymas: 0 s

Santrauka: (100000)
Skaitymas: 0.604 s
Rusiavimas: 0.152 s
Skaidymas: 0 s

Santrauka: (1000000)
Skaitymas: 5.797 s
Rusiavimas: 1.599 s
Skaidymas: 0 s

Santrauka: (10000000)
Skaitymas: 58.542 s
Rusiavimas: 8.142 s
Skaidymas: 0 s
```
```
VECTOR test times with CLASS structure (Compile flag -O2)

Santrauka: (1000)
Skaitymas: 0.006 s
Rusiavimas: 0.001 s
Skaidymas: 0 s

Santrauka: (10000)
Skaitymas: 0.048 s
Rusiavimas: 0.011 s
Skaidymas: 0 s

Santrauka: (100000)
Skaitymas: 0.604 s
Rusiavimas: 0.152 s
Skaidymas: 0 s

Santrauka: (1000000)
Skaitymas: 5.829 s
Rusiavimas: 1.324 s
Skaidymas: 0 s

Santrauka: (10000000)
Skaitymas: 57.7582 s
Rusiavimas: 10.120 s
Skaidymas: 0 s
```
```
VECTOR test times with CLASS structure (Compile flag -O3)

Santrauka: (1000)
Skaitymas: 0.007 s
Rusiavimas: 0.001 s
Skaidymas: 0 s

Santrauka: (10000)
Skaitymas: 0.048 s
Rusiavimas: 0.008 s
Skaidymas: 0 s

Santrauka: (100000)
Skaitymas: 0.619 s
Rusiavimas: 0.154 s
Skaidymas: 0 s

Santrauka: (1000000)
Skaitymas: 5.916 s
Rusiavimas: 1.381 s
Skaidymas: 0 s

Santrauka: (10000000)
Skaitymas: 55.4582 s
Rusiavimas: 1.120 s
Skaidymas: 0 s
```

