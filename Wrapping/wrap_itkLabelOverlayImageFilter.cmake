WRAP_CLASS("itk::LabelOverlayImageFilter" POINTER_WITH_SUPERCLASS)
  UNIQUE(label_types "${WRAP_ITK_INT};UL")

  FOREACH(t ${label_types})
    IF(WRAP_rgb_unsigned_short AND WRAP_unsigned_short)
      WRAP_IMAGE_FILTER_TYPES(US ${t} RGBUS)
    ENDIF(WRAP_rgb_unsigned_short AND WRAP_unsigned_short)

    IF(WRAP_rgb_unsigned_char AND WRAP_unsigned_char)
      WRAP_IMAGE_FILTER_TYPES(UC ${t} RGBUC)
    ENDIF(WRAP_rgb_unsigned_char AND WRAP_unsigned_char)
  ENDFOREACH(t)

END_WRAP_CLASS()
