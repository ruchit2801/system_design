cmake_minimum_required(VERSION 3.21)
project(p2)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(/opt/homebrew/Cellar/boost/1.80.0/include/)
include_directories(/opt/homebrew/Cellar/quantlib/1.27.1/include)

add_executable(p2
        include/BSM.h
        include/CSVReader.h
        include/RealDeltaHedging.h
        include/StdNormal.h
        include/StockPriceSimulator.h
        include/Utils.h
        src/BSM.cpp
        src/CSVReader.cpp
        src/main.cpp
        src/RealDeltaHedging.cpp
        src/StdNormal.cpp
        src/StockPriceSimulator.cpp
        src/Utils.cpp)
