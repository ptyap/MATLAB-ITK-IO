/*=========================================================================

 Program:   Cast Image File Writer Base

 Copyright (c) Pew-Thian Yap. All rights reserved.
 See http://www.unc.edu/~ptyap/ for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.

 =========================================================================*/

#ifndef __itkCastImageFileWriterBase_h
#define __itkCastImageFileWriterBase_h

#include "itkProcessObject.h"
#include "itkImageIOBase.h"
#include "itkImageIORegion.h"

namespace itk
{

/** \class CastImageFileWriterBase
 * \brief Writes image data, after casting, to a single file.
 *
 * \ingroup IOFilters
 */
template < class TInputImage >
class ITK_EXPORT CastImageFileWriterBase : public ProcessObject
{
public:
  /** Standard class typedefs. */
  typedef CastImageFileWriterBase    Self;
  typedef ProcessObject              Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(CastImageFileWriterBase,ProcessObject);

  /** Some convenient typedefs. */
  typedef TInputImage                         InputImageType;
  typedef typename InputImageType::Pointer    InputImagePointer;
  typedef typename InputImageType::RegionType InputImageRegionType;
  typedef typename InputImageType::PixelType  InputImagePixelType;

  typedef typename ImageIOBase::IOComponentType IOComponentType;

  /** Set/Get the image input of this writer.  */
  using Superclass::SetInput;
  virtual void SetInput(const InputImageType *input);
  const InputImageType * GetInput(void);
  const InputImageType * GetInput(unsigned int idx);

  /** Specify the name of the output file to write. */
  itkSetStringMacro(FileName);
  itkGetStringMacro(FileName);

  /** Set/Get the ImageIO helper class. */
  void SetImageIO (ImageIOBase* io)
  {
    if ( this->m_ImageIO != io )
    {
      this->Modified();
      this->m_ImageIO = io;
    }
    m_FactorySpecifiedImageIO = false;
  }
  itkGetObjectMacro(ImageIO,ImageIOBase);

  /** A special version of the Update() method for writers. */
  virtual void Write(void);

  /** Specify the region to write. If left NULL, then the whole image
   * is written. */
  void SetIORegion(const ImageIORegion & region);
  const ImageIORegion &GetIORegion(void) const
  {
    return m_PasteIORegion;
  }

  /** Set/Get the number of pieces to divide the input. */
  itkSetMacro(NumberOfStreamDivisions,unsigned int);
  itkGetConstReferenceMacro(NumberOfStreamDivisions,unsigned int);

  /** Aliased to the Write() method to be consistent with the rest of the
   * pipeline. */
  virtual void Update()
  {
    this->Write();
  }

  /** Set the compression On or Off */
  itkSetMacro(UseCompression,bool);
  itkGetConstReferenceMacro(UseCompression,bool);
  itkBooleanMacro(UseCompression);

  /** By default the MetaDataDictionary is taken from the input image and
   *  passed to the ImageIO. In some cases, however, a user may prefer to
   *  introduce her/his own MetaDataDictionary. */
  itkSetMacro(UseInputMetaDataDictionary,bool);
  itkGetConstReferenceMacro(UseInputMetaDataDictionary,bool);
  itkBooleanMacro(UseInputMetaDataDictionary);

  /** Set/Get component type */
  itkSetEnumMacro(ComponentType, IOComponentType);
  itkGetEnumMacro(ComponentType, IOComponentType);

protected:
  CastImageFileWriterBase();
  ~CastImageFileWriterBase() {};

  /** Print info. */
  void PrintSelf(std::ostream& os, Indent indent) const;

  /** Does the real work. */
  virtual void GenerateData(void) = 0;

  /** Create file type */
  template< class TOutputImage >
  void WriteImage();

private:
  CastImageFileWriterBase(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  std::string          m_FileName;
  ImageIOBase::Pointer m_ImageIO;
  bool                 m_UserSpecifiedImageIO;
  ImageIORegion        m_PasteIORegion;
  unsigned int         m_NumberOfStreamDivisions;
  bool                 m_UserSpecifiedIORegion;
  bool                 m_FactorySpecifiedImageIO;
  bool                 m_UseCompression;
  bool                 m_UseInputMetaDataDictionary;
  IOComponentType      m_ComponentType;
};


} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkCastImageFileWriterBase.hxx"
#endif

#endif // __itkCastImageFileWriterBase_h
