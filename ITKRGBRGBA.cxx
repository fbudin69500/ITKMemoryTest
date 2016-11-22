#include <itkRGBPixel.h>
#include <itkRGBAPixel.h>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageRegionIterator.h>

int main(int argc, char* argv[])
{
  typedef itk::RGBPixel<unsigned char> RGBPixelType;
  typedef itk::Image<RGBPixelType,2> RGBImageType;
  typedef itk::ImageFileReader<RGBImageType> RGBReaderType;
  
  typedef itk::RGBAPixel<unsigned char> RGBAPixelType;
  typedef itk::Image<RGBAPixelType,2> RGBAImageType;
  typedef itk::ImageFileReader<RGBAImageType> RGBAReaderType;
  
  RGBReaderType::Pointer rgbReader = RGBReaderType::New();
  rgbReader->SetFileName(argv[1]);
  rgbReader->Update();
  
  RGBAReaderType::Pointer rgbaReader = RGBAReaderType::New();
  rgbaReader->SetFileName(argv[1]);
  rgbaReader->Update();
  
  itk::ImageRegionIterator<RGBImageType> itrgb(rgbReader->GetOutput(), rgbReader->GetOutput()->GetLargestPossibleRegion());
  itk::ImageRegionIterator<RGBAImageType> itrgba(rgbaReader->GetOutput(), rgbaReader->GetOutput()->GetLargestPossibleRegion());
  RGBPixelType rgbPixel;
  RGBAPixelType rgbaPixel;
  
  if(rgbReader->GetOutput()->GetLargestPossibleRegion().GetSize() != rgbaReader->GetOutput()->GetLargestPossibleRegion().GetSize())
  {
      std::cerr << "Different sizes" << std::endl;
      std::cerr << "RGB size: " << rgbReader->GetOutput()->GetLargestPossibleRegion().GetSize() << std::endl;
      std::cerr << "RGBA size: " << rgbaReader->GetOutput()->GetLargestPossibleRegion().GetSize() << std::endl;
      return 1;
  }
  for(itrgb.GoToBegin(), itrgba.GoToBegin(); !itrgb.IsAtEnd() && !itrgba.IsAtEnd(); ++itrgb, ++itrgba)
  {
    rgbPixel = itrgb.Get();
    rgbaPixel = itrgba.Get();
    if(rgbPixel.GetRed() != rgbaPixel.GetRed()
    || rgbPixel.GetGreen() != rgbaPixel.GetGreen()
    || rgbPixel.GetBlue() != rgbaPixel.GetBlue()
    )
    {
      std::cerr << "Different pixel values" << std::endl;
      return 1;
    }
  }
  return 0;
}

