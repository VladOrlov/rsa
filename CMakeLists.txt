cmake_minimum_required(VERSION 3.13)
project(rsa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(rsa
        RsaKey.h
        exceptions.h
        BigInteger.cpp
        BigInteger.h
        main.cpp
        Rsa.cpp
        Rsa.h)
