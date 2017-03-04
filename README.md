# OpenMP Examples

## OSX notes
install gcc using brew
```
brew reinstall gcc
```
```
alias gcc'=gcc-6'
```


## Hello World
```
mkdir -p target
gcc -fopenmp -o target/hello hello.c ; target/hello
```

## PI
```
mkdir -p target
gcc -fopenmp -o target/pi pi.c ; target/pi 4000000000 32
```
