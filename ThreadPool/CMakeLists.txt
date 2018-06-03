PROJECT(Threadpool)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CPP_FLAGS "-std=c++0x -Wall")
set(CPP_FLAGS_DEBUG "-g")
set(CPP_FLAGS_RELEASE "-O2")

SET( CMAKE_CXX_FLAGS  ${CPP_FLAGS} )
SET( CMAKE_CXX_FLAGS_RELEASE  ${CPP_FLAGS_RELEASE} )
SET( CMAKE_CXX_FLAGS_DEBUG  ${CPP_FLAGS_DEBUG} )


SET(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include)

SET(CPPFILES ${CMAKE_CURRENT_SOURCE_DIR}/src )

SET(LINKLIBS pthread)

INCLUDE_DIRECTORIES(
  ${HEADERS}
  )


SET(LIBSRCS ${CPPFILES}/Mutex.cpp 
            ${CPPFILES}/Waitsignal.cpp
            ${CPPFILES}/Thread.cpp
            ${CPPFILES}/Threadpool.cpp
   )

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

ADD_LIBRARY(threadpool SHARED ${LIBSRCS})

target_link_libraries(threadpool ${LINKLIBS})

set_target_properties(threadpool PROPERTIES PUBLIC_HEADER 
                     "${HEADERS}/Job.h;${HEADERS}/Threadpool.h;${HEADERS}/Mutex.h;${HEADERS}/Thread.h;${HEADERS}/Waitsignal.h"
                      )

install(TARGETS threadpool DESTINATION /usr/local/lib/threadpool
        PUBLIC_HEADER DESTINATION /usr/local/include/threadpool)


set(VERSION "1.0.0")

set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_GENERATOR "RPM")
set(CPACK_PACKAGE_NAME "libthreadpool")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "Arun Nadesh R(arunnadesh@gmail.com)")
set(CPACK_PACKAGE_VENDOR "Arun Nadesh R(arunnadesh@gmail.com)")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME
"${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
include(CPack)

