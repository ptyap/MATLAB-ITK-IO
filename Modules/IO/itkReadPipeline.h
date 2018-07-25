/**
 * @file itkReadPipeline.h
 * @brief Pipeline for reading ITK supported image files
 * @author Pew-Thian Yap <ptyap@med.unc.edu>
 */

#ifndef __itkReadPipeline_h
#define __itkReadPipeline_h

#include "itkVectorImage.h"
#include "itkImageFileReader.h"
#include "itkImageRegionConstIterator.h"

template < class TPixelType, unsigned int Dimension = 4 >
class itkReadPipeline
{
public:
  itkReadPipeline(char* filepath);

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
  typedef typename ImageType::SizeType              SizeType;
  typedef typename ImageType::IndexType             IndexType;

  /**
   * @brief Creates and copies the resulting image and its information.
   *
   * @param info
   */
  void Copy(TPixelType* image, ImageInfo & info);

  /**
   * @brief Get the number of dimensions of the input image
   */
  size_t GetNumberOfDimensions();

  /**
   * @brief Get the dimensions of the input image
   *
   * @param size[Dimension] dimensions
   */
  SizeType GetSize();

  /**
   * @brief Get the number of components per pixel of the input image
   */
  size_t GetNumberOfComponents();

protected:
  // filter types
  typedef itk::ImageFileReader< ImageType > ReaderType;
  typename ReaderType::Pointer m_reader;

  char* m_filepath;
};

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkReadPipeline.hxx"
#endif

#endif // __itkReadPipeline_h
