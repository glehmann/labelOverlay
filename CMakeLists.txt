#Change PROJECT_NAME to the name of your project
PROJECT(labelOverlay)

# set the name of the input image used to run the test
SET(INPUT_IMAGE ${CMAKE_SOURCE_DIR}/images/cthead1.png)

#include some macros from another file...
INCLUDE(IJMacros.txt)

#The following lines are required to use Dart
ENABLE_TESTING()
INCLUDE(Dart)
FIND_PROGRAM(IMAGE_COMPARE ImageCompare)

#Declare any external dependencies that your project may have here.
#examples include: ITK, VTK, JPEG, PNG, OpenGL, ZLIB, Perl, Java
#If you're not sure what name to use, look in the Modules directory of your
#cmake install and check that a file named Find(Package).cmake exists
SET(Required_Packages
  ITK
)

#this foreach loads all of the packages that you specified as required.
#It shouldn't need to be modified.
FOREACH(Package ${Required_Packages})
  LOADPACKAGE(${Package})
ENDFOREACH(Package)

#Set any libraries that your project depends on.
#examples: ITKCommon, VTKRendering, etc
SET(Libraries
  ITKCommon
  ITKBasicFilters
  ITKIO
)

#the following block of code is an example of how to build an executable in
#cmake.  Unmodified, it will add an executable called "MyExe" to the project.
#MyExe will be built using the files MyClass.h and MyClass.cxx, and it will
#be linked to all the libraries you specified above. 
#You can build more than one executable per project

IF(BUILD_TESTING)

SET(CurrentExe "check")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

SET(CurrentExe "check2")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

ENDIF(BUILD_TESTING)

#the following line is an example of how to add a test to your project.
#Testname is the title for this particular test.  ExecutableToRun is the
#program which will be running this test.  It can either be a part of this
#project or an external executable.  After that list any args that are needed
#for this test.  Include as many tests as you like.  If your project doesn't have
#any tests you can comment out or delete the following line.
# ADD_TEST(Testname ExecutableToRun arg1 arg2 arg3)

FOREACH(opacity 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0)
  STRING(REGEX REPLACE "\\." "_" op ${opacity})
  ADD_TEST(Opacity-${op} check2 ${CMAKE_SOURCE_DIR}/images/cthead1.png ${CMAKE_SOURCE_DIR}/images/cthead1MF.png out-${op}.png ${opacity})
  ADD_TEST(CompareImage-${op} ${IMAGE_COMPARE} out-${op}.png ${CMAKE_SOURCE_DIR}/images/out-${op}.png)
ENDFOREACH(opacity)

ADD_TEST(Overlay check2 ${CMAKE_SOURCE_DIR}/images/cthead1.png ${CMAKE_SOURCE_DIR}/images/cthead1MF.png Overlay.png)
ADD_TEST(OverlayCompare ${IMAGE_COMPARE} Overlay.png ${CMAKE_SOURCE_DIR}/images/out-0_7.png)
ADD_TEST(OverlayUseBg check2 ${CMAKE_SOURCE_DIR}/images/cthead1.png ${CMAKE_SOURCE_DIR}/images/cthead1MF.png OverlayUseBg.png 0.7 1)
ADD_TEST(OverlayUseBgCompare ${IMAGE_COMPARE} OverlayUseBg.png ${CMAKE_SOURCE_DIR}/images/OverlayUseBg.png)
ADD_TEST(OverlayUseBg176 check2 ${CMAKE_SOURCE_DIR}/images/cthead1.png ${CMAKE_SOURCE_DIR}/images/cthead1MF.png OverlayUseBg176.png 0.7 1 176)
ADD_TEST(OverlayUseBg176Compare ${IMAGE_COMPARE} OverlayUseBg176.png ${CMAKE_SOURCE_DIR}/images/OverlayUseBg176.png)

ADD_TEST(Color check ${CMAKE_SOURCE_DIR}/images/cthead1-markers.png Color.png)
ADD_TEST(ColorCompare ${IMAGE_COMPARE} Color.png ${CMAKE_SOURCE_DIR}/images/Color.png)
ADD_TEST(ColorUseBg check ${CMAKE_SOURCE_DIR}/images/cthead1-markers.png ColorUseBg.png 1)
ADD_TEST(ColorUseBgCompare ${IMAGE_COMPARE} ColorUseBg.png ${CMAKE_SOURCE_DIR}/images/ColorUseBg.png)
ADD_TEST(ColorUseBg176 check ${CMAKE_SOURCE_DIR}/images/cthead1-markers.png ColorUseBg176.png 1 176)
ADD_TEST(ColorUseBg176Compare ${IMAGE_COMPARE} ColorUseBg176.png ${CMAKE_SOURCE_DIR}/images/ColorUseBg176.png)



OPTION(BUILD_WRAPPERS "Wrap library" OFF)
IF(BUILD_WRAPPERS)
   SUBDIRS(Wrapping)
ENDIF(BUILD_WRAPPERS)

# install devel files
OPTION(INSTALL_DEVEL_FILES "Install C++ headers" ON)
IF(INSTALL_DEVEL_FILES)
FOREACH(f itkLabelOverlayImageFilter.h itkLabelOverlayImageFilter.txx)
  INSTALL_FILES(/include/InsightToolkit/BasicFilters FILES ${labelOverlay_SOURCE_DIR}/${f})
ENDFOREACH(f)
ENDIF(INSTALL_DEVEL_FILES)
