WRAP_CLASS("itk::LabelOverlayImageFilter" POINTER_WITH_SUPERCLASS)
  FOREACH(d ${WRAP_DIMS})
    COND_WRAP("${ITKM_IUS${d}}${ITKM_IUL${d}}${ITKM_IRGBUS${d}}" "${ITKT_IUS${d}},${ITKT_IUL${d}},${ITKT_IRGBUS${d}}" "US;RGBUS") # needed for watershed
    COND_WRAP("${ITKM_IUS${d}}${ITKM_IUS${d}}${ITKM_IRGBUS${d}}" "${ITKT_IUS${d}},${ITKT_IUS${d}},${ITKT_IRGBUS${d}}" "US;RGBUS")
    COND_WRAP("${ITKM_IUS${d}}${ITKM_IUC${d}}${ITKM_IRGBUS${d}}" "${ITKT_IUS${d}},${ITKT_IUC${d}},${ITKT_IRGBUS${d}}" "US;UC;RGBUS")
    COND_WRAP("${ITKM_IUC${d}}${ITKM_IUL${d}}${ITKM_IRGBUC${d}}" "${ITKT_IUC${d}},${ITKT_IUL${d}},${ITKT_IRGBUC${d}}" "UC;RGBUC") # needed for watershed
    COND_WRAP("${ITKM_IUC${d}}${ITKM_IUS${d}}${ITKM_IRGBUC${d}}" "${ITKT_IUC${d}},${ITKT_IUS${d}},${ITKT_IRGBUC${d}}" "UC;US;RGBUC")
    COND_WRAP("${ITKM_IUC${d}}${ITKM_IUC${d}}${ITKM_IRGBUC${d}}" "${ITKT_IUC${d}},${ITKT_IUC${d}},${ITKT_IRGBUC${d}}" "UC;RGBUC")
  ENDFOREACH(d)
END_WRAP_CLASS()
