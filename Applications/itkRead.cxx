/**
 * @file itkread.cpp
 * @brief Matlab mex gateway for reading ITK supported files
 * @author Pew-Thian Yap <ptyap@med.unc.edu>
 */

#include <memory>
#include "mex.h"
#include "itkReadPipeline.h"

void mexFunction(int nlhs, mxArray *plhs[],
    int nrhs, const mxArray *prhs[])
{
  // Check arguments
  if ( nrhs < 1 || nrhs > 1 || !mxIsChar(prhs[0]) )
    mexErrMsgTxt(( std::string("Incorrect input arguments. See 'help ") + std::string(MATLAB_FUNCTION_NAME) + std::string("'.")).c_str());

  if ( nlhs < 1 || nlhs > 2 )
    mexErrMsgTxt(( std::string("Incorrect output arguments. See 'help ") + std::string(MATLAB_FUNCTION_NAME) + std::string("'.")).c_str());

  char* filepath = mxArrayToString(prhs[0]);

  typedef itkReadPipeline< double > itkReadPipelineType;

  try
  {
    itkReadPipelineType pipeline(filepath);

    size_t                        ndims = pipeline.GetNumberOfDimensions();
    size_t                        ncomponents = pipeline.GetNumberOfComponents();
    itkReadPipelineType::SizeType size = pipeline.GetSize();

    if ( ncomponents == 1 )
    {
      mwSize* dims = static_cast< mwSize* >( mxMalloc(sizeof( mwSize ) * ndims) );
      for ( size_t d = 0; d < ndims; d++ )
      {
        dims[d] = size[d];
      }
      plhs[0] = mxCreateNumericArray(ndims, dims, mxDOUBLE_CLASS, mxREAL);
      mxFree(dims);
    }
    else
    {
      mwSize* dims = static_cast< mwSize* >( mxMalloc(sizeof( mwSize ) * ( ndims + 1 )) );
      dims[0] = ncomponents;
      for ( size_t d = 0; d < ndims; d++ )
      {
        dims[d+1] = size[d];
      }
      plhs[0] = mxCreateNumericArray(ndims+1, dims, mxDOUBLE_CLASS, mxREAL);
      mxFree(dims);
    }

    double* image = static_cast< double* >( mxGetPr(plhs[0]) );

    itkReadPipelineType::ImageInfo info;

    switch( nlhs )
    {
      case 1:
        pipeline.Copy(image, info);
        break;

      case 2:
      {
        pipeline.Copy(image, info);

        const char * fieldnames[] = { "ndimensions", "dimensions", "ncomponents", "spacing", "origin", "index", "direction", "component" };
        enum { NDIMS = 0, DIMENSIONS, NCOMPS, SPACING, ORIGIN, INDEX, DIRECTION, COMPONENT };

        mxArray* mx_ndimensions = mxCreateDoubleMatrix(1, 1, mxREAL);
        double*  out_ndimensions = static_cast< double* >( mxGetPr(mx_ndimensions) );

        mxArray* mx_dimensions = mxCreateDoubleMatrix(1, ndims, mxREAL);
        double*  out_dimensions = static_cast< double* >( mxGetPr(mx_dimensions) );

        mxArray* mx_ncomponents = mxCreateDoubleMatrix(1, 1, mxREAL);
        double*  out_ncomponents = static_cast< double* >( mxGetPr(mx_ncomponents) );

        mxArray* mx_spacing = mxCreateDoubleMatrix(1, ndims, mxREAL);
        double*  out_spacing = static_cast< double* >( mxGetPr(mx_spacing) );

        mxArray* mx_origin = mxCreateDoubleMatrix(1, ndims, mxREAL);
        double*  out_origin = static_cast< double* >( mxGetPr(mx_origin) );

        mxArray* mx_index = mxCreateDoubleMatrix(1, ndims, mxREAL);
        double*  out_index = static_cast< double* >( mxGetPr(mx_index) );

        mxArray* mx_direction = mxCreateDoubleMatrix(ndims, ndims, mxREAL);
        double*  out_direction = static_cast< double* >( mxGetPr(mx_direction) );

        out_ndimensions[0] = ndims;
        out_ncomponents[0] = ncomponents;

        for ( size_t d = 0; d < ndims; d++ )
        {
          out_dimensions[d] = info.dimensions[d];
          out_spacing[d] = info.spacing[d];
          out_origin[d] = info.origin[d];

          for ( size_t dd = 0; dd < ndims; dd++ )
          {
            out_direction[dd + d * ndims] = info.direction[d][dd];
          }
        }

        plhs[1] = mxCreateStructMatrix(1,1,8,fieldnames);
        mxSetFieldByNumber(plhs[1], 0, NDIMS, mx_ndimensions);
        mxSetFieldByNumber(plhs[1], 0, DIMENSIONS, mx_dimensions);
        mxSetFieldByNumber(plhs[1], 0, NCOMPS, mx_ncomponents);
        mxSetFieldByNumber(plhs[1], 0, SPACING, mx_spacing);
        mxSetFieldByNumber(plhs[1], 0, ORIGIN, mx_origin);
        mxSetFieldByNumber(plhs[1], 0, INDEX, mx_index);
        mxSetFieldByNumber(plhs[1], 0, DIRECTION, mx_direction);
        mxSetFieldByNumber(plhs[1], 0, COMPONENT, mxCreateString(info.component.c_str()));

        break;
      }

      default:
        break;
    }

  }
  catch ( std::exception & e )
  {
    mexErrMsgTxt(e.what());
    return;
  }
}


