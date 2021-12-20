cmake_minimum_required(VERSION 3.20)
project(DorHadar)

set(CMAKE_CXX_STANDARD 11)

add_executable(DorHadar MainTrain.cpp anomaly_detection_util.h anomaly_detection_util.cpp AnomalyDetector.h
        SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h timeseries.cpp timeseries.h HybridAnomalyDetector.h
        HybridAnomalyDetector.cpp minCircle.cpp minCircle.h)

