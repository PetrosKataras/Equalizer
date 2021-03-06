# Copyright (c) 2010 Daniel Pfeifer <daniel@pfeifer-mail.de>
#               2010-2013 Stefan Eilemann <eile@eyescale.ch>

include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(CPPCHECK_VERSION VERSION_LESS 1.68)
  list(APPEND CPPCHECK_EXTRA_ARGS
    --suppress=invalidscanf:${CMAKE_CURRENT_SOURCE_DIR}/rawVolModel.cpp)
else()
  list(APPEND CPPCHECK_EXTRA_ARGS
    --suppress=invalidscanf_libc:${CMAKE_CURRENT_SOURCE_DIR}/rawVolModel.cpp)
endif()

eq_add_example(eVolve
  HEADERS
    channel.h
    config.h
    eVolve.h
    error.h
    frameData.h
    framesOrderer.h
    glslShaders.h
    hlp.h
    initData.h
    localInitData.h
    node.h
    pipe.h
    rawVolModel.h
    rawVolModelRenderer.h
    sliceClipping.h
    window.h
  SOURCES
    channel.cpp
    config.cpp
    error.cpp
    eVolve.cpp
    frameData.cpp
    framesOrderer.cpp
    glslShaders.cpp
    initData.cpp
    localInitData.cpp
    main.cpp
    node.cpp
    pipe.cpp
    rawVolModel.cpp
    rawVolModelRenderer.cpp
    sliceClipping.cpp
    window.cpp
  SHADERS
    vertexShader.glsl
    fragmentShader.glsl
  )

file(COPY Bucky32x32x32_d.raw Bucky32x32x32_d.raw.vhf
  DESTINATION ${CMAKE_BINARY_DIR}/share/Equalizer/data)
install(FILES Bucky32x32x32_d.raw Bucky32x32x32_d.raw.vhf
  DESTINATION share/Equalizer/data COMPONENT apps)
