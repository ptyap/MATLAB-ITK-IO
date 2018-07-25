/**
 * @file itkWritePipeline.h
 * @brief ITK IO for Matlab
 * @author Pew-Thian Yap
 */

#ifndef __itkWritePipeline_hxx
#define __itkWritePipeline_hxx

#include "itkWritePipeline.h"

template < class TPixelType, unsigned int Dimension >
itkWritePipeline< TPixelType, Dimension >::itkWritePipeline(char* filepath) :
  m_filepath(filepath)
{
}

template < class TPixelType, unsigned int Dimension >
void itkWritePipeline< TPixelType, Dimension >::Save(TPixelType* image, ImageInfo & info)
{
  typename ImageType::SizeType itk_size;
  typename ImageType::SpacingType itk_spacing;
  typename ImageType::PointType itk_origin;
  typename ImageType::IndexType itk_index;
  typename ImageType::DirectionType itk_direction;
  itk_direction.SetIdentity();

  size_t itk_ncomponents = info.ncomponents;

  for ( unsigned int d = 0; d < Dimension; d++ )
  {
    if ( d < info.ndimensions )
    {
      itk_size[d] = info.dimensions[d];
      itk_spacing[d] = info.spacing[d];
      itk_origin[d] = info.origin[d];
      itk_index[d] = info.index[d];

      for ( size_t dd = 0; dd < info.ndimensions; dd++ )
      {
        itk_direction[dd][d] = info.direction[d][dd];
      }
    }
    else
    {
      itk_size[d] = 1;
      itk_spacing[d] = 1;
      itk_origin[d] = 0;
      itk_index[d] = 0;
    }
  }

  typename ImageType::RegionType itk_region;
  itk_region.SetSize(itk_size);
  itk_region.SetIndex(itk_index);

  typename ImageType::Pointer itk_image = ImageType::New();
  itk_image->SetSpacing(itk_spacing);
  itk_image->SetRegions(itk_region);
  itk_image->SetOrigin(itk_origin);
  itk_image->SetNumberOfComponentsPerPixel(itk_ncomponents);
  itk_image->SetDirection(itk_direction);
  itk_image->Allocate();

  typename ImageType::PixelType itk_pixel;
  itk_pixel.SetSize(itk_ncomponents);
  itk_pixel.Fill(0);
  itk_image->FillBuffer(itk_pixel);

  typedef itk::ImageRegionIterator< ImageType > IteratorType;
  IteratorType imageIt(itk_image, itk_region);
  unsigned int count = 0;
  for ( imageIt.GoToBegin(); !imageIt.IsAtEnd(); ++imageIt )
  {
    for ( size_t i = 0; i < itk_ncomponents; i++ )
    {
      itk_pixel[i] = image[count];
      count++;
    }
    imageIt.Set(itk_pixel);
  }

  typename WriterType::Pointer itk_writer = WriterType::New();
  itk_writer->SetFileName(m_filepath);
  itk_writer->SetComponentType( itk::ImageIOBase::GetComponentTypeFromString(info.component) );
  itk_writer->SetInput(itk_image);

  try
  {
    itk_writer->Update();
  }
  catch( itk::ExceptionObject & err )
  {
    std::cerr << "ExceptionObject caught!" << std::endl;
    std::cerr << err << std::endl;
    exit(EXIT_FAILURE);
  }
}

#endif // __itkWritePipeline_hxx
