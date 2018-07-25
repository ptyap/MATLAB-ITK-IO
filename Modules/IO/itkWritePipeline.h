/**
 * @file itkWritePipeline.h
 * @brief Pipeline for writing ITK supported image files
 * @author Pew-Thian Yap <ptyap@med.unc.edu>
 */

#ifndef __itkWritePipeline_h
#define __itkWritePipeline_h

#include "itkVectorImage.h"
#include "itkCastVectorImageFileWriter.h"
#include "itkImageRegionConstIterator.h"

template < class TPixelType, unsigned int Dimension = 4 >
class itkWritePipeline
{
public:
  itkWritePipeline(char* filepath);

  struct ImageInfo {
    size_t ndimensions;
    std::vector< size_t > dimensions;
    size_t ncomponents;
    std::vector< double > spacing;
    std::vector< double > origin;
    std::vector< signed long > index;
    std::vector< std::vector< double > > direction;
    std::string component;
  };

  // main itk types
  typedef itk::VectorImage< TPixelType, Dimension > ImageType;

  /**
   * @brief Save image matrix as any ITK supported format.
   *
   * @param image
   * @param info
   */
  void Save(TPixelType* image, ImageInfo & info);

protected:
  // filter types
  typedef itk::CastVectorImageFileWriter< ImageType > WriterType;

  char* m_filepath;

};

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkWritePipeline.hxx"
#endif

#endif // __itkWritePipeline_h
