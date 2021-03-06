
////////////////////////////////////////////////////////////////////////////////
//
// Generate cropped images using ROI obtained from probabilities
//
////////////////////////////////////////////////////////////////////////////////

// prastawa@cs.unc.edu 11/2003

#ifndef _AtlasCropImageSource_h
#define _AtlasCropImageSource_h

#include "itkObject.h"

#include "DynArray.h"

template <class TInputImage, class TProbabilityImage>
class AtlasCropImageSource: public itk::Object
{

public:

  /** Standard class typedefs. */
  typedef AtlasCropImageSource Self;
  typedef itk::SmartPointer<Self> Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** The dimension of the image. */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TInputImage::ImageDimension);

  // Image types
  typedef TInputImage InputImageType;
  typedef typename TInputImage::Pointer InputImagePointer;
  typedef typename TInputImage::IndexType InputImageIndexType;
  typedef typename TInputImage::OffsetType InputImageOffsetType;
  typedef typename TInputImage::PixelType InputImagePixelType;
  typedef typename TInputImage::RegionType InputImageRegionType;
  typedef typename TInputImage::SizeType InputImageSizeType;
  typedef typename TInputImage::SpacingType InputImageSpacingType;

  typedef TProbabilityImage ProbabilityImageType;
  typedef typename ProbabilityImageType::Pointer ProbabilityImagePointer;
  typedef typename ProbabilityImageType::IndexType ProbabilityImageIndexType;
  typedef typename ProbabilityImageType::OffsetType ProbabilityImageOffsetType;
  typedef typename ProbabilityImageType::PixelType ProbabilityImagePixelType;
  typedef typename ProbabilityImageType::RegionType ProbabilityImageRegionType;
  typedef typename ProbabilityImageType::SizeType ProbabilityImageSizeType;
  typedef typename ProbabilityImageType::SpacingType ProbabilityImageSpacingType;

  typedef DynArray<ProbabilityImagePointer> ProbabilityImageList;

  typedef struct
  {
    InputImageIndexType offset;
    InputImageSizeType cropped_size;
    InputImageSizeType original_size;
  } CropInfoType;

  // Set/get output image padding, in mm
  itkGetMacro(Padding, double);
  itkSetMacro(Padding, double);

  bool CheckBounds();

  void UseProbabilities(ProbabilityImageList probs);

  // Create new images (either cropped or padded)
  InputImagePointer Restore(InputImagePointer img);
  InputImagePointer Crop(InputImagePointer img);

  // Crop region information
  void SetCropInfo(const CropInfoType& info) { m_CropInfo = info; }
  const CropInfoType& GetCropInfo() { return m_CropInfo; }

protected:

  AtlasCropImageSource();
  ~AtlasCropImageSource() {}

  double m_Padding;

  InputImageSizeType m_LowerBound;
  InputImageSizeType m_UpperBound;

  InputImageSizeType m_OriginalSize;

  CropInfoType m_CropInfo;

};

#ifndef MU_MANUAL_INSTANTIATION
#include "AtlasCropImageSource.txx"
#endif

#endif
