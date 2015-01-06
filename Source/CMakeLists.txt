SET(MATLAB_EXECUTABLE
  itkRead
  itkWrite
  )

FOREACH(app ${MATLAB_EXECUTABLE})
  add_matlab_executable(${app} ${PROJECT_SOURCE_DIR}/Source/${app}.cxx ${app}Pipeline.h)
ENDFOREACH(app)
