### Simple Card Detector ###
Uses Canny Edge Detection and Houghline to detect cards ( or any rectangular shaped object in that matter)

### Instructions ###
- Project requires NDK and opencv lib
- Modify the ndk.dir accordingly within local properties
- Please do include the openCVLibrary300 within the directory and link it properly within the project
- Does not depend on the OpenCV Manager, uses static library instead, have included them in jnilibs, but please do 
link them properly in the mk files (opencv dir mk path and such) found in jni as we're building native C++ objects and 
also the wrapper for JNI