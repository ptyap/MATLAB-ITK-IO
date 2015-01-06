/**
 * @file itkReadPipeline.h
 * @brief Pipeline for reading ITK supported image files
 * @author Pew-Thian Yap
 */

#ifndef __itkReadPipeline_h
#define __itkReadPipeline_h

#include "itkImageFileReader.h"
#include "itkImageRegionConstIterator.h"

template <class TPixelType, unsigned int Dimension = 3>
class itkReadPipeline
{
public:
  itkReadPipeline(char* filepath);

  /**
   * @brief Creates and copies the resulting image and its location information to the given
   * double pointers.
   *
   * @param image
   * @param origin
   * @param spacing
   */
  void Copy(TPixelType* image, double* origin = 0, double* spacing = 0);

  /**
   * @brief get the size of the transposed output image
   *
   * @param size[Dimension] dimensions
   */
  void GetSize(size_t *size);

  // main itk types
  typedef itk::Image<TPixelType, Dimension> ImageType;

protected:
  // filter types
  typedef itk::ImageFileReader<ImageType> ReaderType;
  typename ReaderType::Pointer m_reader;

  char* m_filepath;
};

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkReadPipeline.hxx"
#endif

#endif // __itkReadPipeline_h
