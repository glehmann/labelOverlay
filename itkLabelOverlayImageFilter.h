#ifndef __itkLabelOverlayImageFilter_h
#define __itkLabelOverlayImageFilter_h

#include "itkLabelToRGBImageFilter.h"

#include "itkBinaryFunctorImageFilter.h"

namespace itk
{

namespace Functor {  
 
template< class TInputPixel, class TLabel, class TRGBPixel >
class LabelOverlay
{
public:

  LabelOverlay() {}

  inline TRGBPixel operator()(  const TInputPixel & p1,
				const TLabel & p2)
  {
    if( m_UseBackground && p2 == m_BackgroundValue )
      {
      typename TRGBPixel::ValueType p = static_cast< typename TRGBPixel::ValueType >( p1 );
      TRGBPixel rgbPixel;
      rgbPixel.Set( p, p, p );
      return rgbPixel;
      }
     TRGBPixel rgbPixel;
     TRGBPixel opaque = m_RGBFunctor(p2);
     for( int i = 0; i<3; i++)
       {
       rgbPixel[i] = static_cast< typename TRGBPixel::ValueType >( opaque[i] * m_Opacity + p1 * ( 1.0 - m_Opacity ) );
       }
     return rgbPixel;
  }

  bool operator != (const LabelOverlay &l) const
  { return l.m_Opacity == m_Opacity || m_UseBackground != l.m_UseBackground || m_BackgroundValue != l.m_BackgroundValue; }

  ~LabelOverlay() {}

  void SetOpacity( double opacity ) { m_Opacity = opacity; }

  void SetBackgroundValue( TLabel v ) { m_BackgroundValue = v; }

  void SetUseBackground( bool b ) { m_UseBackground = b; }

  double m_Opacity;

  bool m_UseBackground;

  TLabel m_BackgroundValue;

  typename itk::Functor::LabelToRGBFunctor<TLabel, TRGBPixel> m_RGBFunctor;
};
}  // end namespace functor


/** \class LabelOverlayImageFilter
 * \brief Apply a colormap to a label image and put it on top of the input image
 *
 * Apply a colormap to a label image and put it on top of the input image. The set of colors
 * is a good selection of distinct colors. The opacity of the label image
 * can be defined by the user.
 *
 * \author Ga�tan Lehmann. Biologie du D�veloppement et de la Reproduction, INRA de Jouy-en-Josas, France.
 *
 * \sa ScalarToRGBPixelFunctor LabelToRGBImageFilter
 * \ingroup Multithreaded
 *
 */
template <typename  TInputImage, class TLabelImage, typename  TOutputImage>
class ITK_EXPORT LabelOverlayImageFilter :
    public
BinaryFunctorImageFilter<TInputImage, TLabelImage, TOutputImage, 
                        Functor::LabelOverlay< 
  typename TInputImage::PixelType, 
  typename TLabelImage::PixelType, 
  typename TOutputImage::PixelType>   >
{
public:
  /** Standard class typedefs. */
  typedef LabelOverlayImageFilter  Self;
  typedef BinaryFunctorImageFilter<TInputImage, TLabelImage, TOutputImage, 
                        Functor::LabelOverlay< 
                            typename TInputImage::PixelType, 
                            typename TLabelImage::PixelType, 
                            typename TOutputImage::PixelType>   >  Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  typedef TOutputImage OutputImageType;
  typedef TLabelImage  LabelImageType;
  typedef TInputImage  InputImageType;
  typedef typename TOutputImage::PixelType OutputPixelType;
  typedef typename TLabelImage::PixelType  LabelPixelType;
  typedef typename TInputImage::PixelType  InputPixelType;

  /** Runtime information support. */
  itkTypeMacro(LabelOverlayImageFilter, BinaryFunctorImageFilter);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);
  
   /** Set the label image */
  void SetLabelImage(TLabelImage *input)
     { this->SetInput2( input ); }

  /** Get the label image */
  LabelImageType * GetLabelImage()
    { return static_cast<LabelImageType*>(const_cast<DataObject *>(this->ProcessObject::GetInput(1))); }

  itkSetMacro( Opacity, double );
  itkGetConstReferenceMacro( Opacity, double );

  itkSetMacro( BackgroundValue, LabelPixelType );
  itkGetConstReferenceMacro( BackgroundValue, LabelPixelType );

  itkSetMacro( UseBackground, bool );
  itkGetConstReferenceMacro( UseBackground, bool );
  itkBooleanMacro(UseBackground);

protected:
  LabelOverlayImageFilter();
  virtual ~LabelOverlayImageFilter() {};

  /** Process to execute before entering the multithreaded section */
  void BeforeThreadedGenerateData(void);

  /** Print internal ivars */
  void PrintSelf(std::ostream& os, Indent indent) const;
  
private:
  LabelOverlayImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  double m_Opacity;
  bool m_UseBackground;
  LabelPixelType m_BackgroundValue;

};


  
} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkLabelOverlayImageFilter.txx"
#endif

#endif

