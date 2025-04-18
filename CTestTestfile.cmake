# CMake generated Testfile for 
# Source directory: /home/jaichauhan/Documents/Hazelnet
# Build directory: /home/jaichauhan/Documents/Hazelnet
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_hzl_client_desktop "/home/jaichauhan/Documents/Hazelnet/test_hzl_client_desktop")
set_tests_properties(test_hzl_client_desktop PROPERTIES  _BACKTRACE_TRIPLES "/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;418;add_test;/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;0;")
add_test(test_hzl_client_desktop_shared "/home/jaichauhan/Documents/Hazelnet/test_hzl_client_desktop_shared")
set_tests_properties(test_hzl_client_desktop_shared PROPERTIES  _BACKTRACE_TRIPLES "/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;420;add_test;/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;0;")
add_test(test_hzl_server_desktop "/home/jaichauhan/Documents/Hazelnet/test_hzl_server_desktop")
set_tests_properties(test_hzl_server_desktop PROPERTIES  _BACKTRACE_TRIPLES "/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;499;add_test;/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;0;")
add_test(test_hzl_server_desktop_shared "/home/jaichauhan/Documents/Hazelnet/test_hzl_server_desktop_shared")
set_tests_properties(test_hzl_server_desktop_shared PROPERTIES  _BACKTRACE_TRIPLES "/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;501;add_test;/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;0;")
add_test(test_hzl_interop_desktop "/home/jaichauhan/Documents/Hazelnet/test_hzl_interop_desktop")
set_tests_properties(test_hzl_interop_desktop PROPERTIES  _BACKTRACE_TRIPLES "/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;557;add_test;/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;0;")
add_test(test_hzl_interop_desktop_shared "/home/jaichauhan/Documents/Hazelnet/test_hzl_interop_desktop_shared")
set_tests_properties(test_hzl_interop_desktop_shared PROPERTIES  _BACKTRACE_TRIPLES "/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;559;add_test;/home/jaichauhan/Documents/Hazelnet/CMakeLists.txt;0;")
subdirs("external/libascon")
