/**
 * @file itkwrite.cpp
 * @brief Matlab mex gateway for writing ITK supported files
 * @author Pew-Thian Yap
 */

#include <memory>
#include "mex.h"
#include "matrix.h"
#include "itkWritePipeline.h"

void mexFunction(int nlhs, mxArray *plhs[],
    int nrhs, const mxArray *prhs[])
{
  // Check arguments
  if ( nrhs < 2 || nrhs > 3
       || !mxIsChar(prhs[0]) || !mxIsNumeric(prhs[1])
       || ( nrhs > 2 && !mxIsClass(prhs[2], "struct") ) )
    mexErrMsgTxt(( std::string("Incorrect input arguments. See 'help ") + std::string(MATLAB_FUNCTION_NAME) + std::string("'.")).c_str());

  if ( nlhs > 0 )
    mexErrMsgTxt(( std::string("Incorrect output arguments. See 'help ") + std::string(MATLAB_FUNCTION_NAME) + std::string("'.")).c_str());

  char* filepath = mxArrayToString(prhs[0]);

  typedef itkWritePipeline< double > itkWritePipelineType;

  try
  {
    itkWritePipelineType pipeline(filepath);

    mwSize        ndims = mxGetNumberOfDimensions(prhs[1]);
    const mwSize *dims  = mxGetDimensions(prhs[1]);
    double*       image = static_cast< double* >( mxGetPr(prhs[1]) );

    itkWritePipelineType::ImageInfo info;

    switch( nrhs )
    {
      case 2:
      {
        info.ndimensions = ndims;
        info.ncomponents = 1;
        info.component = "double";

        info.dimensions.resize( ndims );
        info.spacing.resize( ndims );
        info.origin.resize( ndims );
        info.index.resize( ndims );
        info.direction.resize( ndims );

        for ( size_t d = 0; d < ndims; d++ )
        {
          info.dimensions[d] = dims[d];
          info.spacing[d] = 1;
          info.origin[d] = 0;
          info.index[d] = 0;

          info.direction[d].resize(ndims);
          for ( size_t dd = 0; dd < ndims; dd++ )
          {
            if ( d == dd )
            {
              info.direction[d][dd] = 1;
            }
            else
            {
              info.direction[d][dd] = 0;
            }
          }
        }

        break;
      }

      case 3:
      {
        const char * fieldnames[] = { "ndimensions", "dimensions", "ncomponents", "spacing", "origin", "index", "direction", "component" };
        enum { NDIMS = 0, DIMENSIONS, NCOMPS, SPACING, ORIGIN, INDEX, DIRECTION, COMPONENT };

        mxArray* mx_ndimensions = mxGetFieldByNumber(prhs[2], 0, NDIMS);
        double*  ndimensions = static_cast< double* >( mxGetPr(mx_ndimensions) );

        mxArray* mx_dimensions = mxGetFieldByNumber(prhs[2], 0, DIMENSIONS);
        double*  dimensions = static_cast< double* >( mxGetPr(mx_dimensions) );

        mxArray* mx_ncomponents = mxGetFieldByNumber(prhs[2], 0, NCOMPS);
        double*  ncomponents = static_cast< double* >( mxGetPr(mx_ncomponents) );

        mxArray* mx_spacing = mxGetFieldByNumber(prhs[2], 0, SPACING);
        double*  spacing = static_cast< double* >( mxGetPr(mx_spacing) );

        mxArray* mx_origin = mxGetFieldByNumber(prhs[2], 0, ORIGIN);
        double*  origin = static_cast< double* >( mxGetPr(mx_origin) );

        mxArray* mx_index = mxGetFieldByNumber(prhs[2], 0, INDEX);
        double*  index = static_cast< double* >( mxGetPr(mx_index) );

        mxArray* mx_direction = mxGetFieldByNumber(prhs[2], 0, DIRECTION);
        double*  direction = static_cast< double* >( mxGetPr(mx_direction) );

        mxArray* mx_component = mxGetFieldByNumber(prhs[2], 0, COMPONENT);
        char*    component = mxArrayToString( mx_component );

        info.ndimensions = ndimensions[0];
        info.ncomponents = ncomponents[0];
        info.component = component;

        info.dimensions.resize( info.ndimensions );
        info.spacing.resize( info.ndimensions );
        info.origin.resize( info.ndimensions );
        info.index.resize( info.ndimensions );
        info.direction.resize( info.ndimensions );

        for ( size_t d = 0; d < info.ndimensions; d++ )
        {
          info.dimensions[d] = dimensions[d];
          info.spacing[d] = spacing[d];
          info.origin[d] = origin[d];
          info.index[d] = index[d];

          info.direction[d].resize(info.ndimensions);
          for ( size_t dd = 0; dd < info.ndimensions; dd++ )
          {
            info.direction[d][dd] = direction[dd + d * info.ndimensions];
          }
        }
        break;
      }

      default:
        break;
    }

    pipeline.Save(image, info);
  }
  catch ( std::exception & e )
  {
    mexErrMsgTxt(e.what());
    return;
  }
}

