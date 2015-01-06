/**
 * @file itkwrite.cpp
 * @brief Matlab mex gateway for writing ITK supported files
 * @author Pew-Thian Yap
 */

#include <memory>
#include "mex.h"
#include "itkWritePipeline.h"

void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
  // input argument check
  if ( nrhs < 2 || nrhs > 4 || !mxIsChar(prhs[0]) )
    mexErrMsgTxt("Incorrect arguments");

  char* filepath = mxArrayToString(prhs[0]);

  const unsigned int Dimension = 4;

  typedef itkWritePipeline<double, Dimension> itkWritePipelineType;

  try
    {
    itkWritePipelineType pipeline(filepath);

    const mwSize *dims = mxGetDimensions(prhs[1]);
    mwSize numdims = mxGetNumberOfDimensions(prhs[1]);
    double* image = static_cast<double*>(mxGetPr(prhs[1]));

    double* origin = 0;
    double* spacing = 0;

    size_t out_size[Dimension];
    double out_origin[Dimension];
    double out_spacing[Dimension];

    if ( nrhs > 2 )
      {
      origin = static_cast<double*>(mxGetPr(prhs[2]));
      }

    if ( nrhs > 3 )
      {
      spacing = static_cast<double*>(mxGetPr(prhs[3]));
      }

    for (unsigned int d = 0; d < numdims; d++)
      {
      out_size[d] = dims[d];
      if ( nrhs > 2 )
        {
        out_origin[d] = origin[d];
        }
      else
        {
        out_origin[d] = 0.0;
        }

      if ( nrhs > 3 )
        {
        out_spacing[d] = spacing[d];
        }
      else
        {
        out_spacing[d] = 1.0;
        }
      }

    for (unsigned int d = numdims; d < Dimension; d++)
      {
      out_size[d] = 1;
      out_spacing[d] = 1.0;
      out_origin[d] = 0.0;
      }

    pipeline.Save(image, out_size, out_origin, out_spacing);
    }
  catch (std::exception & e)
    {
    mexErrMsgTxt(e.what());
    return;
    }
}

