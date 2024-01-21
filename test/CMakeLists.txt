# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(KeyDetectionTests LANGUAGES CXX)

# ---- Tests ----

add_executable(KeyDetection_test source/KeyDetection_test.cpp)
target_link_libraries(KeyDetection_test PRIVATE KeyDetection_lib)
target_compile_features(KeyDetection_test PRIVATE cxx_std_17)

add_test(NAME KeyDetection_test COMMAND KeyDetection_test)

# ---- End-of-file commands ----

add_folders(Test)
