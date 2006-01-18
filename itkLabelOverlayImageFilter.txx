#ifndef _itkLabelOverlayImageFilter_txx
#define _itkLabelOverlayImageFilter_txx

#include "itkLabelOverlayImageFilter.h"

namespace itk
{

/**
 *
 */
template <class TInputImage, class TLabelImage, class TOutputImage>
LabelOverlayImageFilter<TInputImage, TLabelImage, TOutputImage>
::LabelOverlayImageFilter()
{
}

// template <class TInputImage, class TLabelImage, class TOutputImage>
// void
// LabelOverlayImageFilter<TInputImage, TLabelImage, TOutputImage>
// ::BeforeThreadedGenerateData()
// {
//   this->GetFunctor().SetMaximum(m_Maximum);
// }

/**
 *
 */
// template <class TInputImage, class TLabelImage, class TOutputImage>
// void 
// LabelOverlayImageFilter<TInputImage, TLabelImage, TOutputImage>
// ::PrintSelf(std::ostream& os, Indent indent) const
// {
//   Superclass::PrintSelf(os,indent);
// 
//   os << indent << "Maximum: "
//      << static_cast<typename NumericTraits<InputPixelType>::PrintType>(m_Maximum)
//      << std::endl;
// }


} // end namespace itk

#endif
