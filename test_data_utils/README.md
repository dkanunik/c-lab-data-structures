## Test Data Utils 

Plain handmade utils for test data generating (_in progress..._)

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
target_link_libraries(${PROJECT_NAME} PUBLIC ${TEST_DATA_UTILS})
```
