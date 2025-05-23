cmake_minimum_required(VERSION 3.16)

function(set_generic_compiler_options target_name access)
    get_property(languages GLOBAL PROPERTY ENABLED_LANGUAGES)

    if(MSVC)
        set(cpp_compile_opts
            /MP
            /W4
            /permissive- # Enforces standards conformance.
            /w14242 # 'identfier': conversion from 'type1' to 'type1', possible loss of data
            /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
            /w14263 # 'function': member function does not override any base class virtual member function
            /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
            /w14287 # 'operator': unsigned/negative constant mismatch
            /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside the for-loop scope
            /w14296 # 'operator': expression is always 'boolean_value'
            /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
            /w14545 # expression before comma evaluates to a function which is missing an argument list
            /w14546 # function call before comma missing argument list
            /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
            /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
            /w14555 # expression has no effect; expected expression with side-effect
            /w14619 # pragma warning: there is no warning number 'number'
            /w14640 # Enable warning on thread un-safe static member initialization
            /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected runtime behavior.
            /w14905 # wide string literal cast to 'LPSTR'
            /w14906 # string literal cast to 'LPWSTR'
            /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
        )

    else()
        # command warnings for clang and gcc
        set(cpp_compile_opts
            -Werror # treat warnings as errors
            -pedantic # Warn on language extensions
            -Wall -Wextra # reasonable and standard
            -Wpedantic # (all versions of GCC, Clang >= 3.2) warn if non-standard C++ is used
            -Wshadow # warn the user if a variable declaration shadows one from a parent context
            -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
            -Wold-style-cast # warn for c-style casts
            -Wcast-align # warn for potential performance problem casts
            -Wunused # warn on anything being unused
            -Woverloaded-virtual # warn if you overload (not override) a virtual function
            -Wconversion # warn on type conversions that may lose data
            -Wnull-dereference # (only in GCC >= 6.0) warn if a null dereference is detected
            -Wdouble-promotion # (GCC >= 4.6, Clang >= 3.8) warn if float is implicit promoted to double
            -Wfloat-equal
            -Wcast-qual
            -Wzero-as-null-pointer-constant
            -Wsign-conversion # (Clang all versions, GCC >= 4.3) warn on sign conversions
            -Wformat=2 # warn on security issues around functions that format output (ie printf)
            -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
        )

        if(CMAKE_CXX_COMPILER_ID STREQUAL "GCC")
            list(APPEND cpp_compile_opts
                -Wduplicated-cond # warn if if / else chain has duplicated conditions
                -Wduplicated-branches # warn if if / else branches have duplicated code
                -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
                -Wstrict-null-sentinel
                -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
                -Wuseless-cast # warn if you perform a cast to the same type
                -Wsuggest-override # warn if an overridden member function is not marked 'override' or 'final'
            )
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            # only special branch of Clang currently but it is really helpful
            # list(APPEND cpp_compile_opts
            # -Wlifetime # shows object lifetime issues
            # )
        endif()
    endif()

    if("CXX" IN_LIST languages)
        # Enable these options for C++ exclusively. The project may contain also cuda files so these will not interfere
        target_compile_options(${target_name} ${access} $<$<COMPILE_LANGUAGE:CXX>:${cpp_compile_opts}>)
    endif()

    if ("CUDA" IN_LIST languages)
        set(cuda_compile_opts
            --Werror cross-execution-space-call
            --expt-relaxed-constexpr
        )
        target_compile_options(${target_name} ${access} $<$<COMPILE_LANGUAGE:CUDA>:${cuda_compile_opts}>)
    endif()

endfunction()
