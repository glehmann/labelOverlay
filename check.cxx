#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCommand.h"
#include "itkSimpleFilterWatcher.h"

#include "itkLabelToRGBImageFilter.h"


int main(int argn, char * argv[])
{

  if( argn == 1 )
    {
    std::cerr << "Usage: check label output [useBg [bg]]" << std::endl;
    std::cerr << " useBg is false by default" << std::endl;
    std::cerr << " bg is 0 by default" << std::endl;
    return 1;
    }

  const int dim = 2;
  
  typedef unsigned char PType;
  typedef itk::Image< PType, dim > IType;

  typedef itk::RGBPixel<unsigned char> CPType;
  typedef itk::Image< CPType, dim > CIType;

  typedef itk::ImageFileReader< IType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  typedef itk::LabelToRGBImageFilter< IType, CIType> FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  if( argn >= 4 )
    { filter->SetUseBackground( atoi(argv[3]) ); }
  if( argn >= 5 )
    { filter->SetBackgroundValue( atoi(argv[4]) ); }

  itk::SimpleFilterWatcher watcher(filter, "filter");

  typedef itk::ImageFileWriter< CIType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( argv[2] );
  writer->Update();

  return 0;
}

