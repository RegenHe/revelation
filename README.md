# revelation

## Usage: 
1. Pull Code
```
git clone https://github.com/RegenHe/revelation.git
git submodule add https://github.com/ithewei/libhv.git dep/libhv
```
2. Compile and Run
```
mkdir build
cd build
cmake ..
make

cd ../html html
./revelation 8080 0.0.0.0
```