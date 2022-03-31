cmake_minimum_required(VERSION 3.20)
project(Archiver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")


add_executable(Archiver Archiver.cpp
        HuffmanTree.cpp
        HuffmanTree.h
        CanonicalForm.cpp
        CanonicalForm.h
        Encoder.cpp
        Encoder.h
        BitWriter.cpp
        BitWriter.h BitReader.cpp BitReader.h Decoder.cpp Decoder.h Archiver.h ParseCommandLine.cpp ParseCommandLine.h PriorityQueue.h)
