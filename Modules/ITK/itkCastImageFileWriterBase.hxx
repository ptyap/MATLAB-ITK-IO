/*=========================================================================

 Program:   Cast Image File Writer Base

 Copyright (c) Pew-Thian Yap. All rights reserved.
 See http://www.unc.edu/~ptyap/ for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.

 =========================================================================*/

#ifndef __itkCastImageFileWriterBase_hxx
#define __itkCastImageFileWriterBase_hxx

#include "itkImage.h"
#include "itkImageFileWriter.h"
#include "itkCastImageFilter.h"
#include "itkCastImageFileWriterBase.h"

namespace itk
{

template < class TInputImage >
CastImageFileWriterBase< TInputImage >
::CastImageFileWriterBase() :
  m_PasteIORegion(TInputImage::ImageDimension)
{
  m_UseCompression = false;
  m_UseInputMetaDataDictionary = true;
  m_FactorySpecifiedImageIO = false;
  m_UserSpecifiedIORegion = false;
  m_UserSpecifiedImageIO = false;
  m_NumberOfStreamDivisions = 1;
  m_ComponentType = ImageIOBase::DOUBLE;
}

template < class TInputImage >
void
CastImageFileWriterBase< TInputImage >
::SetInput(const InputImageType *input)
{
  // ProcessObject is not const_correct so this cast is required here.
  this->ProcessObject::SetNthInput(0, const_cast< TInputImage * >( input ) );
}

template < class TInputImage >
const typename CastImageFileWriterBase< TInputImage >::InputImageType *
CastImageFileWriterBase< TInputImage >
::GetInput(void)
{
  if ( this->GetNumberOfInputs() < 1 )
  {
    return 0;
  }

  return static_cast< TInputImage* > ( this->ProcessObject::GetInput(0) );
}

template < class TInputImage >
const typename CastImageFileWriterBase< TInputImage >::InputImageType *
CastImageFileWriterBase< TInputImage >
::GetInput(unsigned int idx)
{
  return static_cast< TInputImage* > ( this->ProcessObject::GetInput(idx));
}

template < class TInputImage >
void
CastImageFileWriterBase< TInputImage >
::SetIORegion (const ImageIORegion& region)
{
  if ( m_PasteIORegion != region )
  {
    m_PasteIORegion = region;
    this->Modified();
    m_UserSpecifiedIORegion = true;
  }
}

template < class TInputImage >
void
CastImageFileWriterBase< TInputImage >
::Write()
{
  this->GenerateData();
}

template < class TInputImage >
template < class TOutputImage >
void
CastImageFileWriterBase< TInputImage >
::WriteImage()
{
  const InputImageType * inputPtr = this->GetInput();

  typedef CastImageFilter< TInputImage, TOutputImage > CastFilterType;
  typename CastFilterType::Pointer castFilter = CastFilterType::New();
  castFilter->SetInput( inputPtr );

  typedef ImageFileWriter< TOutputImage > WriterType;
  typename WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( this->GetFileName() );
  writer->SetInput( castFilter->GetOutput() );
  writer->SetImageIO( this->GetImageIO() );
  writer->SetIORegion( this->GetIORegion() );
  writer->SetNumberOfStreamDivisions( this->GetNumberOfStreamDivisions() );
  writer->SetUseCompression( this->GetUseCompression() );
  writer->SetUseInputMetaDataDictionary( this->GetUseInputMetaDataDictionary() );
  writer->Update();
}

template < class TInputImage >
void
CastImageFileWriterBase< TInputImage >
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "File Name: "
     << ( m_FileName.data() ? m_FileName.data() : "(none)" ) << std::endl;

  os << indent << "Image IO: ";
  if ( m_ImageIO.IsNull() )
  {
    os << "(none)\n";
  }
  else
  {
    os << m_ImageIO << "\n";
  }

  os << indent << "IO Region: " << m_PasteIORegion << "\n";
  os << indent << "Number of Stream Divisions: " << m_NumberOfStreamDivisions << "\n";

  if ( m_UseCompression )
  {
    os << indent << "Compression: On\n";
  }
  else
  {
    os << indent << "Compression: Off\n";
  }

  if ( m_UseInputMetaDataDictionary )
  {
    os << indent << "UseInputMetaDataDictionary: On\n";
  }
  else
  {
    os << indent << "UseInputMetaDataDictionary: Off\n";
  }

  if ( m_FactorySpecifiedImageIO )
  {
    os << indent << "FactorySpecifiedmageIO: On\n";
  }
  else
  {
    os << indent << "FactorySpecifiedmageIO: Off\n";
  }
}

} // end namespace itk

#endif
