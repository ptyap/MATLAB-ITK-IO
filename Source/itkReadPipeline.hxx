/**
 * @file itkReadPipeline.h
 * @brief ITK IO for Matlab
 * @author Pew-Thian Yap
 */

#ifndef __itkReadPipeline_hxx
#define __itkReadPipeline_hxx

#include "itkReadPipeline.h"

template <class TPixelType, unsigned int Dimension>
itkReadPipeline<TPixelType, Dimension>::itkReadPipeline(char* filepath):
  m_filepath(filepath)
{
  m_reader = ReaderType::New();
  m_reader->SetFileName(filepath);
}

template <class TPixelType, unsigned int Dimension>
void itkReadPipeline<TPixelType, Dimension>::Copy(TPixelType* image, double* origin, double* spacing)
{
  m_reader->Update();
  typename ImageType::Pointer itk_image = m_reader->GetOutput();
  typename ImageType::RegionType itk_region = itk_image->GetLargestPossibleRegion();
  typename ImageType::SizeType itk_size = itk_region.GetSize();
  typedef itk::ImageRegionConstIterator<ImageType> ConstIteratorType;

  ConstIteratorType imageIt(itk_image, itk_region);
  unsigned int count = 0;
  for (imageIt.GoToBegin(); !imageIt.IsAtEnd(); ++imageIt, count++)
    {
    image[count] = imageIt.Value();
    }

  if (origin != 0)
    {
    typename ImageType::PointType itk_origin = itk_image->GetOrigin();
    for (unsigned int d=0; d<Dimension; d++)
      {
      origin[d] = static_cast<double>(itk_origin[d]);
      }
    }

  if (spacing != 0)
    {
    typename ImageType::SpacingType itk_spacing = itk_image->GetSpacing();
    for (unsigned int d=0; d<Dimension; d++)
      {
      spacing[d] = static_cast<double>(itk_spacing[d]);
      }
    }
}

template <class TPixelType, unsigned int Dimension>
void itkReadPipeline<TPixelType, Dimension>::GetSize(size_t *size)
{
  m_reader->UpdateOutputInformation();
  typename ImageType::SizeType itk_size = m_reader->GetOutput()->GetLargestPossibleRegion().GetSize();
  for (unsigned int d=0; d<Dimension; d++)
    {
    size[d] = itk_size[d];
    }
}

#endif // __itkReadPipeline_hxx
