# triforce

Find out if you can triforce!

# Screenshots 

![Screenshot_20210411_221625](https://user-images.githubusercontent.com/59165467/114318032-b3e8e280-9b13-11eb-9d2b-8ada92dfa333.png)
![Screenshot_20210411_221636](https://user-images.githubusercontent.com/59165467/114318035-bb0ff080-9b13-11eb-9fa2-47902ffc506a.png)


# Dependencies

- CMake >= 3.17
- gcc 10.2.0
- gcc-libs 10.2.0
- X11 - libx11 1.7.0
- OpenGL 3.3 - mesa 21.0.1
- glew 2.2.0

# Build

```
git clone https://github.com/perst20/triforce
cd triforce && mkdir build && cd build
cmake ..
cmake --build .
./triforce
```

Tested on Manjaro Linux 21.0.1
