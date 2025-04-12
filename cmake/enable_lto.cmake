cmake_minimum_required(VERSION 3.16)

include(CheckIPOSupported)

# Check for lto support only once and save the value in cache
if (NOT DEFINED var_lto_supported)
    check_ipo_supported(RESULT ipo_supported OUTPUT lto_supported_output)
    SET(var_lto_supported ${ipo_supported} CACHE INTERNAL "var_lto_supported")
    SET(var_lto_supported_output "${lto_supported_output}" CACHE INTERNAL STRING "var_lto_supported_output")
    if (var_lto_supported)
        message(STATUS "LTO is supported")
    else()
        message(WARNING "Could not enable LTO. Debug info here: ${var_lto_supported_output}")
    endif()
endif()

function(enable_lto_globally)
    if (NOT var_lto_supported)
        return()
    endif()

    if(POLICY CMP0069)
        cmake_policy(SET CMP0069 NEW)
        set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
    endif(POLICY CMP0069)

    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endfunction(enable_lto_globally)

function(disable_lto_globally)
    if(POLICY CMP0069)
        cmake_policy(SET CMP0069 NEW)
        set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
    endif(POLICY CMP0069)

    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)
endfunction()

function(enable_lto_for target_name)
    if (var_lto_supported)
        set_property(TARGET ${target_name} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
endfunction()
