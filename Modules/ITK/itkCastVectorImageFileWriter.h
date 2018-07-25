/*=========================================================================

 Program:   Cast Vector Image File Writer

 Copyright (c) Pew-Thian Yap. All rights reserved.
 See http://www.unc.edu/~ptyap/ for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.

 =========================================================================*/

#ifndef __itkCastVectorImageFileWriter_h
#define __itkCastVectorImageFileWriter_h

#include "itkCastImageFileWriterBase.h"

namespace itk
{

/** \class CastVectorImageFileWriter
 * \brief Writes image data, after casting, to a single file.
 *
 * \ingroup IOFilters
 */
template < class TInputImage >
class ITK_TEMPLATE_EXPORT CastVectorImageFileWriter :
  public                  CastImageFileWriterBase< TInputImage >
{
public:
  /** Standard class typedefs. */
  typedef CastVectorImageFileWriter              Self;
  typedef CastImageFileWriterBase< TInputImage > Superclass;
  typedef SmartPointer< Self >                   Pointer;
  typedef SmartPointer< const Self >             ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(CastVectorImageFileWriter,CastImageFileWriterBase);

  /** Some convenient typedefs. */
  typedef typename Superclass::InputImageType    InputImageType;
  typedef typename Superclass::InputImagePointer InputImagePointer;
  typedef typename Superclass::IOComponentType   IOComponentType;

protected:
  CastVectorImageFileWriter() {};
  ~CastVectorImageFileWriter() {};

  /** Does the real work. */
  void GenerateData();

private:
  CastVectorImageFileWriter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};


} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkCastVectorImageFileWriter.hxx"
#endif

#endif // __itkCastVectorImageFileWriter_h
