/**
 * @file itkWritePipeline.h
 * @brief ITK IO for Matlab
 * @author Pew-Thian Yap
 */

#ifndef __itkWritePipeline_hxx
#define __itkWritePipeline_hxx

#include "itkWritePipeline.h"

template <class TPixelType, unsigned int Dimension>
itkWritePipeline<TPixelType, Dimension>::itkWritePipeline(char* filepath):
	m_filepath(filepath)
{
	m_writer = WriterType::New();
	m_writer->SetFileName(filepath);
}

template <class TPixelType, unsigned int Dimension>
void itkWritePipeline<TPixelType, Dimension>::Save(TPixelType* image, size_t* size, double* origin, double* spacing)
{
  typename ImageType::Pointer itk_image = ImageType::New();
  typename ImageType::RegionType itk_region;
  typename ImageType::SizeType itk_size;
  typename ImageType::PointType itk_origin;
	typename ImageType::SpacingType itk_spacing;
  typename ImageType::IndexType itk_index;
  typename ImageType::PixelType itk_pixel;
	typedef itk::ImageRegionIterator<ImageType> IteratorType;

	if (origin != 0)
    {
		for (unsigned int d=0; d<Dimension; d++)
      {
			itk_origin[d] = origin[d];
      }
    }
	else
    {
		itk_origin.Fill(0);
    }

	if (spacing != 0)
    {
		for (unsigned int d=0; d<Dimension; d++)
      {
			itk_spacing[d] = spacing[d];
      }
    }
	else
    {
		itk_spacing.Fill(1.0);
    }

	for (unsigned int d=0; d<Dimension; d++)
    {
		itk_size[d] = size[d];
    }

	itk_index.Fill(0);
	itk_region.SetSize(itk_size);
	itk_region.SetIndex(itk_index);
	itk_image->SetSpacing(itk_spacing);
	itk_image->SetRegions(itk_region);
	itk_image->SetOrigin(itk_origin);
	itk_image->Allocate();
	itk_pixel = itk::NumericTraits<typename ImageType::PixelType>::Zero;
	itk_image->FillBuffer(itk_pixel);

	IteratorType imageIt(itk_image, itk_region);
	unsigned int count = 0;
  for (imageIt.GoToBegin(); !imageIt.IsAtEnd(); ++imageIt, count++)
    {
		itk_pixel = image[count];
		imageIt.Set(itk_pixel);
    }

	typename WriterType::Pointer itk_writer = WriterType::New();
	itk_writer->SetFileName(m_filepath);
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
