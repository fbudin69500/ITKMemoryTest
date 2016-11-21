#include <itkVectorImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <iostream>

int main(int argc, char* argv[])
{
typedef itk::VectorImage<double,3> ImageType;
typedef itk::ImageFileReader<ImageType> ReaderType;
typedef itk::ImageFileWriter<ImageType> WriterType;
ImageType::Pointer image = ImageType::New();
ImageType::SizeType size;
size.Fill(4);
image->SetRegions(size);
image->SetNumberOfComponentsPerPixel(2);
image->Allocate();
ImageType::PixelType pixel;
pixel.SetSize(2);
pixel.Fill(2.4);
image->FillBuffer(pixel);
WriterType::Pointer writer = WriterType::New();
writer->SetFileName("output.mha");
writer->SetInput(image);
writer->Update();
ReaderType::Pointer reader = ReaderType::New();
reader->SetFileName("output.mha");
reader->Update();
std::cout<<"Size: "<<reader->GetOutput()->GetLargestPossibleRegion().GetSize()<<std::endl;
std::cout<<"Number of component per pixel: "<<reader->GetOutput()->GetNumberOfComponentsPerPixel() <<std::endl;
}
