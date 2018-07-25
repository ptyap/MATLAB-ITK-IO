FUNCTION(add_matlab_executable appName mainFile)

  # Setup doc for matlab functions
  SET(MATLAB_FUNCTION_NAME ${appName})
  CONFIGURE_FILE(${appName}.m ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${appName}.m)

  # Setup compilation target
  ADD_LIBRARY(${appName} SHARED ${mainFile} ${ARGN})
  TARGET_LINK_LIBRARIES(${appName} ${ITK_LIBRARIES} ${MATLAB_LIBRARIES})
  IF(MSYS)
    TARGET_LINK_LIBRARIES(${appName} stdc++)
  ENDIF()

  SET_TARGET_PROPERTIES(${appName} PROPERTIES COMPILE_DEFINITIONS MATLAB_MEX_FILE)
  TARGET_COMPILE_DEFINITIONS(${appName} PRIVATE MATLAB_FUNCTION_NAME="${appName}")

  matlab_set_output_filename(${appName})
  matlab_set_compile_flags(${appName})
  matlab_install(${appName})

ENDFUNCTION(add_matlab_executable)


FUNCTION(matlab_install target)

  INSTALL(TARGETS ${target}
    RUNTIME DESTINATION mex
    LIBRARY DESTINATION mex
    ARCHIVE DESTINATION mex)
 
  INSTALL(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.m DESTINATION mex)

ENDFUNCTION(matlab_install)


FUNCTION(matlab_set_output_filename target)

  # Set output name
  SET_TARGET_PROPERTIES(${appName} PROPERTIES
                        LIBRARY_OUTPUT_NAME ${appName}
                        PREFIX "")

  # Determine mex suffix
  IF(UNIX)
    # if this is OSX (which is UNIX) then the library suffixes depend on the architecture
    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
      IF(CMAKE_OSX_ARCHITECTURES MATCHES i386)
        # mac intel 32-bit
        SET_TARGET_PROPERTIES(${target} PROPERTIES SUFFIX ".mexmaci")
      ELSEIF(CMAKE_OSX_ARCHITECTURES MATCHES x86_64)
        # mac intel 64-bit
        SET_TARGET_PROPERTIES(${target} PROPERTIES SUFFIX ".mexmaci64")
      ELSE(CMAKE_OSX_ARCHITECTURES MATCHES i386)
        # Mac Power PC
        SET_TARGET_PROPERTIES(${target} PROPERTIES SUFFIX ".mexmac")
      ENDIF(CMAKE_OSX_ARCHITECTURES MATCHES i386)
    ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
      IF(CMAKE_SIZEOF_VOID_P MATCHES "4")
        SET_TARGET_PROPERTIES(${target} PROPERTIES SUFFIX ".mexglx")
      ELSEIF(CMAKE_SIZEOF_VOID_P MATCHES "8")
        SET_TARGET_PROPERTIES(${target} PROPERTIES SUFFIX ".mexa64")
      ELSE(CMAKE_SIZEOF_VOID_P MATCHES "4")
        MESSAGE(FATAL_ERROR 
          "CMAKE_SIZEOF_VOID_P (${CMAKE_SIZEOF_VOID_P}) doesn't indicate a valid platform")
      ENDIF(CMAKE_SIZEOF_VOID_P MATCHES "4")
    ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  ELSEIF(WIN32)
    IF(CMAKE_SIZEOF_VOID_P MATCHES "4")
      SET_TARGET_PROPERTIES(${target} PROPERTIES SUFFIX ".mexw32")
    ELSEIF(CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET_TARGET_PROPERTIES(${target} PROPERTIES SUFFIX ".mexw64")
    ELSE(CMAKE_SIZEOF_VOID_P MATCHES "4")
      MESSAGE(FATAL_ERROR 
        "CMAKE_SIZEOF_VOID_P (${CMAKE_SIZEOF_VOID_P}) doesn't indicate a valid platform")
    ENDIF(CMAKE_SIZEOF_VOID_P MATCHES "4")
  ENDIF(UNIX)
  
ENDFUNCTION(matlab_set_output_filename)


FUNCTION(matlab_set_compile_flags target)
 
  IF(MSVC)
    append_target_properties(${appName} LINK_FLAGS "/export:mexFunction")
  ENDIF(MSVC)

ENDFUNCTION(matlab_set_compile_flags)


FUNCTION(append_target_properties target prop)

  FOREACH(newPropVal ${ARGN})
    GET_TARGET_PROPERTY(oldPropVals ${target} ${prop})
    IF(oldPropVals)
      IF(NOT "${oldPropVals}" MATCHES "^.*${newPropVal}.*$")
        SET_TARGET_PROPERTIES(${target} PROPERTIES ${prop} "${newPropVal} ${oldPropVals}")
      ENDIF(NOT "${oldPropVals}" MATCHES "^.*${newPropVal}.*$")
    ELSE(oldPropVals)
      SET_TARGET_PROPERTIES(${target} PROPERTIES ${prop} ${newPropVal})
    ENDIF(oldPropVals)
  ENDFOREACH(newPropVal ${ARGN})

ENDFUNCTION(append_target_properties)

