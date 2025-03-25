
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
VECTOR test times with CLASS structure (using average values)

Santrauka: (1000)
Skaitymas: 0.006 s
Rusiavimas: 0.001 s
Skaidymas: 0 s

Santrauka: (10000)
Skaitymas: 0.03 s
Rusiavimas: 0.004 s
Skaidymas: 0 s

Santrauka: (100000)
Skaitymas: 0.324 s
Rusiavimas: 0.048 s
Skaidymas: 0 s

Santrauka: (1000000)
Skaitymas: 3.176 s
Rusiavimas: 0.526 s
Skaidymas: 0 s

Santrauka: (10000000)
Skaitymas: 32.382 s
Rusiavimas: 8.519 s
Skaidymas: 0 s
```

VECTOR test times with STRUCT structure (using average values)

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