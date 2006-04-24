#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCommand.h"
#include "itkSimpleFilterWatcher.h"

#include "itkLabelOverlayImageFilter.h"


int main(int argn, char * argv[])
{

  if( argn == 1 )
    {
    std::cerr << "Usage: check2 input label output [opacity [useBg [bg]]]" << std::endl;
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
  ReaderType::Pointer reader2 = ReaderType::New();
  reader2->SetFileName( argv[2] );

  typedef itk::LabelOverlayImageFilter< IType, IType, CIType> FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetLabelImage( reader2->GetOutput() );
  if( argn >= 5 )
    { filter->SetOpacity( atof(argv[4]) ); }
  if( argn >= 6 )
    { filter->SetUseBackground( atoi(argv[5]) ); }
  if( argn >= 7 )
    { filter->SetBackgroundValue( atoi(argv[6]) ); }

  itk::SimpleFilterWatcher watcher(filter, "filter");

  typedef itk::ImageFileWriter< CIType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( argv[3] );
  writer->Update();

  return 0;
}

