/**
 * @file itkWritePipeline.h
 * @brief Pipeline for writing ITK supported image files
 * @author Pew-Thian Yap
 */

#ifndef __itkWritePipeline_h
#define __itkWritePipeline_h

#include "itkImageFileWriter.h"
#include "itkImageRegionConstIterator.h"

template <class TPixelType, unsigned int Dimension = 3>
class itkWritePipeline
{
public:
  itkWritePipeline(char* filepath);

  /**
   * @brief Save image matrix as any ITK supported format.
   *
   * @param image
   * @param size
   * @param origin
   * @param spacing
   */
  void Save(TPixelType* image, size_t* size = 0, double* origin = 0, double* spacing = 0);

  // main itk types
  typedef itk::Image<TPixelType, Dimension> ImageType;

protected:
  // filter types
  typedef itk::ImageFileWriter<ImageType> WriterType;
  typename WriterType::Pointer m_writer;

  char* m_filepath;

};

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkWritePipeline.hxx"
#endif

#endif // __itkWritePipeline_h
