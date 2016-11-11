This README file is the Introduction of "EE569_hw4_4946850713_Shen.zip" and 
                    the Guidance of compiling and running the projects.

The source code outside the .zip file is just a sample. Please unzip the .zip file to see and run the complete project.

#################################################

All the projects were built on Xcode(7.0.1), OS X (10.10.5)

#################################################

The Steps of running a projects: (Xcode)
1) open Xcode
2) open a project in the "EE569_hw4_4946850713_Shen.zip"
3) click “command+B” to build 
4) click “command+R” to run

#################################################
  
Problem 1 (a):   implement the OCR of the training image

Project:         OCR_test->OCR_test(.xcodeproj)

Source File:     main.cpp 

Input Image:     Training.raw

Output Image:    Segment_result.raw

Output results:  display in 'All Output' console


#################################################
  
Problem 1 (b):   implement the OCR of the ideal test image

Project:         OCR_test1->OCR_test1(.xcodeproj)

Source File:     main.cpp 

Input Image:     Test_ideal1.raw

Output results:  display in 'All Output' console

#################################################

Problem 1 (b):   implement the OCR of the ideal test image

Project:         OCR_test2->OCR_test2(.xcodeproj)

Source File:     main.cpp 

Input Image:     Test_ideal2.raw

Output Image:    Binary_ideal2_3.raw

Output results:  display in 'All Output' console

#################################################

Problem 1 (c):   implement the OCR of the “night” test image

Project:         OCR_night->OCR_night(.xcodeproj)

Source File:     main.cpp 

Input Image:     Test_night.raw

Output Image:    Binary_night_3.raw

Output results:  display in 'All Output' console

#################################################

Problem 1 (c):   implement the OCR of the “shade” test image

Project:         OCR_shade->OCR_shade(.xcodeproj)

Source File:     main.cpp 

Input Image:     Test_shade.raw

Output Image:    Binary_shade_1.raw
                 Binary_shade_2.raw
                 Binary_shade_3.raw
                 Segment_shade.raw

Output results:  display in 'All Output' console

#################################################
  
Problem 2:       Contour Modeling

Instructions:    Because we use other people’s tools online, so there is no code submitted              
                 for this part. 
                
#################################################

Problem 3:       Image Matching 

Instructions:    Because we use other people’s codes for this part. So the code I submit                
                 is how I implement these tools online but not the one I write by myself.

Pre-request
package :        VlFeat open source library, VLFeat-0.9.20 (not in the zip file)
                 To install it, in command window, input 
                 “>> run('vlfeat-0.9.20/toolbox/vl_setup’)”

M-file name:     siftFeature.m
(Problem3)       surfFeature.m
                 schoolbusMatch.m
                 carMatch1.m
                 carMatch2.m
                 bagOfWord.m

                
#################################################
