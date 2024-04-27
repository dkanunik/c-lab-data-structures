## Test Data Utils 

Plain handmade utils for test data generating (_in progress..._)

### API:

- generate a file with arbitrary numbers
- return an array of numbers from generated file
- verify the sorting of an array of numbers by ascending (_in progress..._)

### Installation:

```shell
$ make
$ make install
```
### Targets:
```
libtest_data_utils.so -> /usr/local/lib 
test_data_utils.h -> /usr/local/include 
```
### Usage:

```cmake
set(test_data_utils_LIBRARY_DIR /usr/local/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC test_data_utils)
```
