/*=========================================================================

 Program:   Cast Vector Image File Writer

 Copyright (c) Pew-Thian Yap. All rights reserved.
 See http://www.unc.edu/~ptyap/ for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.

 =========================================================================*/

#ifndef __itkCastVectorImageFileWriter_hxx
#define __itkCastVectorImageFileWriter_hxx

#include "itkVariableLengthVector.h"
#include "itkCastVectorImageFileWriter.h"

namespace itk
{

template < class TInputImage >
void
CastVectorImageFileWriter< TInputImage >
::GenerateData()
{
  switch ( this->GetComponentType() )
  {
    case ImageIOBase::UCHAR:
      this->template WriteImage< VectorImage<unsigned char, TInputImage::ImageDimension> >();
      break;
    case ImageIOBase::CHAR:
      this->template WriteImage< VectorImage<char, TInputImage::ImageDimension> >();
      break;
    case ImageIOBase::USHORT:
      this->template WriteImage< VectorImage<unsigned short, TInputImage::ImageDimension> >();
      break;
    case ImageIOBase::SHORT:
      this->template WriteImage< VectorImage<short, TInputImage::ImageDimension> >();
      break;
    case ImageIOBase::UINT:
      this->template WriteImage< VectorImage<unsigned int, TInputImage::ImageDimension> >();
      break;
    case ImageIOBase::INT:
      this->template WriteImage< VectorImage<int, TInputImage::ImageDimension> >();
      break;
    case ImageIOBase::ULONG:
      this->template WriteImage< VectorImage<unsigned long, TInputImage::ImageDimension> >();
      break;
    case ImageIOBase::LONG:
      this->template WriteImage< VectorImage<long, TInputImage::ImageDimension> >();
      break;
    case ImageIOBase::FLOAT:
      this->template WriteImage< VectorImage<float, TInputImage::ImageDimension> >();
      break;
    case ImageIOBase::DOUBLE:
      this->template WriteImage< VectorImage<double, TInputImage::ImageDimension> >();
      break;
    default:
      break;
  }
}

} // end namespace itk

#endif
