/**
 * @file itkReadPipeline.h
 * @brief ITK IO for Matlab
 * @author Pew-Thian Yap <ptyap@med.unc.edu>
 */

#ifndef __itkReadPipeline_hxx
#define __itkReadPipeline_hxx

#include "itkReadPipeline.h"
#include "itkImageIOBase.h"


template < class TPixelType, unsigned int Dimension >
itkReadPipeline< TPixelType, Dimension >::itkReadPipeline(char* filepath) :
  m_filepath(filepath)
{
  m_reader = ReaderType::New();
  m_reader->SetFileName(filepath);
  m_reader->UpdateOutputInformation();
}

template < class TPixelType, unsigned int Dimension >
void itkReadPipeline< TPixelType, Dimension >::Copy(TPixelType* image, ImageInfo & info)
{
  m_reader->Update();

  typename ImageType::Pointer itk_image = m_reader->GetOutput();
  typename itk::ImageIOBase::Pointer itk_imageio = m_reader->GetImageIO();

  size_t itk_ncomponents = this->GetNumberOfComponents();
  typename ImageType::RegionType itk_region = itk_image->GetLargestPossibleRegion();

  typedef itk::ImageRegionConstIterator< ImageType > ConstIteratorType;
  ConstIteratorType imageIt(itk_image, itk_region);

  size_t count = 0;

  for ( imageIt.GoToBegin(); !imageIt.IsAtEnd(); ++imageIt )
  {
    typename ImageType::PixelType pixel = imageIt.Get();
    for ( size_t i = 0; i < itk_ncomponents; i++ )
    {
      image[count] = pixel[i];
      count++;
    }
  }

  info.ndimensions = itk_imageio->GetNumberOfDimensions();
  info.ncomponents = itk_image->GetNumberOfComponentsPerPixel();

  typename ImageType::SizeType itk_size = itk_region.GetSize();
  info.dimensions.resize( info.ndimensions );
  for ( size_t d = 0; d < info.ndimensions; d++ )
  {
    info.dimensions[d] = static_cast< size_t >( itk_size[d] );
  }

  typename ImageType::SpacingType itk_spacing = itk_image->GetSpacing();
  info.spacing.resize( info.ndimensions );
  for ( size_t d = 0; d < info.ndimensions; d++ )
  {
    info.spacing[d] = static_cast< double >( itk_spacing[d] );
  }

  typename ImageType::PointType itk_origin = itk_image->GetOrigin();
  info.origin.resize( info.ndimensions );
  for ( size_t d = 0; d < info.ndimensions; d++ )
  {
    info.origin[d] = static_cast< double >( itk_origin[d] );
  }

  typename ImageType::IndexType itk_index = itk_region.GetIndex();
  info.index.resize( info.ndimensions );
  for ( size_t d = 0; d < info.ndimensions; d++ )
  {
    info.index[d] = static_cast< double >( itk_index[d] );
  }

  info.direction.resize(info.ndimensions);
  for ( size_t c = 0; c < info.ndimensions; c++ )
  {
    info.direction[c] = itk_imageio->GetDirection(c);
  }

  info.component =
      itk_imageio->GetComponentTypeAsString( itk_imageio->GetComponentType() );
}

template < class TPixelType, unsigned int Dimension >
size_t itkReadPipeline< TPixelType, Dimension >::GetNumberOfDimensions()
{
  return m_reader->GetImageIO()->GetNumberOfDimensions();
}

template < class TPixelType, unsigned int Dimension >
typename itkReadPipeline< TPixelType, Dimension >::SizeType
itkReadPipeline< TPixelType, Dimension >::GetSize()
{
  return m_reader->GetOutput()->GetLargestPossibleRegion().GetSize();
}

template < class TPixelType, unsigned int Dimension >
size_t itkReadPipeline< TPixelType, Dimension >::GetNumberOfComponents()
{
  return m_reader->GetOutput()->GetNumberOfComponentsPerPixel();
}

#endif // __itkReadPipeline_hxx
