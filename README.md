This repository contains benchmarks of modular multiplication and modular squaring with the following 3 prime numbers:

* 2<sup>255</sup>-19
* 2<sup>254</sup> + 45560315531419706090280762371685220353
* 6212163 * 2<sup>232</sup> + 1

These primes are used by the Ed25519, Pallas and Vega elliptic curves, respectively.

The benchmark requires Intel Broadwell or newer CPU (or AMD Zen or newer).

## Build & run

```
git clone https://github.com/tevador/ec-bench.git
cd ec-bench
mkdir build
cd build
cmake ..
make
```
```
./ec-bench
```
