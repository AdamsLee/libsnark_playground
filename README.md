# libsnark_playground
*By Adams Lee*

This is a tutorial intended to cover the very basics of the [libsnark](https://github.com/scipr-lab/libsnark) software library for creating zk-SNARKs. We will demonstrate how to formulate zk-SNARK circuits, create proofs and verify the proofs. 

# Building & running tests

The repo is set up according to the [tutorial by Howard Wu](https://github.com/howardwu/libsnark-tutorial). See that tutorial for more info about how to configure the CMake files etc. We will here just cover the basics.

To install the dependencies:

On Ubuntu 16.04 LTS:

```
sudo apt-get install build-essential cmake git libgmp3-dev libprocps4-dev python-markdown libboost-all-dev libssl-dev
```

On Ubuntu 14.04 LTS:

```
sudo apt-get install build-essential cmake git libgmp3-dev libprocps3-dev python-markdown libboost-all-dev libssl-dev
```
In order to download and build the repo:

```
git clone https://github.com/AdamsLee/libsnark-playground.git
cd libsnark-playground
git submodule update --init --recursive
mkdir build && cd build && cmake ..
make
```

To run the tests go to the `build/src` directory and run:

```
./src/range-setup
./src/range-prove 23
./src/range-verify
```
This test simulates the prover to prove he has a secret value which is less than 188;
range-setup (run by prover) simulates to generate the proving key and verification key which will be exported to local files "range_pk.raw" and "range_vk.raw";
range-prove (run by prover) simulates to load the proving key from local file and generate the proof which will be exported to local file "range_proof.raw". A secret integer (less than 188) should be passed to it when running;
range-verify (run by verifier) simulates to load the verification key from local file and verify.