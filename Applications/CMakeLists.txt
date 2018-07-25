SET(MATLAB_EXECUTABLE
  itkRead
  itkWrite
  )

FOREACH(app ${MATLAB_EXECUTABLE})
  add_matlab_executable(${app} ${app}.cxx)
ENDFOREACH(app)
