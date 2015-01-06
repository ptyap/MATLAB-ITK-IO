/**
 * @file itkread.cpp
 * @brief Matlab mex gateway for reading ITK supported files
 * @author Pew-Thian Yap
 */

#include <memory>
#include "mex.h"
#include "itkReadPipeline.h"

void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
  // input argument check
  if ( nrhs < 1 || nrhs > 1 || !mxIsChar(prhs[0]) )
    mexErrMsgTxt("Incorrect arguments");

  char* filepath = mxArrayToString(prhs[0]);

  const unsigned int Dimension = 4;

  typedef itkReadPipeline<double, Dimension> itkReadPipelineType;

  try
    {
    itkReadPipelineType pipeline(filepath);

    size_t size[Dimension];
    pipeline.GetSize(size);
    mwSize dims[Dimension];

    for (unsigned int d = 0; d < Dimension; d++)
      {
      dims[d] = size[d];
      }

    plhs[0] = mxCreateNumericArray(Dimension, dims, mxDOUBLE_CLASS, mxREAL);
    double* image = static_cast<double*>(mxGetPr(plhs[0]));
    double* out_origin = 0, *out_spacing = 0;
    double origin[Dimension], spacing[Dimension];
    int numdims = 0;

    if (size[Dimension - 1] == 1) // 3D
      {
      numdims = Dimension - 1;
      }
    else
      {
      numdims = Dimension;
      }

    switch(nlhs)
      {
      case 1:
        pipeline.Copy(image);
        break;
      case 2:
        pipeline.Copy(image, origin);

        plhs[1] = mxCreateDoubleMatrix(numdims, 1, mxREAL);
        out_origin = static_cast<double*>(mxGetPr(plhs[1]));

        for (unsigned int d = 0; d < numdims; d++)
          {
          out_origin[d] = origin[d];
          }
        break;
      case 3:
        pipeline.Copy(image, origin, spacing);

        plhs[1] = mxCreateDoubleMatrix(numdims, 1, mxREAL);
        out_origin = static_cast<double*>(mxGetPr(plhs[1]));
        plhs[2] = mxCreateDoubleMatrix(numdims, 1, mxREAL);
        out_spacing = static_cast<double*>(mxGetPr(plhs[2]));

        for (unsigned int d = 0; d < numdims; d++)
          {
          out_origin[d] = origin[d];
          out_spacing[d] = spacing[d];
          }

        break;

      default:
        mexErrMsgTxt("Incorrect output arguments. See 'help @MATLAB_FUNCTION_NAME_ITKREAD@'.");
      }
    }
  catch (std::exception & e)
    {
    mexErrMsgTxt(e.what());
    return;
    }
}


