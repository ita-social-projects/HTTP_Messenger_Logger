CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

PROJECT(Logger)

ADD_DEFINITIONS(-DLOGGER_LIBRARY)

INCLUDE_DIRECTORIES(BEFORE include)

SET(sources
  src/Logger.cpp
  src/Log.cpp
)

SET(includes
  include/Logger.h
  include/Log.h
)

SET(library_target Logger)

# ${library_target}

ADD_LIBRARY("Logger" STATIC ${sources} ${includes})

TARGET_INCLUDE_DIRECTORIES(${library_target} PUBLIC include)

INSTALL(TARGETS ${library_target} DESTINATION lib)

