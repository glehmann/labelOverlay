#ifndef __itkLabelOverlayImageFilter_h
#define __itkLabelOverlayImageFilter_h

#include "itkBinaryFunctorImageFilter.h"

namespace itk
{

namespace Functor {  
 
template< class TInputPixel, class TLabel, class TRGBPixel >
class LabelOverlay
{
public:
  LabelOverlay()
  {
    
    TRGBPixel rgbPixel;
    // the following colors are from "R", and named:
    // "red"             "green3"          "blue"            "cyan"           
    //"magenta"         "darkorange1"     "darkgreen"       "blueviolet"     
    //"brown4"          "navy"            "yellow4"         "violetred1"     
    //"salmon4"         "turquoise4"      "sienna3"         "darkorchid1"    
    //"springgreen4"    "mediumvioletred" "orangered3"      "lightseagreen"  
    //"slateblue"       "deeppink1"       "aquamarine4"     "royalblue1"     
    //"tomato3"         "mediumblue"      "violetred4"      "darkmagenta"    
    //"violet"          "red4"           
    // They are a good selection of distinct colours for plotting and
    // overlays.
    
    rgbPixel.Set(255, 0, 0);
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set(0, 205, 0);
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 0 , 0 , 255 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 0 , 255 , 255 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 255 , 0 , 255 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 255 , 127 , 0 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 0 , 100 , 0 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 138 , 43 , 226 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 139 , 35 , 35 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 0 , 0 , 128 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 139 , 139 , 0 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 255 , 62 , 150 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 139 , 76 , 57 );
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( 0 , 134 , 139 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 205 , 104 , 57 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 191 , 62 , 255 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 0 , 139 , 69 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 199 , 21 , 133 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 205 , 55 , 0 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 32 , 178 , 170 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 106 , 90 , 205 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 255 , 20 , 147 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 69 , 139 , 116 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 72 , 118 , 255 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 205 , 79 , 57 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 0 , 0 , 205 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 139 , 34 , 82 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 139 , 0 , 139 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 238 , 130 , 238 );
    m_Colors.push_back( rgbPixel );

    rgbPixel.Set( 139 , 0 , 0 );
    m_Colors.push_back( rgbPixel );

  }

  inline TRGBPixel operator()(  const TInputPixel & p1,
				const TLabel & p2)
  {
    if( p2 == itk::NumericTraits< TLabel >::Zero )
      {
      typename TRGBPixel::ValueType p = static_cast< typename TRGBPixel::ValueType >( p1 );
      TRGBPixel rgbPixel;
      rgbPixel.Set( p, p, p );
      return rgbPixel;
      }
     TRGBPixel rgbPixel;
     for( int i = 0; i<3; i++)
       {
       rgbPixel[i] = static_cast< typename TRGBPixel::ValueType >( m_Colors[ p2 % m_Colors.size() ][i] * m_Opacity + p1 * ( 1.0 - m_Opacity ) );
       }
     return rgbPixel;
  }

  bool operator != (const LabelOverlay&) const
  { return false; }

  ~LabelOverlay() {}

  void SetOpacity( double opacity ) { m_Opacity = opacity; }

  std::vector< TRGBPixel > m_Colors;

  double m_Opacity;
};
}  // end namespace functor


/** \class LabelOverlayImageFilter
 * \brief TODO
 *
 *
 * \author Gaëtan Lehmann. Biologie du Développement et de la Reproduction, INRA de Jouy-en-Josas, France.
 * \author Richard Beare. Department of Medicine, Monash University, Melbourne, Australia.
 *
 * \sa TODO
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
    { return this->GetInput2(); }

  itkSetMacro( Opacity, double );
  itkGetConstReferenceMacro( Opacity, double );

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
};


  
} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkLabelOverlayImageFilter.txx"
#endif

#endif

