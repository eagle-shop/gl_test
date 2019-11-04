`git clone https://github.com/eagle-shop/gl_test`  
`cd gl_test`  
`git submodule update --init --recursive`  
`mkdir build`  
`cd build`  

`cmake ..`  
`cmake --build .`  
or (for macOS)  
`cmake .. -G Xcode`  
or (for windows mingw)  
`cmake .. -G "Unix Makefiles"`  

Note  
It seems that mingw needs to be installed in a path without spaces.
