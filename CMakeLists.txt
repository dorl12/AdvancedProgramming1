cmake_minimum_required(VERSION 3.20)
project(DorHadar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(DorHadar MainTrain.cpp anomaly_detection_util.h anomaly_detection_util.cpp AnomalyDetector.h
        SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h timeseries.cpp timeseries.h HybridAnomalyDetector.h
        HybridAnomalyDetector.cpp minCircle.cpp minCircle.h commands.h CLI.cpp CLI.h Server.cpp Server.h)