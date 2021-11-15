cmake_minimum_required(VERSION 3.20)
project(DorHadar)

set(CMAKE_CXX_STANDARD 11)

add_executable(DorHadar MainTrain.cpp anomaly_detection_util.cpp anomaly_detection_util.h AnomalyDetector.h SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h timeseries.cpp timeseries.h)

