#include <itkRGBPixel.h>
#include <itkVector.h>
#include <iostream>
#include <itkImage.h>
#include <itkImageRegionIterator.h>

template<typename ComponentType> void FillAndPrintRGB(int intsize, std::string name)
{
  typedef itk::RGBPixel<ComponentType> RGBPixelType;
  RGBPixelType rgbPixel;
  if(sizeof(rgbPixel) != sizeof(ComponentType)*3)
  {
    std::cerr << "sizeof(rgbPixel): " << sizeof(rgbPixel)
              << "  sizeof(ComponentType)*3: " << sizeof(ComponentType)*3 << std::endl;
    throw(std::string("RGB: Wrong pixel size:")+name);
  }
  typedef itk::Image<RGBPixelType,3> RGBImageType;
  typename RGBImageType::Pointer rgbImage = RGBImageType::New();
  typename RGBImageType::SizeType rgbsize;
  rgbsize.Fill(intsize);
  rgbImage->SetRegions(rgbsize);
  rgbImage->Allocate();
  itk::ImageRegionIterator<RGBImageType> it(rgbImage,rgbImage->GetLargestPossibleRegion());
  ComponentType val=0;
  for(it.GoToBegin(); !it.IsAtEnd();++it)
  {
    rgbPixel.SetRed(val);
    rgbPixel.SetGreen(val+1);
    rgbPixel.SetBlue(val+2);
    it.Set(rgbPixel);
    val+=3;
  }
  ComponentType* ptr = reinterpret_cast<ComponentType*>(rgbImage->GetBufferPointer());
  for(int ii =0; ii < rgbsize[0]*rgbsize[1]*rgbsize[2];ii++)
  {
    ComponentType val_1 = *(ptr+ii*3);
    ComponentType val_2 = *(ptr+ii*3+1);
    ComponentType val_3 = *(ptr+ii*3+2);
   if( static_cast<unsigned long>(val_1) +1 != static_cast<unsigned long>(val_2)
    || static_cast<unsigned long>(val_1)+2 != static_cast<unsigned long>(val_3))
   {
     std::cerr<<"val_1:"<<static_cast<double>(val_1)<<std::endl;
     std::cerr<<"val_2:"<<static_cast<double>(val_2)<<std::endl;
     std::cerr<<"val_3:"<<static_cast<double>(val_3)<<std::endl;
     throw(std::string("RGB: Wrong value:")+name);
   }
  }
}

template<typename ComponentType> void FillAndPrintRGB(std::string name, size_t max)
{
  for( size_t ii = 1; ii < max ; ii++ )
  {
    FillAndPrintRGB<ComponentType>(ii, name);
  }
}



template<typename ComponentType,int SizeVec>
void FillAndTestVectorImages(unsigned long size_im, std::string name)
{
  typedef itk::Vector<ComponentType,SizeVec> VectorType;
  VectorType vectorPixel;
  if(sizeof(vectorPixel) != sizeof(ComponentType)*SizeVec)
  {
    std::cout << "sizeof(vectorPixel): " << sizeof(vectorPixel)
              << "  sizeof(ComponentType)*SizeVec: " << sizeof(ComponentType)*SizeVec << std::endl;
    throw(std::string("Vector: Wrong pixel size:")+name);
  }
  typedef itk::Image<VectorType,3> ImageType;
  typename ImageType::Pointer image = ImageType::New();
  typename ImageType::SizeType size;
  size.Fill(size_im);
  image->SetRegions(size);
  image->Allocate();
  itk::ImageRegionIterator<ImageType> it(image,image->GetLargestPossibleRegion());
  ComponentType val=0;
  for(it.GoToBegin(); !it.IsAtEnd();++it)
  {
    for(int ii = 0 ; ii < SizeVec ; ii++)
    {
      vectorPixel[ii]=val;
      val++;
    }
    it.Set(vectorPixel);
  }
  ComponentType* ptr = reinterpret_cast<ComponentType*>(image->GetBufferPointer());
  for(int ii =0; ii < size[0]*size[1]*size[2];ii++)
  {
    std::vector<ComponentType> vec;
    for(int jj = 0 ; jj < SizeVec; jj++)
    {
      vec.push_back(*(ptr+ii*SizeVec+jj));
      if( static_cast<unsigned long>(vec[0])+jj != static_cast<unsigned long>(vec[jj]))
      {
        std::cerr << "static_cast<unsigned long>(vec[0])+jj: " << static_cast<unsigned long>(vec[0])+jj
                  << "  static_cast<unsigned long>(vec[jj]): " << static_cast<unsigned long>(vec[jj]) << std::endl;
        throw(std::string("Wrong value:")+name);
      }
   }
  }
}

template<typename ComponentType, int VecSize>
void FillAndTestVectorImages(std::string name, size_t max)
{
  for( size_t ii = 1; ii < max ; ii++ )
  {
    FillAndTestVectorImages<ComponentType, VecSize>(ii, name);
  }
}


int main(int argc, char* argv[])
{
  try
  {
    FillAndPrintRGB<double>("double",100);
    FillAndPrintRGB<float>("float",100);
    FillAndPrintRGB<unsigned char>("unsigned char",4);
    FillAndPrintRGB<char>("char",3);
    FillAndPrintRGB<short>("short",3);
    FillAndPrintRGB<unsigned short>("unsigned short",3);
    FillAndPrintRGB<unsigned int>("unsigned int",10);
    FillAndPrintRGB<signed int>("signed int",10);
    FillAndPrintRGB<long>("long",10);
    FillAndPrintRGB<unsigned long>("unsigned long",10);
    FillAndPrintRGB<long long>("long long",10);
    FillAndPrintRGB<unsigned long long>("unsigned long long",10);
    FillAndTestVectorImages<double, 10>("double", 10);
    FillAndTestVectorImages<float, 10>("float", 10);
    FillAndTestVectorImages<signed char, 3>("signed char", 3);
    FillAndTestVectorImages<unsigned char, 4>("unsigned char", 5);
    FillAndTestVectorImages<short, 4>("short", 5);
    FillAndTestVectorImages<unsigned short, 4>("unsigned short", 5);
    FillAndTestVectorImages<int, 10>("int", 10);
    FillAndTestVectorImages<unsigned int, 10>("unsigned int", 10);
    FillAndTestVectorImages<long, 10>("long", 10);
    FillAndTestVectorImages<unsigned long, 10>("unsigned long", 10);
    FillAndTestVectorImages<long long, 10>("long long", 10);
    FillAndTestVectorImages<unsigned long long, 10>("unsigned long long", 10);
  }
  catch(std::string error)
  {
    std::cout<<error<<std::endl;
    return 1;
  }
  return 0;
}
