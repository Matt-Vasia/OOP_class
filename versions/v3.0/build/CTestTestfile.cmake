# CMake generated Testfile for 
# Source directory: C:/Users/matas/Desktop/VS coding/OOP (c++)/OOP/versions/v3.0
# Build directory: C:/Users/matas/Desktop/VS coding/OOP (c++)/OOP/versions/v3.0/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[StudentaiTests]=] "studentai_tests")
  set_tests_properties([=[StudentaiTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/matas/Desktop/VS coding/OOP (c++)/OOP/versions/v3.0/CMakeLists.txt;55;add_test;C:/Users/matas/Desktop/VS coding/OOP (c++)/OOP/versions/v3.0/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[StudentaiTests]=] "studentai_tests")
  set_tests_properties([=[StudentaiTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/matas/Desktop/VS coding/OOP (c++)/OOP/versions/v3.0/CMakeLists.txt;55;add_test;C:/Users/matas/Desktop/VS coding/OOP (c++)/OOP/versions/v3.0/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[StudentaiTests]=] "studentai_tests")
  set_tests_properties([=[StudentaiTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/matas/Desktop/VS coding/OOP (c++)/OOP/versions/v3.0/CMakeLists.txt;55;add_test;C:/Users/matas/Desktop/VS coding/OOP (c++)/OOP/versions/v3.0/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[StudentaiTests]=] "studentai_tests")
  set_tests_properties([=[StudentaiTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/matas/Desktop/VS coding/OOP (c++)/OOP/versions/v3.0/CMakeLists.txt;55;add_test;C:/Users/matas/Desktop/VS coding/OOP (c++)/OOP/versions/v3.0/CMakeLists.txt;0;")
else()
  add_test([=[StudentaiTests]=] NOT_AVAILABLE)
endif()
subdirs("_deps/googletest-build")
