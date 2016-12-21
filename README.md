# Cache Line Speed: Row vs Col memory access

Sum array of 1,073,741,824 elements = 576,460,751,766,552,576.

Sum 1+2+3+...+n = n*(n+1)/2
Sum of 0+1+2+...+n-1 = (n-1)*n/2 

|i +=|Bytes|Op/s   |Time     |
|---:|----:|------:|--------:|
|   1|    4|  1 G/s|00:00:00s|
|   2|    8|  1 G/s|00:00:00s|
|   4|   16|733 M/s|00:00:01s|
|   8|   32|388 M/s|00:00:02s|
|  16|   64|213 M/s|00:00:04s|
|  32|  128|141 M/s|00:00:07s|
|  64|  256|116 M/s|00:00:08s|
| 128|  512|115 M/s|00:00:08s|
| 256|1,024|115 M/s|00:00:08s|
| 512|2,048|100 M/s|00:00:10s|
|1024|4,096| 66 M/s|00:00:15s|

Notes:

* `+=` Stride element delta access
* `Bytes` Stride delta in bytes

# Tests

Running `tests` which does `bin/col #`

```
Stride: [1] @ 4 bytes
Len: 1,073,741,824
int: 4
Mem: 4,294,967,296
Sum= 576,460,751,766,552,576  pass
1 G cells/s 1 seconds = 00:00:00

Stride: [2] @ 8 bytes
Len: 1,073,741,824
int: 4
Mem: 4,294,967,296
Sum= 576,460,751,766,552,576  pass
1 G cells/s 1 seconds = 00:00:00

Stride: [4] @ 16 bytes
Len: 1,073,741,824
int: 4
Mem: 4,294,967,296
Sum= 576,460,751,766,552,576  pass
733 M cells/s 1 seconds = 00:00:01

Stride: [8] @ 32 bytes
Len: 1,073,741,824
int: 4
Mem: 4,294,967,296
Sum= 576,460,751,766,552,576  pass
388 M cells/s 3 seconds = 00:00:02

Stride: [16] @ 64 bytes
Len: 1,073,741,824
int: 4
Mem: 4,294,967,296
Sum= 576,460,751,766,552,576  pass
213 M cells/s 5 seconds = 00:00:04

Stride: [32] @ 128 bytes
Len: 1,073,741,824
int: 4
Mem: 4,294,967,296
Sum= 576,460,751,766,552,576  pass
141 M cells/s 7 seconds = 00:00:07

Stride: [64] @ 256 bytes
Len: 1,073,741,824
int: 4
Mem: 4,294,967,296
Sum= 576,460,751,766,552,576  pass
116 M cells/s 9 seconds = 00:00:08

Stride: [128] @ 512 bytes
Len: 1,073,741,824
int: 4
Mem: 4,294,967,296
Sum= 576,460,751,766,552,576  pass
115 M cells/s 9 seconds = 00:00:08

Stride: [256] @ 1024 bytes
Len: 1,073,741,824
int: 4
Mem: 4,294,967,296
Sum= 576,460,751,766,552,576  pass
115 M cells/s 9 seconds = 00:00:08

Stride: [512] @ 2048 bytes
Len: 1,073,741,824
int: 4
Mem: 4,294,967,296
Sum= 576,460,751,766,552,576  pass
100 M cells/s 10 seconds = 00:00:10

Stride: [1024] @ 4096 bytes
Len: 1,073,741,824
int: 4
Mem: 4,294,967,296
Sum= 576,460,751,766,552,576  pass
66 M cells/s 16 seconds = 00:00:15
```
