cmake_minimum_required(VERSION 2.8)

ADD_EXECUTABLE(final main.c http_parser.c)

target_link_libraries(final ev pthread)
